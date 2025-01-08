
#include "client.h"
#include <iostream>
#include <limits>
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define MAX_SCORE 22
#define MIN_SCORE 11

using namespace std;
using namespace client;
using namespace engine;

Client::Client()
{
    this->engine = engine::Engine();
}

void Client::setUp()
{
    bool isValidSetUp = false;
    while (!isValidSetUp)
    {
        int nbPlayer = this->enterNbPlayer();
        int maxScore = this->enterMaxScore();
        std::vector<std::string> playersNames = this->enterPlayersNames(nbPlayer);
        SetUpGame setUpCommand = SetUpGame(nbPlayer, maxScore, playersNames);
        cout << "Game is set up!" << endl;
        this->engine.setActualCmd(&setUpCommand);
        isValidSetUp = this->engine.runCommand(&engine);
    }
}

int Client::enterNbPlayer()
{
    std::string prompt = "Enter number of players (2 or 4): ";
    int nbPlayer = this->getValidatedInteger(prompt);
    return nbPlayer;
}

int Client::enterMaxScore()
{
    std::string prompt = "Enter the maximum score (11 or 22): ";
    int maxScore = this->getValidatedInteger(prompt);
    return maxScore;
}

int Client::getValidatedInteger(std::string prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cout << "Invalid input! Expected an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            return value;
        }
    }
}

char Client::getValidatedChar(std::string prompt)
{
    char response;
    bool validInput = false;
    const string VALID_INPUT = "YyNn";
    while (!validInput)
    {
        cout << prompt;
        cin >> response;
        if (cin.fail())
        {
            cout << "Invalid input! Expected a character.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            if (VALID_INPUT.find(response) != string::npos)
            {
                validInput = true;
            }
            else
            {
                cout << "Invalid input! Expected 'y' or 'n'.\n";
            }
        }
    }
    return response;
}

void Client::displayHandCards()
{
    cout << "Your cards are :" << endl;
    state::Player player = engine.getActualPlayer();
    for (size_t i = 0; i < player.getHoldCard().size(); i++)
    {
        cout << i << "[" << player.getHoldCard()[i].getNumberCard() << "|" << player.getHoldCard()[i].getTypeCard() << "]" << endl;
    }
    cout << "--------------------------------------" << endl;
}

void Client::displayBoardCards()
{
    cout << "Cards on the board are :" << endl;
    state::GameBoard *board = engine.getState().getBoard();

    for (state::Card c : board->getCardBoard())
    {
        cout << "[" << c.getNumberCard() << "|" << c.getTypeCard() << "]" << endl;
    }
    cout << "--------------------------------------" << endl;
}

std::vector<std::string> Client::enterPlayersNames(int nbPlayers)
{
    std::vector<std::string> playersNames;
    for (int i = 0; i < nbPlayers; i++)
    {
        string name;
        cout << "Enter player " << i + 1 << " name: ";
        cin >> name;
        playersNames.push_back(name);
    }
    return playersNames;
}

bool Client::initDistribute()
{
    string prompt = "Do you want to gard the keep your first card ? (y/n): ";
    char response = this->getValidatedChar(prompt);
    RoundInitDistributeCards roundInitDistributeCards = RoundInitDistributeCards(response);
    this->engine.setActualCmd(&roundInitDistributeCards);
    return this->engine.runCommand(&engine);
}

void Client::distributeCard()
{
    RoundDistributeCards roundDistributeCards = RoundDistributeCards();
    this->engine.setActualCmd(&roundDistributeCards);
    this->engine.runCommand(&engine);
}

ActionType Client::chooseAction()
{
    int action;
    bool validInput = false;

    while (!validInput)
    {
        action = this->getValidatedInteger("Choose an action: 1. Throw card 2. Capture card\n");
        if (action >= 1 && action <= 2)
        {
            validInput = true;
        }
        else
        {
            cout << "Invalid input! Expected a number  1 or 2."
                 << endl;
        }
    }

    if (action == 1)
    {
        return Throwing;
    }
    else
    {
        return Collecting;
    }
}

int Client::enterIndexToThrowedCard()
{
    int indexCard = this->getValidatedInteger("Enter the index of the card to throw: ");
    return indexCard;
}

std::vector<int> Client::enterIndexesToBeCollectedCards()
{
    std::vector<int> indexes;
    bool isDone = false;
    do
    {
        int index = this->getValidatedInteger("Enter the index of the card to collect: ");
        indexes.push_back(index);
        char response = this->getValidatedChar("Do you want to collect another card? (y/n): ");
        if (response == 'n' || response == 'N')
        {
            isDone = true;
        }

    } while (isDone);
    return indexes;
}

void Client::playThrowCard()
{
    bool isValidThrowCard = false;
    while (!isValidThrowCard)
    {
        int indexCard = this->enterIndexToThrowedCard();
        ThrowCard throwCard = ThrowCard(indexCard);
        this->engine.setActualCmd(&throwCard);
        isValidThrowCard = this->engine.runCommand(&engine);
    }
}

void Client::playCaptureCard()
{
    bool isValidCaptureCard = false;
    while (!isValidCaptureCard)
    {
        int indexOfCardFromHand = this->enterIndexToThrowedCard();
        std::vector<int> indexesOfCardsFromBoard = this->enterIndexesToBeCollectedCards();
        CaptureCard captureCard = CaptureCard(indexOfCardFromHand, indexesOfCardsFromBoard);
        this->engine.setActualCmd(&captureCard);
        isValidCaptureCard = this->engine.runCommand(&engine);
    }
}

bool Client::isEndOfGame()
{
    state::State state = this->engine.getState();
    for (state::Player *player : state.getAllPlayers())
    {
        if (player->getScore() >= state.getMaxScore())
        {
            return true;
        }
    }
    return false;
}

int Client::getNbPlayerAndIA()
{
    state::State currentState = engine.getState();
    return currentState.getNbPlayer();
}

Client::~Client()
{
    // delete &engine;
}