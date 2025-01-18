#include "ai.h"
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using namespace ai;
using namespace std;
using namespace state;
using namespace engine;

// Constructor
HeuristicAi::HeuristicAi(string name) : AI(name) {}

// Utility function to calculate the sum of card values
int cardSum(vector<Card> &cards, vector<int> &indices) {
    int sum = 0;
    for (int i : indices) {
        sum += cards[i].getNumberCard();
    }
    return sum;
}

int cardSum(vector<Card> &cards) {
    int sum = 0;
    for (auto &card : cards) {
        sum += card.getNumberCard();
    }
    return sum;
}

// Function to find all combinations of indices from a vector
void findCombinationsIndices(vector<int> &indices, vector<vector<int>> &result, vector<int> &tempCombination, size_t start) {
    result.push_back(tempCombination); // Add current combination
    for (size_t i = start; i < indices.size(); ++i) {
        tempCombination.push_back(indices[i]);
        findCombinationsIndices(indices, result, tempCombination, i + 1);
        tempCombination.pop_back();
    }
}

// Helper function to find the index of Sept Dinari in a card set
int findSeptDinari(vector<Card> &cards) {
    for (size_t i = 0; i < cards.size(); ++i) {
        if (cards[i].getNumberCard() == 7 && cards[i].getTypeCard() == carreau) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to find possible moves for Chkobba
std::map<std::string, std::vector<int>> HeuristicAi::checkPossibleChkoba(
    std::vector<state::Card> hand, std::vector<state::Card> cardsOnBoard)
{
    std::map<std::string, std::vector<int>> result;

    // Calcul de la somme totale des cartes sur le plateau
    int totalBoardSum = 0;
    for (auto& card : cardsOnBoard) {
        totalBoardSum += card.getNumberCard();  // Assuming `getNumberCard()` gives the card's value
    }

    // Parcours chaque carte de la main
    for (size_t i = 0; i < hand.size(); ++i) {
        state::Card &chosenCard = hand[i];
        int targetValue = chosenCard.getNumberCard(); // Valeur de la carte de la main

        // Vérifier si la carte choisie dans la main peut capturer toutes les cartes du plateau
        if (targetValue == totalBoardSum) {
            // Si la somme des cartes sur le plateau correspond à la valeur de la carte choisie
            result["hand"] = {static_cast<int>(i)};  // Indice de la carte dans la main
            result["board"] = {};  // Toutes les cartes sur le plateau doivent être capturées
            for (size_t j = 0; j < cardsOnBoard.size(); ++j) {
                result["board"].push_back(static_cast<int>(j));  // Ajouter les indices des cartes du plateau
            }
            return result; // Retourner dès qu'une capture est possible
        }
    }

    // Si aucune condition de Chkobba n'est trouvée, on retourne un résultat vide
    result["hand"] = {};
    result["board"] = {};
    return result;
}


// Function to find possible moves for Sept Dinari
std::map<std::string, std::vector<int>> HeuristicAi::checkPossible7Carreau(std::vector<state::Card> hand, std::vector<state::Card> cardsOnBoard) {
    map<string, vector<int>> vals;

    int handIndex = findSeptDinari(hand);  // Recherche du "Sept de Carreau" dans la main
    int boardIndex = findSeptDinari(cardsOnBoard);  // Recherche du "Sept de Carreau" sur le plateau



    if (handIndex != -1 && boardIndex != -1) {
        vals["hand"] = {handIndex};
        vals["board"] = {boardIndex};
        return vals;
    }

    // Si un "Sept de Carreau" est trouvé sur le plateau, on capture ce "Sept" avec n'importe quel "Sept" de la main
    if (boardIndex != -1) {
        // Chercher un "Sept" dans la main
        int x = hand.size();
        for (int i = 0; i < x; ++i) {
            if (hand[i].getNumberCard() == 7) {  // On s'assure que l'on prend un "Sept" de la main
                vals["hand"] = {i};  // Indice du "Sept" dans la main
                vals["board"] = {boardIndex};  // Indice du "Sept" sur le plateau
                return vals;
            }
        }
    }

    vector<int> indicesOnBoard(cardsOnBoard.size());
    iota(indicesOnBoard.begin(), indicesOnBoard.end(), 0);

    if (handIndex != -1) {
        vector<vector<int>> allCombinations;
        vector<int> combinationTemp;

        findCombinationsIndices(indicesOnBoard, allCombinations, combinationTemp, 0);

        for (auto &combination : allCombinations) {
            if (cardSum(cardsOnBoard, combination) == 7) {
                vals["hand"] = {handIndex};
                vals["board"] = combination;
                return vals;
            }
        }
    }

    return vals;
}

// Function to determine the best move to maximize profit
std::map<std::string, std::vector<int>> HeuristicAi::maximiseProfit(std::vector<state::Card> hand, std::vector<state::Card> cardsOnBoard) {
    map<string, vector<int>> bestMove;
    int maxScore = 0;

    vector<int> indicesOnBoard(cardsOnBoard.size());
    iota(indicesOnBoard.begin(), indicesOnBoard.end(), 0);

    // Prioriser les cartes de type carreau
    int carreauIndex = -1;
    // Chercher si une carte de type carreau existe dans les cartes du plateau
    for (size_t j = 0; j < cardsOnBoard.size(); ++j) {
        if (cardsOnBoard[j].getTypeCard() == carreau) {
            carreauIndex = static_cast<int>(j);
            break;
        }
    }

    // Si une carte de type carreau existe, l'IA doit la prioriser
    if (carreauIndex != -1) {
        for (size_t i = 0; i < hand.size(); ++i) {
            Card &chosenCard = hand[i];
            // Vérifier s'il y a une correspondance directe avec la carte carreau
            if (cardsOnBoard[carreauIndex].getNumberCard() == chosenCard.getNumberCard()) {
                bestMove["hand"] = {static_cast<int>(i)};
                bestMove["board"] = {carreauIndex};
                return bestMove; // Retourner immédiatement la carte carreau capturée
            }
        }
    }

    // Si aucune carte carreau n'est trouvée, continuer avec la logique de maximisation du profit
    for (size_t i = 0; i < hand.size(); ++i) {
        Card &chosenCard = hand[i];

        // Vérifier s'il y a une correspondance directe avec la carte du plateau
        for (size_t j = 0; j < cardsOnBoard.size(); ++j) {
            if (cardsOnBoard[j].getNumberCard() == chosenCard.getNumberCard()) {
                bestMove["hand"] = {static_cast<int>(i)};
                bestMove["board"] = {static_cast<int>(j)};
                return bestMove; // Retourner immédiatement si une carte correspondante est trouvée
            }
        }

        // Si aucune correspondance directe, continuer avec la logique de combinaison
        vector<vector<int>> allCombinations;
        vector<int> combinationTemp;

        findCombinationsIndices(indicesOnBoard, allCombinations, combinationTemp, 0);

        for (auto &combination : allCombinations) {
            if (cardSum(cardsOnBoard, combination) == chosenCard.getNumberCard()) {
                int sizeScore = combination.size();
                int dinariCount = 0, septCount = 0;

                for (int idx : combination) {
                    if (cardsOnBoard[idx].getTypeCard() == carreau)
                        dinariCount++;
                    if (cardsOnBoard[idx].getNumberCard() == 7)
                        septCount++;
                }

                int totalScore = sizeScore + dinariCount + 2 * septCount;

                if (totalScore > maxScore) {
                    maxScore = totalScore;
                    bestMove["hand"] = {static_cast<int>(i)};
                    bestMove["board"] = combination;
                }
            }
        }
    }

    return bestMove;
}

// Function to decide the card to throw
int HeuristicAi::throwStrategy(vector<Card> hand) {
    int minCard = 0;
    for (size_t i = 1; i < hand.size(); i++) {
        if (hand[minCard].getNumberCard() > hand[i].getNumberCard()) {
            minCard = i;
        }
    }

    return minCard;
}

// Run AI logic
void HeuristicAi::run(engine::Engine *eng) {
    State &state = eng->getState();
    Player &player = eng->getActualPlayer();
    vector<Card> hand = player.getHoldCard();
    vector<Card> cardsOnBoard = state.getBoard()->getCardBoard();

    if (!state.getBoard() || hand.empty()) {
        return;
    }

    map<string, vector<int>> vals;

    // Checking Chkobba
    cout << "Checking Chkobba..." << endl;
    vals = checkPossibleChkoba(hand, cardsOnBoard);
    if (!vals["hand"].empty() && !vals["board"].empty()) {
        cout << "Chkobba condition passed!" << endl;
        int cardIndex = vals["hand"][0];  // Indice de la carte choisie
        cout << "Captured card from hand: " << hand[cardIndex].getNumberCard() << endl;

        cout << "Captured cards from board: ";
        for (int boardIndex : vals["board"]) {
            cout << cardsOnBoard[boardIndex].getNumberCard() << " ";
        }
        cout << endl;

        CaptureCard captureAction(cardIndex, vals["board"]);
        eng->setActualCmd(&captureAction);
        captureAction.execute(eng);
        return;
    }

// Checking Seven of Diamonds
cout << "Checking Seven of Diamonds..." << endl;
vals = checkPossible7Carreau(hand, cardsOnBoard);
if (!vals["hand"].empty() && !vals["board"].empty()) {
    cout << "Seven of Diamonds condition passed!" << endl;

    int cardIndex = vals["hand"][0];  // Indice de la carte choisie dans la main
    cout << "Captured card from hand: " << hand[cardIndex].getNumberCard() << endl;

    cout << "Captured cards from board: ";
    for (int boardIndex : vals["board"]) {
        cout << cardsOnBoard[boardIndex].getNumberCard() << " ";
    }
    cout << endl;

    CaptureCard captureAction(cardIndex, vals["board"]);
    eng->setActualCmd(&captureAction);
    captureAction.execute(eng);
    return;
}


    // Maximizing profit
    cout << "Maximizing profit..." << endl;
    vals = maximiseProfit(hand, cardsOnBoard);
    if (!vals["hand"].empty() && !vals["board"].empty()) {
        cout << "Maximize profit condition passed!" << endl;
        int cardIndex = vals["hand"][0];  // Indice de la carte choisie
        cout << "Captured card from hand: " << hand[cardIndex].getNumberCard() << endl;

        cout << "Captured cards from board: ";
        for (int boardIndex : vals["board"]) {
            cout << cardsOnBoard[boardIndex].getNumberCard() << " ";
        }
        cout << endl;

        CaptureCard captureAction(cardIndex, vals["board"]);
        eng->setActualCmd(&captureAction);
        captureAction.execute(eng);
        return;
    }

    // Throw a card if no other condition is met
    int throwCard = throwStrategy(hand);
    int x = hand.size();
    if (throwCard >= 0 && throwCard < x) {
        ThrowCard throwAction(throwCard);
        eng->setActualCmd(&throwAction);
        throwAction.execute(eng);
        cout << "I threw a card: " << hand[throwCard].getNumberCard() << endl;
    } else {
        cout << "No valid cards to throw. Ending turn." << endl;
    }
}


// Destructor
HeuristicAi::~HeuristicAi() {}
