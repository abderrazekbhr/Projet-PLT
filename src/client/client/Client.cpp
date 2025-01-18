#include "client.h"
#include <iostream>
#include <limits>
#include "ai.h"
#include <unistd.h>
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
        int gameType = 0;
        while (true) {
            std::cout << "Choose the game type:\n";
            std::cout << "1. RandomAI vs HeuristicAI\n";
            std::cout << "2. RandomAI vs RandomAI\n";
            std::cout << "3. HeuristicAI vs HeuristicAI\n";
            std::cout << "4. Player vs AI\n";
            std::cout << "5. Player vs Player\n";
            std::cout << "Enter your choice (1-5): ";
            std::cin >> gameType;

            if (std::cin.fail() || gameType < 1 || gameType > 5) {
                std::cin.clear(); // Réinitialise le flag d'erreur
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore la saisie incorrecte
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            } else {
                break; // Sortie de la boucle si le choix est valide
            }
        }

        int nbPlayer = 2; // Par défaut pour IA vs IA
        int maxScore = this->enterMaxScore();
        char playerIsIA = 'n'; // Par défaut pour IA vs IA
        int level = -1;
        std::vector<std::string> playersNames;

        if (gameType >= 1 && gameType <= 3)
        {
            // Cas IA vs IA
            playerIsIA = 'y';
            if (gameType == 1) // RandomAI vs HeuristicAI
            {
                level = 1; // RandomAI pour le premier joueur
                playersNames = {"RandomAI_1", "HeuristicAI_2"}; // Noms des IA
            }
            else if (gameType == 2) // RandomAI vs RandomAI
            {
                level = 1; // RandomAI pour les deux joueurs
                playersNames = {"RandomAI_1", "RandomAI_2"}; // Noms des IA
            }
            else if (gameType == 3) // HeuristicAI vs HeuristicAI
            {
                level = 2; // HeuristicAI pour les deux joueurs
                playersNames = {"HeuristicAI_1", "HeuristicAI_2"}; // Noms des IA
            }
        }
        else if (gameType == 4)
        {
            // Cas Joueur vs AI
            nbPlayer = this->enterNbPlayer();
            level = this->enterIALevel();
            playWithAi = true;
            playerIsIA = 'w';
            playersNames = this->enterPlayersNames(nbPlayer,level);
        }
        else if (gameType == 5)
        {
            // Cas Joueur vs Joueur
            nbPlayer = this->enterNbPlayer();
            playersNames = this->enterPlayersNames(nbPlayer,level);
        }
        else
        {
            std::cout << "Invalid choice. Please enter a valid option (1-5).\n";
            continue;
        }

        // Création et exécution de la commande SetUpGame
        SetUpGame setUpCommand = SetUpGame(nbPlayer, maxScore, playersNames, playerIsIA, level);
        this->engine.setActualCmd(&setUpCommand);
        isValidSetUp = this->engine.runCommand(&this->engine);
    }
    scene = new render::Scene(engine.getState());
}
int Client::enterNbPlayer()
{
    int nbPlayer = 0;
    while (true)
    {
        std::cout << "Enter number of players (2 or 4): ";
        std::cin >> nbPlayer;

        // Vérification de la validité de la saisie
        if (std::cin.fail() || (nbPlayer != 2 && nbPlayer != 4))
        {
            std::cin.clear(); // Réinitialise le flag d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore les caractères restants dans le buffer
            std::cout << "Invalid input. Please enter 2 or 4.\n";
        }
        else
        {
            break; // Sortie de la boucle si la saisie est valide
        }
    }
    return nbPlayer;
}


char Client::wantToPlayWithIA()
{
    std::string prompt = "Do you want to play with IA ? (y/n): ";
    int resp = this->getValidatedChar(prompt);
    return resp;
}

int Client::enterMaxScore() {
    int maxScore;
    while (true) {
        std::cout << "Enter the maximum score (4 or 11): ";
        std::cin >> maxScore;

        if (std::cin.fail()) {
            std::cin.clear(); // Réinitialise le flag d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore la saisie incorrecte
            std::cout << "Invalid input. Please enter a valid number.\n";
        } else if (maxScore == 4 || maxScore == 11) {
            return maxScore; // Valeur valide, on retourne
        } else {
            std::cout << "Invalid choice. Please enter 4 or 11.\n";
        }
    }
}

