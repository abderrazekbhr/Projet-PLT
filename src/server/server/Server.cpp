
#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json/json.h>
// #include "../../src/client/client.h"
using namespace server;
using namespace state;
using namespace engine;
// using namespace client;

const std::string ACK_MESSAGE = "ACK";

Server::Server(int port, bool running, State* state)
    : server_fd(-1), port(port), running(running), nextClientId(0), state(state) {}


Server::~Server() {
    stop();
}

void Server::start() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        throw std::runtime_error("Failed to create socket");
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        throw std::runtime_error("Failed to set SO_REUSEADDR");
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return;
    }

    running = true;
    std::cout << "Server is listening on port " << port << "..." << std::endl;
}

void Server::stop() {
    running = false;
    for (int client_fd : clients) {
        close(client_fd);
    }
    clients.clear();
    if (server_fd != -1) {
        close(server_fd);
        server_fd = -1;
    }
    std::cout << "Server stopped." << std::endl;
}

void Server::acceptClients() {
    sockaddr_in client_address{};
    socklen_t client_len = sizeof(client_address);

    int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_len);
    if (client_fd < 0) {
        perror("Accept failed");
        return;
    }

    clients.push_back(client_fd);
    clientIds[client_fd] = nextClientId++;
    std::cout << "New client connected with ID: " << clientIds[client_fd] << std::endl;
}

void Server::sendRequestToClient(int clientId, ServerRequest& request) {
    std::string serializedRequest = request.serialize();
    ssize_t sent = send(clientId, serializedRequest.c_str(), serializedRequest.size(), 0);
    if (sent != static_cast<ssize_t>(serializedRequest.size())) {
        perror("Failed to send request");
        throw std::runtime_error("Error sending request to client.");
    }
    std::cout << "Request sent to client " << clientId << ": " << serializedRequest << std::endl;

    if (!waitForAcknowledgment(clientId)) {
        throw std::runtime_error("Failed to receive acknowledgment from client.");
    }
}

Json::Value Server::receiveResponseFromClient(int clientId) {
    char buffer[4096];
    ssize_t bytesReceived = recv(clientId, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
        throw std::runtime_error("Failed to receive response from client.");
    }

    buffer[bytesReceived] = '\0';
    std::string jsonString(buffer);
    std::istringstream jsonStream(jsonString);
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errors;

    if (!Json::parseFromStream(reader, jsonStream, &root, &errors)) {
        throw std::runtime_error("Failed to parse JSON response: " + errors);
    }

    sendAcknowledgment(clientId);
    return root;
}

std::string Server::serializeGameState() {
    Json::Value root;
    root["gameState"] = "Sample serialized state"; // Placeholder for real serialization logic.
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, root);
}

Json::Value Server::serializeCardsDeck(CardsDeck* cards) {
    Json::Value jsonDeck;
    jsonDeck["deckSize"] = 40;
    return jsonDeck;
}

void Server::sendIdentifierToClients() {
    for (std::vector<int>::size_type i = 0; i < clients.size(); ++i) {
        ssize_t sent = send(clients[i], &i, sizeof(i), 0);
        if (sent != sizeof(i)) {
            perror("Failed to send identifier");
            throw std::runtime_error("Error sending identifier to client.");
        }

        if (!waitForAcknowledgment(clients[i])) {
            throw std::runtime_error("Failed to receive acknowledgment for identifier.");
        }
        std::cout << "Sent identifier " << i << " to client." << std::endl;
    }
}

std::vector<int> Server::handleClientResponse(int client_fd, Json::Value& response) {
    RequestType type = static_cast<RequestType>(response["type"].asInt());
    const Json::Value& data = response["response"];
    std::vector<int> result;

    switch (type) {
        case RequestType::Actions:
            std::cout << "Client performed an action." << std::endl;
            // Parse action data (example placeholder)
            break;

        case RequestType::GameSettings:
            std::cout << "Client adjusted game settings." << std::endl;
            result.push_back(data["setting"].asInt());
            break;

        default:
            std::cerr << "Unknown request type received." << std::endl;
    }

    return result;
}

void Server::broadcastGameState() {
    auto gameState = serializeGameState();
    for (int client_fd : clients) {
        sendLargeJson(client_fd, gameState);
    }
}

bool Server::waitForAcknowledgment(int client_fd) {
    char buffer[16];
    ssize_t bytesReceived = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
        return false;
    }
    buffer[bytesReceived] = '\0';
    return std::string(buffer) == ACK_MESSAGE;
}

void Server::sendAcknowledgment(int client_fd) {
    send(client_fd, ACK_MESSAGE.c_str(), ACK_MESSAGE.size(), 0);
}

void Server::sendLargeJson(int client_fd, const std::string& jsonString) {
    uint32_t totalSize = htonl(jsonString.size());
    send(client_fd, &totalSize, sizeof(totalSize), 0);

    size_t bytesSent = 0;
    size_t chunkSize = 4096;

    while (bytesSent < jsonString.size()) {
        size_t remaining = jsonString.size() - bytesSent;
        size_t currentChunkSize = std::min(chunkSize, remaining);

        send(client_fd, jsonString.data() + bytesSent, currentChunkSize, 0);
        bytesSent += currentChunkSize;
    }

    waitForAcknowledgment(client_fd);
}

void Server::handleActions(Engine* gameEngine) {
    ServerRequest actionRequest;
    actionRequest.type = Actions;

    for (int client_fd : clients) {
        sendRequestToClient(client_fd, actionRequest);
        Json::Value response = receiveResponseFromClient(client_fd);
        handleClientResponse(client_fd, response);
    }
}
