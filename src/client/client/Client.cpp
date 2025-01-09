#include "client.h"
#include <iostream>
#include <limits>
#include "ai.h"
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define MAX_SCORE 21
// #define MIN_SCORE 11
#define MIN_SCORE 5

using namespace std;
using namespace client;
using namespace engine;
using namespace ai;

Client::Client()
{
    playWithAi = false;
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
            playWithAi = true;
        }

        std::vector<std::string> playersNames = this->enterPlayersNames(nbPlayer);

        SetUpGame setUpCommand = SetUpGame(nbPlayer, maxScore, playersNames, playerIsIA, level);
        this->engine.setActualCmd(&setUpCommand);
        isValidSetUp = this->engine.runCommand(&this->engine); // Corrected to use engine instance.
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

std::string numberCardToString(state::NumberCard number)
{
    switch (number)
    {
    case state::un:
        return "un";
    case state::deux:
        return "deux";
    case state::trois:
        return "trois";
    case state::quatre:
        return "quatre";
    case state::cinq:
        return "cinq";
    case state::six:
        return "six";
    case state::sept:
        return "sept";
    case state::dame:
        return "dame";
    case state::valet:
        return "valet";
    case state::roi:
        return "roi";
    default:
        return "inconnu";
    }
}

std::string typeCardToString(state::TypeCard type)
{
    switch (type)
    {
    case state::treffle:
        return "treffle";
    case state::carreau:
        return "carreau";
    case state::pique:
        return "pique";
    case state::coeur:
        return "coeur";
    default:
        return "inconnu";
    }
}

void Client::displayHandCards()
{
    state::Player player = engine.getActualPlayer();
    for (size_t i = 0; i < player.getHoldCard().size(); i++)
    {
        std::string cardNumber = numberCardToString(player.getHoldCard()[i].getNumberCard());
        std::string cardType = typeCardToString(player.getHoldCard()[i].getTypeCard());
        std::cout << i << " : " << " [" << cardNumber << " | " << cardType << "]" << std::endl;
    }
}

void Client::displayBoardCards()
{
    state::GameBoard *board = engine.getState().getBoard();
    int i = 0;
    for (state::Card c : board->getCardBoard())
    {
        std::string cardNumber = numberCardToString(c.getNumberCard());
        std::string cardType = typeCardToString(c.getTypeCard());
        std::cout << i << " : " << " [" << cardNumber << " | " << cardType << "]" << std::endl;
        i++;
    }
}

std::vector<std::string> Client::enterPlayersNames(int nbPlayers)
{
    std::vector<std::string> playersNames;
    string name;
    cout << "Enter player " << 1 << " name: ";
    cin >> name;
    playersNames.push_back(name);

    for (int i = 1; i < nbPlayers; i++)
    {
        if (playWithAi)
        {
            cout << "Enter AI " << i + 1 << " name: ";
        }
        else
        {
            cout << "Enter player " << i + 1 << " name: ";
        }
        cin >> name;
        playersNames.push_back(name);
    }
    return playersNames;
}

bool Client::initDistribute()
{

    char response = 'y';
    RoundInitDistributeCards roundInitDistributeCards = RoundInitDistributeCards(response);
    this->engine.setActualCmd(&roundInitDistributeCards);
    return this->engine.runCommand(&this->engine);
}

void Client::distributeCard()
{
    RoundDistributeCards roundDistributeCards = RoundDistributeCards();
    this->engine.setActualCmd(&roundDistributeCards);
    this->engine.runCommand(&this->engine);
}

