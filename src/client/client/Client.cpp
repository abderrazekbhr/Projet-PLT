
#include "client.h"
#include <iostream>
#include <limits>
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define MAX_SCORE 21
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
        char playerIsIA = this->wantToPlayWithIA();
        int level = -1;
        if (playerIsIA == 'y' || playerIsIA == 'Y')
        {
            level = this->enterIALevel();
        }
        std::vector<std::string> playersNames = this->enterPlayersNames(nbPlayer);

        SetUpGame setUpCommand = SetUpGame(nbPlayer, maxScore, playersNames, playerIsIA, level);
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

char Client::wantToPlayWithIA()
{
    std::string prompt = "Do you want to play with IA ? (y/n): ";
    int resp = this->getValidatedChar(prompt);
    return resp;
}

int Client::enterMaxScore()
{
    std::string prompt = "Enter the maximum score (11 or 21): ";
    int maxScore = this->getValidatedInteger(prompt);
    return maxScore;
}

int Client::enterIALevel()
{
    std::string prompt = "Enter the level of the AI (1 or 2): ";
    int level = this->getValidatedInteger(prompt);
    return level;
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
    int indexCard = this->getValidatedInteger("Enter the index of the card you wish to play from your hand (indices start from 0): ");
    return indexCard;
}

std::vector<int> Client::enterIndexesToBeCollectedCards()
{
    std::vector<int> indexes;
    bool isDone = false;
    do
    {
        int index = this->getValidatedInteger("Enter the index of the card you wish to collect from the board (indices start from 0): ");
        indexes.push_back(index);
        char response = this->getValidatedChar("Do you want to select another card to collect from the board? (y/n):");
        if (response == 'y' || response == 'Y')
        {
            isDone = true;
        }
        else
        {
            isDone = false;
        }

    } while (isDone);
    return indexes;
}

void Client::playThrowCard()
{
    bool isValidThrowCard = false;
    ActionType action;
    while (!isValidThrowCard)
    {
        int indexCard = this->enterIndexToThrowedCard();
        ThrowCard throwCard = ThrowCard(indexCard);
        this->engine.setActualCmd(&throwCard);
        isValidThrowCard = this->engine.runCommand(&engine);
        if (!isValidThrowCard)
        {
            cout << "Invalid card throw action: This may be caused by an incorrect card index." << endl;
            action = this->chooseAction();
            if (action == Collecting)
            {
                break;
            }
        }
    }
    if (action == Collecting)
    {
        this->playCaptureCard();
    }
}

void Client::playCaptureCard()
{
    bool isValidCaptureCard = false;
    ActionType action;
    while (!isValidCaptureCard)
    {

        int indexOfCardFromHand = this->enterIndexToThrowedCard();
        std::vector<int> indexesOfCardsFromBoard = this->enterIndexesToBeCollectedCards();
        CaptureCard captureCard = CaptureCard(indexOfCardFromHand, indexesOfCardsFromBoard);
        this->engine.setActualCmd(&captureCard);
        isValidCaptureCard = this->engine.runCommand(&engine);
        if (!isValidCaptureCard)
        {
            cout << "Invalid card capture action: This may be caused by an incorrect card index or an invalid card combination for the sum." << endl;
            action = this->chooseAction();
            if (action == Throwing)
            {
                break;
            }
        }
    }
    if (action == Collecting)
    {
        this->playCaptureCard();
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