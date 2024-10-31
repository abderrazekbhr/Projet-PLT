#include <iostream>
#include <vector>
#include <set>
#include "state.h"
#include <limits>
#include <bits/algorithmfwd.h>

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

// getters
int Player::getIdPlayer() { return idPlayer; }
string Player::getName() { return name; }
int Player::getScore() { return totalScore; }
std::vector<Card> Player::getCollectCard() { return collectedCard; }
std::vector<Card> Player::getHoldCard() { return holdedCard; }

// Setters
void Player::setName(std::string name) { this->name = std::move(name); }

void Player::displayCollectCard()
{
    cout << "Collected Cards:" << endl;
    if (collectedCard.empty())
    {
        cout << "Vous n'avez pas de cartes collectées\n"
             << endl;
    }
    else
    {
        for (Card card : collectedCard)
        {
            cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "] ,";
        }
        cout << endl;
    }
}

void Player::displayHoldCard()
{
    cout << "*********** Les cartes dans ta main: ***********" << endl;
    if (holdedCard.empty())
    {
        cout << "*********** Vous ne possédez pas de cartes ***********\n"
             << endl;
    }
    else
    {
        for (Card card : holdedCard)
        {
            cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "] ,";
        }
        cout << endl;
    }
}

void Player::addToScore(int points) { totalScore += points; }

Card Player::selectCardFromHand()
{
    int cardIndex = -1;
    int size = holdedCard.size();
    displayHoldCard();
    cout << "*********** Choisissez une carte à jouer entre 1 et " << size <<" ***********" << endl;

    while (!(cin >> cardIndex) || cardIndex < 1 || cardIndex > size)
    {
        cout << "*********** Entrez un index valide entre 1 et " << size <<" ***********"<< endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return holdedCard[cardIndex - 1];
}

void Player::removeCardFromHand(Card card)
{
    auto it = std::remove_if(holdedCard.begin(), holdedCard.end(),
                             [&](Card &c)
                             { return c.getNumberCard() == card.getNumberCard() && c.getTypeCard() == card.getTypeCard(); });
    if (it != holdedCard.end())
    {
        holdedCard.erase(it);
    }
}

vector<Card> Player::selectCardFromBoard()
{
    vector<Card> selectedCard;
    set<int> cardIndex;
    bool needToSelect = true;
    string answer;
    int boardSize = Game::getGameBoard().getCardBoard().size();

    cout << "*********** Choisissez les cartes de board: ***********" << endl;
    for (Card card : Game::getGameBoard().getCardBoard())
    {
        cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "] ,";
    }
    cout << endl;

    while (needToSelect)
    {
        cout << "*********** Voulez-vous selectionner une carte? (oui/non) ***********" << endl;
        cin >> answer;
        if (answer == "non")
            break;

        int index = -1;
        while (!(cin >> index) || cardIndex.count(index) || index < 0 || index >= boardSize)
        {
            cout << "*********** Entrez un index valide entre 0 et " << boardSize - 1 << " (non déjà sélectionné) ***********" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (!cardIndex.insert(index).second)
        {
            selectedCard.push_back(Game::getGameBoard().getCardBoard()[index]);
        }
        else
        {
            cout << "*********** Cette carte est déjà sélectionnée. ***********" << endl;
        }
    }

    return selectedCard;
}

void Player::play()
{
    cout << "-----------------------------------" << endl;
    cout << "C'est le tour de " << name << endl;
    while (true)
    {
        cout << "*********** selectionner une carte de votre main pour jouer ***********" << endl;
        Card card = selectCardFromHand();
        cout << "*********** selectionner une carte du board pour jouer ***********" << endl;
        vector<Card> selectedCard = selectCardFromBoard();
        int cardNumber = card.getNumberCard();

        bool cardExistInBoard = std::any_of(Game::getGameBoard().getCardBoard().begin(), Game::getGameBoard().getCardBoard().end(),
                                            [&](Card &cd)
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
            for (Card cd : selectedCard)
            {
                sum += cd.getNumberCard();
            }

            if (sum == cardNumber)
            {
                collectedCard.push_back(card);
                removeCardFromHand(card);
                for (Card cd : selectedCard)
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

Player::~Player()
{
    collectedCard.clear();
    holdedCard.clear();
    totalScore = 0;
}