ActionType Client::chooseAction()
{
    int action;
    bool validInput = false;
    state::Player &player = engine.getActualPlayer();
    RandomAi *ai1 = dynamic_cast<RandomAi *>(&player);
    HeuristicAi *ai2 = dynamic_cast<HeuristicAi *>(&player);
    // Display player's hand and the board

    if (ai1 != nullptr)
    {
        std::cout << "Name of Random AI Player : " << player.getName() << std::endl;

        ai1->run(&engine);
        validInput = true;
    }
    else if (ai2 != nullptr)
    {
        std::cout << "Name of Heuristic AI Player : " << player.getName() << std::endl;
        ai2->run(&engine);
        validInput = true;
    }
    while (!validInput)
    {
        std::cout << std::endl;
        std::cout << "Name of player : " << player.getName() << std::endl;
        cout << "CARDS IN YOUR HAND:" << endl;
        this->displayHandCards();
        std::cout << "\n--------------------------------------\n"
                  << std::endl;
        cout << "CARDS ON THE BOARD:"
             << endl;
        this->displayBoardCards();

        action = this->getValidatedInteger("Choose an action: 1. Throw card 2. Capture card\n");
        if (action == 1 || action == 2)
        {
            validInput = true;
        }
        else
        {
            cout << "Invalid input! Expected a number 1 or 2.\n";
        }
    }
if (action == 1) {
    return Throwing;
}else if (action == 2) {
    return Collecting;
}else {
    return Nothing;
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
    ActionType action = Nothing; // Ensure action type is set before loop
    while (!isValidThrowCard)
    {
        int indexCard = this->enterIndexToThrowedCard();
        ThrowCard throwCard = ThrowCard(indexCard);
        this->engine.setActualCmd(&throwCard);
        isValidThrowCard = this->engine.runCommand(&this->engine);
        if (!isValidThrowCard)
        {
            cout << "Invalid card throw action: This may be caused by an incorrect card index." << endl;
            action = this->chooseAction();
            if (action == Collecting)
            {
                break; // Exit loop and switch to Collecting action
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
    ActionType action = Collecting; // Ensure action type is set before loop
    bool isValidCaptureCard = false;
    while (!isValidCaptureCard)
    {
        int indexOfCardFromHand = this->enterIndexToThrowedCard();
        std::vector<int> indexesOfCardsFromBoard = this->enterIndexesToBeCollectedCards();
        CaptureCard captureCard = CaptureCard(indexOfCardFromHand, indexesOfCardsFromBoard);
        this->engine.setActualCmd(&captureCard);
        isValidCaptureCard = this->engine.runCommand(&this->engine);
        if (!isValidCaptureCard)
        {
            cout << "Invalid card capture action: You must capture a card on the board with the same number as your selected card." << endl;
            action = this->chooseAction();
            if (action == Throwing)
            {
                break; // Exit loop and switch to Collecting action
            }
        }
    }
    if (action == Throwing)
    {
        this->playThrowCard();
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

void Client::countScore() {
    // Appelle la commande CountScore pour calculer les scores
    engine::CountScore countScoreCmd;
    countScoreCmd.execute(&this->engine);

    // Affiche les scores des joueurs actuels
    std::cout << "Current scores:" << std::endl;
    auto players = engine.getState().getAllPlayers();
    for (const auto& player : players) {
        std::cout << "Player: " << player->getName() << ", Score: " << player->getScore() << std::endl;
    }
}


// Appelle la commande EndRound pour attribuer les cartes restantes au dernier gagnant
void Client::endRound()
{
    engine::EndRound endRoundCmd;
    endRoundCmd.execute(&this->engine);
}

// Affiche le gagnant à la fin du jeu
void Client::displayWinner()
{
    auto players = engine.getState().getAllPlayers();
    int maxScore = -1;
    std::string winnerName;

    // Trouver le joueur avec le score maximum
    for (const auto &player : players)
    {
        if (player->getScore() > maxScore)
        {
            maxScore = player->getScore();
            winnerName = player->getName();
        }
    }

    std::cout << " Winner Name : " << winnerName << " with a score of : " << maxScore << " points. Congratulations! " << std::endl;
}

Client::~Client()
{
    delete &engine; // Fixed memory management
}
