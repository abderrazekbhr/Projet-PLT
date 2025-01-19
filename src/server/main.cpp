#include "server.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "state.h"
#include "engine.h"
#include "../client/client.h"
using namespace state;
using namespace server;
using namespace engine;
using namespace client;

int main()
{
    // Initialisation de l'état du jeu
    State* state = new State();

    // Création et démarrage du serveur
    auto server = new Server(8080, true, state);
    server->start();

    std::cout << "Waiting for clients..." << std::endl;

    // Acceptation des clients (maximum 2)
    while (server->clients.size() < 2)
    {
        server->acceptClients();
    }

    // Envoi de l'identifiant aux clients
    server->sendIdentifierToClients();

    // Définition de la requête de déplacement
    ServerRequest moveRequest;
    moveRequest.type = server::RequestType::Actions;

    // Initialisation du moteur de jeu
    auto gameEngine = new Engine();

    // Déclaration des variables pour gérer les joueurs et les clients
    client::Client* client;
    Player* currentPlayer;

    // Lancement d'un thread pour gérer le serveur et les actions des clients
    std::thread serverThread([&]()
    {
        int clientId = -1;

        // Boucle pour traiter les actions des clients
        while (server->clients.size() < 2)
        {
            // Attente que les clients se connectent (on peut étendre la logique ici)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Une fois les clients connectés, on traite les actions
        server->handleActions(gameEngine);
    });

    // Le serveur attend un délai arbitraire avant de s'arrêter
    std::this_thread::sleep_for(std::chrono::seconds(600));

    // Arrêt du serveur et des threads
    server->stop();
    serverThread.join();
    return 0;
}
