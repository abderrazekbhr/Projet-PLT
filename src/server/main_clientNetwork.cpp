#include <iostream>
#include <fstream>
#include "server.h"
#include <thread>
#include <state/Player.h>
using namespace server;

int main()
{
    /*try
    {
        // Création d'une instance de State directement (plus simple, sans allocation dynamique)
        state::State state;

        // Création d'une instance de NetworkClient et passage de la référence de state
        NetworkClient client("127.0.0.1", 8080, &state);
        client.connectToServer();
        // Réception de l'identifiant du client
        auto id = client.receiveIdentifier();
        client.setPlayerName(id);

        // Obtention de tous les joueurs à partir de l'état
        auto players = state.getAllPlayers();

        // Configuration de la requête venant du serveur
        ServerRequest configRequest = client.receiveRequest();
        client.handleServerRequest(configRequest);

        while (true)
        {
            // Réception de l'état du jeu du serveur
            auto gameStateString = client.receiveLargeJson();
            auto gameState = client.deserializeGameState(gameStateString);
            client.updateGameState(gameState);

            // Affichage du tableau de jeu
            state.getBoard();

            // Vérification si c'est au tour du joueur actuel
            bool isCurrentPlayer = false;
            for (const auto& player : players)
            {
                if (player->getName() == client.getPlayerName())
                {
                    isCurrentPlayer = true;
                    break;
                }
            }

            if (isCurrentPlayer)
            {
                // Réception et gestion de la requête du serveur
                server::ServerRequest request = client.receiveRequest();
                client.handleServerRequest(request);
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }*/
    return 0;
}