int Client::enterIALevel() {
    int level;
    while (true) {
        std::cout << "Enter the level of the AI (1 or 2): ";
        std::cin >> level;

        if (std::cin.fail()) {
            std::cin.clear(); // Réinitialise le flag d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore la saisie incorrecte
            std::cout << "Invalid input. Please enter a valid number.\n";
        } else if (level == 1 || level == 2) {
            return level; // Valeur valide, on retourne
        } else {
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }
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

std::vector<std::string> Client::enterPlayersNames(int nbPlayers,int level)
{
    std::vector<std::string> playersNames;
    std::string name;

    // Demander le nom pour le premier joueur (toujours humain)
    std::cout << "Enter player " << 1 << " name: ";
    std::cin >> name;
    playersNames.push_back(name);

    // Ajouter les autres joueurs (IA ou humains)
    for (int i = 1; i < nbPlayers; i++)
    {
        if (playWithAi)
        {
            // Assigner un nom par défaut selon le niveau
            if (level == 1)
            {
                name = "RandomAI_" + std::to_string(i);
            }
            else if (level == 2)
            {
                name = "HeuristicAI_" + std::to_string(i);
            }

            // Afficher un message pour informer l'utilisateur
            std::cout << "AI " << i + 1 << " assigned name: " << name << std::endl;
        }
        else
        {
            // Demander un nom pour un joueur humain
            std::cout << "Enter player " << i + 1 << " name: ";
            std::cin >> name;
        }

        // Ajouter le nom à la liste
        playersNames.push_back(name);
    }

    return playersNames;
}

bool Client::initDistribute()
{
    char response = 'y';
    RoundInitDistributeCards roundInitDistributeCards = RoundInitDistributeCards(response);
    this->engine.setActualCmd(&roundInitDistributeCards);
    cout << "player name :" << engine.getActualPlayer().getName() << " | nb card :" << engine.getActualPlayer().getSizeHoldedCards() << endl;

    bool execResult = this->engine.runCommand(&this->engine);

    return execResult;
}

void Client::distributeCard()
{
    RoundDistributeCards roundDistributeCards = RoundDistributeCards();
    this->engine.setActualCmd(&roundDistributeCards);
    this->engine.runCommand(&this->engine);
}

ActionType Client::chooseAction()
{
    int action = -1; // Initialize action with an invalid value
    state::Player &player = engine.getActualPlayer();
    RandomAi *ai1 = dynamic_cast<RandomAi *>(&player);
    HeuristicAi *ai2 = dynamic_cast<HeuristicAi *>(&player);

    // Handle AI players
    if (ai1 != nullptr)
    {
        std::cout << "\nName of Random AI Player: " << player.getName() << std::endl;
        this->displayBoardCards(); // Display the board after AI action

        ai1->run(&engine); // Corrected to pass engine pointer
        return Nothing;    // AI has no action prompt for human input
    }
    else if (ai2 != nullptr)
    {
        std::cout << "\nName of Heuristic AI Player: " << player.getName() << std::endl;
        this->displayBoardCards(); // Display the board after AI action
        ai2->run(&engine); // Corrected to pass engine pointer
        return Nothing;    // AI has no action prompt for human input
    }

    // For human players, prompt for an action
    while (true)
    {
        std::cout << "\nName of player: " << player.getName() << std::endl;

        std::cout << "CARDS IN YOUR HAND:" << std::endl;

        this->displayHandCards();

        std::cout << "\n--------------------------------------\n"
                  << std::endl;

        std::cout << "CARDS ON THE BOARD:" << std::endl;
        this->displayBoardCards();
        std::cout << std::endl;

        // Prompt for action
        action = this->getValidatedInteger("Choose an action: 1. Throw card 2. Capture card\n");

        if (action == 1)
        {
            return Throwing;
        }
        else if (action == 2)
        {
            return Collecting;
        }
        else
        {
            std::cout << "Invalid input! Expected 1 (Throw card) or 2 (Capture card).\n";
        }
    }
}

int Client::enterIndexToThrowedCard()
{
    int indexCard = this->getValidatedInteger("Enter the index of the card you wish to play from your hand (indices start from 0): ");
    return indexCard;
}

std::vector<int> Client::enterIndexesToBeCollectedCards(int indexOfCardFromHand)
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
        scene->drawScene(indexCard, {});
        sleep(1);
        ThrowCard throwCard = ThrowCard(indexCard);
        this->engine.setActualCmd(&throwCard);
        isValidThrowCard = this->engine.runCommand(&this->engine);
        if (!isValidThrowCard)
        {
            scene->drawScene(-1, {});

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
        scene->drawScene(indexOfCardFromHand, {});
        std::vector<int> indexesOfCardsFromBoard = this->enterIndexesToBeCollectedCards(indexOfCardFromHand);
        scene->drawScene(indexOfCardFromHand, indexesOfCardsFromBoard);
        sleep(1);
        CaptureCard captureCard = CaptureCard(indexOfCardFromHand, indexesOfCardsFromBoard);

        this->engine.setActualCmd(&captureCard);
        isValidCaptureCard = this->engine.runCommand(&this->engine);
        if (!isValidCaptureCard)
        {
            scene->drawScene(-1, {});
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

void Client::countScore()
{
    // Appelle la commande CountScore pour calculer les scores
    engine::CountScore countScoreCmd;
    countScoreCmd.execute(&this->engine);

    // Affiche les scores des joueurs actuels
    std::cout << "Current scores:" << std::endl;
    auto players = engine.getState().getAllPlayers();
    for (const auto &player : players)
    {
        std::cout << "Player: " << player->getName() << ", Score: " << player->getScore() << std::endl;
    }
}

// Appelle la commande EndRound pour attribuer les cartes restantes au dernier gagnant
void Client::endRound()
{
    engine::EndRound endRoundCmd;
    endRoundCmd.execute(&this->engine);
}

void Client::displayWinner()
{
    auto players = engine.getState().getAllPlayers();
    int maxScoreWin = -1;
    std::string winnerName;
    int countMaxScore = 0;

    // Trouver le score maximum et compter les joueurs ayant ce score
    for (const auto &player : players)
    {
        if (player->getScore() > maxScoreWin)
        {
            maxScoreWin = player->getScore();
            winnerName = player->getName();
            countMaxScore = 1; // Réinitialiser le compteur
        }
        else if (player->getScore() == maxScoreWin)
        {
            countMaxScore++; // Incrémenter le compteur en cas d'égalité
        }
    }

    // Vérifier si le cas d'égalité existe
    if (countMaxScore > 1)
    {
        std::cout << "End of game !! Equality!!"
                  << std::endl;
    }
    else
    {
        std::cout << "Winner Name : " << winnerName
                  << " with a score of : " << maxScoreWin << " points. Congratulations!"
                  << std::endl;
    }
}

Client::~Client()
{
    // delete &engine; // Fixed memory management
}
