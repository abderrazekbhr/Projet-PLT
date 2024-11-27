#include <iostream>
#include <vector>
#include <set>
#include "state.h"
#include <limits>
#include <algorithm> // For std::remove_if and std::any_of

using namespace state;
using namespace std;

Player::Player()
{
    cout << "Enter your name:" << endl;
    cin >> name;
    totalScore = 0;
}

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
void Player::setName(std::string name) { this->name = name; }

// Displays the collected cards of the player
void Player::displayCollectCard()
{
    cout << "Collected Cards:" << endl;
    if (collectedCard.empty())
    {
        cout << "You don't have any collected cards." << endl;
    }
    else
    {
        for (Card &card : collectedCard) // Use const reference for efficiency
        {
            cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "], ";
        }
        cout << endl;
    }
}

// Adds a card to the list of collected cards
void Player::addHoldedCard(Card card)
{
    holdedCard.push_back(card);
}

// Displays the cards held in hand by the player
void Player::displayHoldCard()
{
    cout << "*********** Your Holded Cards: ***********" << endl;
    if (holdedCard.empty())
    {
       cout << "*********** You don't have any cards in your hand. ***********" << endl;
    }
    else
    {
        for (Card &card : holdedCard) // Use const reference for efficiency
        {
            cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "], ";
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
 /*   
    displayHoldCard();

    while (!(cin >> cardIndex) || cardIndex < 1 || cardIndex > size)
    {
        cout << "*********** Choose a card index from your hand between 1 and " << size << " ***********" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
*/
    return holdedCard[cardIndex - 1]; // Adjust for 0-based index
}

// Removes a specified card from the player's hand
void Player::removeCardFromHand(Card card)
{
    auto it = std::remove_if(holdedCard.begin(), holdedCard.end(),
                             [&](Card &c)
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
    int boardSize = Game::getGameBoard()->getCardBoard().size();
    if (boardSize == 0)
    {
        cout << "*********** The board is empty ***********" << endl;
        return selectedCard;
    }

    cout << "*********** Choose a card index from the board between 1 and " << boardSize << " ***********" << endl;
    for (Card &card : Game::getGameBoard()->getCardBoard()) // Use const reference
    {
        cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "], ";
    }
    cout << endl;

    while (needToSelect)
    {
        cout << "*********** Do you want to choose any card from the board? (yes/no) ***********" << endl;
        cin >> answer;
        if (answer == "no")
            break;

        int index = -1;
        while (!(cin >> index) || cardIndex.count(index) || index < 0 || index >= boardSize)
        {
            cout << "*********** Enter a valid index between 0 and " << boardSize - 1 << " (not already selected) ***********" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cardIndex.insert(index); // Insert directly
        
        selectedCard.push_back(Game::getGameBoard()->getCardBoard()[index]);
    }

    return selectedCard; // Returns the selected cards
}

// Handles the player's turn and manages the game logic for playing a card
void Player::play()
{
    cout << "-----------------------------------" << endl;
    cout << "It's " << name << "'s turn." << endl;

    while (true)
    {
        cout << "*********** Select a card from your hand to play ***********" << endl;
        Card card = selectCardFromHand();
        cout << "*********** Select cards from the board to play ***********" << endl;
        vector<Card> selectedCard = selectCardFromBoard();
        int cardNumber = card.getNumberCard();

        if (selectedCard.size() == 1 && selectedCard[0].getNumberCard() == cardNumber)
        {
            collectedCard.push_back(card);
            removeCardFromHand(card);
            Game::getGameBoard()->deleteCard(selectedCard[0]);
            break;
        }

        else if (selectedCard.empty())
        {
            Game::getGameBoard()->addCardToBoard(card);
            removeCardFromHand(card);
            break;
        }
        else
        {
            int sum = 0;
            for (Card &cd : selectedCard)
            {
                sum += cd.getNumberCard();
            }

            if (sum == cardNumber)
            {
                collectedCard.push_back(card);
                removeCardFromHand(card);
                for (const Card &cd : selectedCard)
                {
                    collectedCard.push_back(cd);
                    Game::getGameBoard()->deleteCard(cd);
                }
                break;
            }
            else
            {
                cout << "*********** The sum of selected cards does not match the chosen card number. ***********" << endl;
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
