#include <iostream>
#include <vector>
#include <set>
#include "state.h"
#include <limits>
#include <algorithm> // For std::remove_if and std::any_of

using namespace state;
using namespace std;

int nbPlayerInstance = 0;

Player::Player()
{
    nbPlayerInstance++;
    idPlayer = nbPlayerInstance;
    name = "Player " + to_string(idPlayer);
    totalScore = 0;
}

// Getters
// Returns the ID of the player
int Player::getIdPlayer() { return idPlayer; }

// Returns the name of the player
string Player::getName() { return name; }

// Returns the total score of the player
int Player::getScore() { return totalScore; }

// Returns the list of collected cards
std::vector<Card> Player::getCollectCard() { return collectedCard; }

// Returns the list of held cards
std::vector<Card> Player::getHoldCard() { return holdedCard; }

// Setters
// Sets the name of the player
void Player::setName(std::string name) { this->name = std::move(name); }

// Displays the collected cards of the player
void Player::displayCollectCard()
{
    cout << "Collected Cards:" << endl;
    if (collectedCard.empty())
    {
        cout << "Vous n'avez pas de cartes collectées\n" << endl;
    }
    else
    {
        for ( Card& card : collectedCard) // Use const reference for efficiency
        {
            cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "] ,";
        }
        cout << endl;
    }
}

// Displays the cards held in hand by the player
void Player::displayHoldCard()
{
    cout << "*********** Les cartes dans ta main: ***********" << endl;
    if (holdedCard.empty())
    {
        cout << "*********** Vous ne possédez pas de cartes ***********\n" << endl;
    }
    else
    {
        for ( Card& card : holdedCard) // Use const reference for efficiency
        {
            cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "] ,";
        }
        cout << endl;
    }
}

// Adds points to the player's total score
void Player::addToScore(int points) { totalScore += points; }

// Prompts the player to select a card from their hand
Card Player::selectCardFromHand()
{
    int cardIndex = -1;
    int size = holdedCard.size();
    displayHoldCard();
    cout << "*********** Choisissez une carte à jouer entre 1 et " << size << " ***********" << endl;

    while (!(cin >> cardIndex) || cardIndex < 1 || cardIndex > size)
    {
        cout << "*********** Entrez un index valide entre 1 et " << size << " ***********" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return holdedCard[cardIndex - 1]; // Adjust for 0-based index
}

// Removes a specified card from the player's hand
void Player::removeCardFromHand(Card card)
{
    auto it = std::remove_if(holdedCard.begin(), holdedCard.end(),
                             [&]( Card& c) // Use const reference
                             {
                                 return c.getNumberCard() == card.getNumberCard() &&
                                        c.getTypeCard() == card.getTypeCard();
                             });

    holdedCard.erase(it, holdedCard.end()); // Use erase-remove idiom
}

// Prompts the player to select cards from the game board
vector<Card> Player::selectCardFromBoard()
{
    vector<Card> selectedCard;
    set<int> cardIndex;
    bool needToSelect = true;
    string answer;
    int boardSize = Game::getGameBoard().getCardBoard().size();

    cout << "*********** Choisissez les cartes de board: ***********" << endl;
    for ( Card& card : Game::getGameBoard().getCardBoard()) // Use const reference
    {
        cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "] ,";
    }
    cout << endl;

    while (needToSelect)
    {
        cout << "*********** Voulez-vous selectionner une carte? (oui/non) ***********" << endl;
        cin >> answer;
        if (answer == "non") break;

        int index = -1;
        while (!(cin >> index) || cardIndex.count(index) || index < 0 || index >= boardSize)
        {
            cout << "*********** Entrez un index valide entre 0 et " << boardSize - 1
                 << " (non déjà sélectionné) ***********" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cardIndex.insert(index); // Insert directly
        selectedCard.push_back(Game::getGameBoard().getCardBoard()[index]);
    }

    return selectedCard; // Returns the selected cards
}

// Handles the player's turn and manages the game logic for playing a card
void Player::play()
{
    cout << "-----------------------------------" << endl;
    cout << "C'est le tour de " << name << endl;

    while (true)
    {
        cout << "*********** sélectionnez une carte de votre main pour jouer ***********" << endl;
        Card card = selectCardFromHand();
        cout << "*********** sélectionnez une carte du board pour jouer ***********" << endl;
        vector<Card> selectedCard = selectCardFromBoard();
        int cardNumber = card.getNumberCard();

        bool cardExistInBoard = std::any_of(Game::getGameBoard().getCardBoard().begin(),
                                            Game::getGameBoard().getCardBoard().end(),
                                            [&]( Card& cd) // Use const reference
                                            { return cd.getNumberCard() == cardNumber; });

        if (cardExistInBoard)
        {
            if (selectedCard.size() == 1 && selectedCard[0].getNumberCard() == cardNumber)
            {
                collectedCard.push_back(card);
                removeCardFromHand(card);
                Game::getGameBoard().deleteCardFrom(selectedCard[0]);

                if (holdedCard.empty())
                {
                    cout << "*********** Vous avez une CHKOBA ***********" << endl;
                    addToScore(1);
                }
                break;
            }
            else
            {
                cout << "*********** Le nombre de cette carte est déjà dans le board; il faut le prendre. ***********" << endl;
            }
        }
        else if (selectedCard.empty())
        {
            Game::getGameBoard().addCardToBoard(card);
            removeCardFromHand(card);
            break;
        }
        else
        {
            int sum = 0;
            for ( Card& cd : selectedCard) // Use const reference
            {
                sum += cd.getNumberCard();
            }

            if (sum == cardNumber)
            {
                collectedCard.push_back(card);
                removeCardFromHand(card);
                for ( Card& cd : selectedCard) // Use const reference
                {
                    collectedCard.push_back(cd);
                    Game::getGameBoard().deleteCardFrom(cd);
                }
                break;
            }
            else
            {
                cout << "*********** La somme des cartes sélectionnées n'est pas égale à la carte choisie. ***********" << endl;
            }
        }
    }
}

// Destructor that cleans up player data
Player::~Player()
{
    collectedCard.clear();
    holdedCard.clear();
    totalScore = 0;
}
