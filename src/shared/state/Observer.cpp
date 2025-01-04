#include "Observer.h"
#include "StateEvent.h"
#include "State.h"
#include <iostream>

namespace state {

    void Observer::StateChanged(StateEvent& event, State& state) {
        // Récupérer l'ID de l'événement
        StateEventId eventId = event.getStateEventId();
        
        // Réagir en fonction du type d'événement
        switch (eventId) {
            case StateEventId::SET_UP:
                std::cout << "Setup de l'état du jeu." << std::endl;
                // Logique spécifique au setup
                break;

            case StateEventId::DISTRIBUTE:
                std::cout << "Distribution des cartes." << std::endl;
                // Exemple : mettre à jour l'affichage des cartes distribuées
                break;

            case StateEventId::CACUL_SCORE:
                std::cout << "Calcul du score en cours." << std::endl;
                // Exemple : afficher les scores mis à jour
                break;

            case StateEventId::PLAYER_THROW_CARD:
                std::cout << "Un joueur a joué une carte." << std::endl;
                // Exemple : mettre à jour l'affichage des cartes jouées
                break;

            case StateEventId::PLAYER_CAPTURE_CARD:
                std::cout << "Un joueur a capturé une carte." << std::endl;
                // Exemple : mettre à jour l'affichage des cartes capturées
                break;

            default:
                std::cerr << "Événement inconnu reçu." << std::endl;
                break;
        }
    }
}
