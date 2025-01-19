#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <json/json.h>
#include "../server.h"

using namespace server;
using namespace state;

const std::string ACK_MESSAGE = "ACK";

NetworkClient::NetworkClient(std::string server_ip, int port, state::State* state)
    : client_fd(-1), server_ip(server_ip), server_port(port), state(state) {}

NetworkClient::~NetworkClient() {
    disconnect();
}

void NetworkClient::connectToServer() {
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        return;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return;
    }

    if (connect(client_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return;
    }

    std::cout << "Connected to server." << std::endl;
}

void NetworkClient::disconnect() {
    if (client_fd != -1) {
        close(client_fd);
        client_fd = -1;
    }
}

void NetworkClient::handleServerRequest(ServerRequest& request) {
    switch (request.type) {
    case Actions: {
        std::cout << "Actions Request Received. Choose an action:\n"
                  << "(1) Capture Card\n"
                  << "(2) Throw Card\n";

        int actionChoice;
        std::cin >> actionChoice;

        Json::Value response;
        if (actionChoice == 1) {
            response["action"] = "Capture Card";
        } else if (actionChoice == 2) {
            response["action"] = "Throw Card";
        } else {
            std::cerr << "Invalid choice. No action taken." << std::endl;
            response["action"] = "None";
        }

        sendResponseToServer(request.type, response);
        break;
    }

    case GameSettings: {
        std::cout << "GameSettings Request Received. Configure game settings:\n"
                  << "(1) Number of Players\n"
                  << "(2) Maximum Score\n";

        int settingChoice;
        std::cout << "Enter your choice: ";
        std::cin >> settingChoice;

        Json::Value response;
        response["settingChoice"] = settingChoice;

        sendResponseToServer(request.type, response);
        break;
    }

    default:
        std::cerr << "Unknown request type received." << std::endl;
        break;
    }
}

GameState NetworkClient::deserializeGameState(const std::string& jsonString) {
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errors;

    std::istringstream jsonStream(jsonString);
    if (!Json::parseFromStream(reader, jsonStream, &root, &errors)) {
        throw std::runtime_error("Failed to parse JSON: " + errors);
    }

    GameState gameState;

    if (!root.isMember("cards") || !root["cards"].isArray()) {
        throw std::runtime_error("Invalid JSON: Missing 'cards' array.");
    }

    for (const auto& jsonCard : root["cards"]) {
        if (!jsonCard.isMember("value") || !jsonCard.isMember("suit") || !jsonCard.isMember("owner")) {
            throw std::runtime_error("Invalid JSON: Missing required fields in card object.");
        }

        NumberCard number = static_cast<NumberCard>(jsonCard["value"].asInt());
        TypeCard type = static_cast<TypeCard>(jsonCard["suit"].asInt());

        Card card(number, type);
        gameState.cards->getAllCards().push_back(card);
    }

    gameState.currentPlayer = root["currentPlayer"].asInt();
    return gameState;
}

void NetworkClient::updateGameState(GameState gameState) {
    for (const Card& card : gameState.cards->getAllCards()) {
        state->getAllCards()->getAllCards().push_back(card);
    }
    state->addPlayer(gameState.currentPlayer);
}

std::string NetworkClient::receiveIdentifier() {
    char buffer[512];  // Tampon pour éviter débordement
    ssize_t received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (received <= 0) {
        perror("Failed to receive identifier");
        throw std::runtime_error("Error receiving identifier from server.");
    }

    std::string identifier(buffer, received);  // Crée une chaîne à partir du tampon reçu
    std::cout << "Received identifier: " << identifier << std::endl;

    try {
        sendAcknowledgment();
    } catch (const std::exception& e) {
        std::cerr << "Failed to send acknowledgment in receiveIdentifier: " << e.what() << std::endl;
        throw;
    }

    return identifier;
}

void NetworkClient::sendResponseToServer(RequestType type, Json::Value response) {
    Json::Value root;
    root["type"] = static_cast<int>(type);
    root["response"] = response;

    Json::StreamWriterBuilder writer;
    std::string serializedResponse = Json::writeString(writer, root);

    ssize_t sent = send(client_fd, serializedResponse.c_str(), serializedResponse.size(), 0);
    if (sent != static_cast<ssize_t>(serializedResponse.size())) {
        perror("Failed to send response to server");
        throw std::runtime_error("Error sending response to server.");
    }

    if (!waitForAcknowledgment()) {
        throw std::runtime_error("Failed to receive acknowledgment in sendResponseToServer.");
    }
}

ServerRequest NetworkClient::receiveRequest() {
    char buffer[4096];
    ssize_t bytesReceived = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
        throw std::runtime_error("Failed to receive request from server.");
    }

    buffer[bytesReceived] = '\0';
    std::string jsonString(buffer);

    ServerRequest request;
    try {
        sendAcknowledgment();
    } catch (const std::exception& e) {
        std::cerr << "Failed to send acknowledgment in receiveRequest: " << e.what() << std::endl;
        throw;
    }

    return request.deserialize(jsonString);
}

bool NetworkClient::waitForAcknowledgment() {
    char buffer[4096];
    ssize_t bytesReceived = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived <= 0) {
        perror("Failed to receive acknowledgment");
        return false;
    }

    buffer[bytesReceived] = '\0';
    std::string response(buffer);

    return response == ACK_MESSAGE;
}

void NetworkClient::sendAcknowledgment() {
    ssize_t sent = send(client_fd, ACK_MESSAGE.c_str(), ACK_MESSAGE.size(), 0);
    if (sent != static_cast<ssize_t>(ACK_MESSAGE.size())) {
        throw std::runtime_error("Failed to send acknowledgment to server.");
    }
}

std::string NetworkClient::receiveLargeJson() {
    std::string data;
    char buffer[4096];
    ssize_t bytesReceived;

    while ((bytesReceived = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        data += buffer;
        if (bytesReceived < sizeof(buffer) - 1) break; // Fin des données
    }

    if (bytesReceived < 0) {
        throw std::runtime_error("Error receiving large JSON from server.");
    }

    return data;
}
