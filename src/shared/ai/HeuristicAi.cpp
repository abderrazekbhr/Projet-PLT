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
HeuristicAi::HeuristicAi(string name) : AI(name)
{
}

// Utility function to calculate the sum of card values
int cardSum(vector<Card> &cards, vector<int> &indices)
{
    int sum = 0;
    for (int i : indices)
    {
        sum += cards[i].getNumberCard();
    }
    return sum;
}

int cardSum(vector<Card> &cards)
{
    int sum = 0;
    for (auto &card : cards)
    {
        sum += card.getNumberCard();
    }
    return sum;
}

// Function to find all combinations of indices from a vector
void findCombinationsIndices(vector<int> &indices, vector<vector<int>> &result, vector<int> &tempCombination, size_t start)
{
    result.push_back(tempCombination); // Add current combination
    for (size_t i = start; i < indices.size(); ++i)
    {
        tempCombination.push_back(indices[i]);
        findCombinationsIndices(indices, result, tempCombination, i + 1);
        tempCombination.pop_back();
    }
}

// Helper function to find the index of Sept Dinari in a card set
int findSeptDinari(vector<Card> &cards)
{
    for (size_t i = 0; i < cards.size(); ++i)
    {
        if (cards[i].getNumberCard() == 7 && cards[i].getTypeCard() == carreau)
        {
            return i;
        }
    }
    return -1; // Not found
}

// Function to find possible moves for Chkobba
std::map<std::string, std::vector<int>> HeuristicAi::checkPossibleChkoba(std::vector<state::Card> hand, std::vector<state::Card> cardsOnBoard)
{
    map<string, vector<int>> result;

    // Iterate through cards in hand
    for (size_t i = 0; i < hand.size(); ++i)
    {
        Card &chosenCard = hand[i];
        if (cardSum(cardsOnBoard) == chosenCard.getNumberCard())
        {
            // Return the indices of the chosen card and all cards on the board
            result["hand"] = {(int)i};
            result["board"].resize(cardsOnBoard.size());
            iota(result["board"].begin(), result["board"].end(), 0); // All indices on the board
            return result;
        }
    }
    return result; // Return empty if no valid move
}

// Function to find possible moves for Sept Dinari
std::map<std::string, std::vector<int>> HeuristicAi::checkPossible7Carreau(std::vector<state::Card> hand, std::vector<state::Card> cardsOnBoard)
{
    map<string, vector<int>> vals;

    int handIndex = findSeptDinari(hand);          // Index of Sept Dinari in hand
    int boardIndex = findSeptDinari(cardsOnBoard); // Index of Sept Dinari on board

    // Case 1: Sept Dinari exists in both hand and board
    if (handIndex != -1 && boardIndex != -1)
    {
        vals["hand"] = {handIndex};
        vals["board"] = {boardIndex};
        return vals;
    }

    // Generate indices for combinations on the board
    vector<int> indicesOnBoard(cardsOnBoard.size());
    iota(indicesOnBoard.begin(), indicesOnBoard.end(), 0);

    // Case 2: Sept Dinari in hand and a combination on the board sums to 7
    if (handIndex != -1)
    {
        vector<vector<int>> allCombinations;
        vector<int> combinationTemp;

        findCombinationsIndices(indicesOnBoard, allCombinations, combinationTemp, 0);

        for (auto &combination : allCombinations)
        {
            int sum = 0;
            for (int idx : combination)
            {
                sum += cardsOnBoard[idx].getNumberCard();
            }

            if (sum == 7)
            {
                vals["hand"] = {handIndex};
                vals["board"] = combination;
                return vals;
            }
        }
    }

    return vals; // Return empty if no valid move
}

// Function to determine the best move to maximize profit
std::map<std::string, std::vector<int>> HeuristicAi::maximiseProfit(std::vector<state::Card> hand, std::vector<state::Card> cardsOnBoard)
{
    map<string, vector<int>> bestMove;
    int maxScore = 0;

    vector<int> indicesOnBoard(cardsOnBoard.size());
    iota(indicesOnBoard.begin(), indicesOnBoard.end(), 0);

    for (size_t i = 0; i < hand.size(); ++i)
    {
        Card &chosenCard = hand[i];

        vector<vector<int>> allCombinations;
        vector<int> combinationTemp;

        findCombinationsIndices(indicesOnBoard, allCombinations, combinationTemp, 0);

        for (auto &combination : allCombinations)
        {
            if (cardSum(cardsOnBoard, combination) == chosenCard.getNumberCard())
            {
                int sizeScore = combination.size();
                int dinariCount = 0, septCount = 0;

                for (int idx : combination)
                {
                    if (cardsOnBoard[idx].getTypeCard() == carreau)
                        dinariCount++;
                    if (cardsOnBoard[idx].getNumberCard() == 7)
                        septCount++;
                }

                int totalScore = sizeScore + dinariCount + 2 * septCount;

                if (totalScore > maxScore)
                {
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
int HeuristicAi::throwStrategy(vector<Card> hand)
{
    int minCard = 0;
    for (size_t i = 0; i < hand.size(); i++)
    {
        if (hand[minCard].getNumberCard() > hand[i].getNumberCard())
        {
            minCard = i;
        }
    }

    return minCard;
}

// Run AI logic
void HeuristicAi::run(engine::Engine *eng)
{
    State state = eng->getState();
    Player player = eng->getActualPlayer();
    vector<Card> hand = player.getHoldCard();
    vector<Card> cardsOnBoard = state.getBoard()->getCardBoard();
    map<string, vector<int>> vals = checkPossibleChkoba(hand, cardsOnBoard);
    if (vals["hand"].size() != 0 && vals["board"].size() != 0)
    {
        CaptureCard captureAction(vals["hand"][0], vals["board"]);
    }
    vals = checkPossible7Carreau(hand, cardsOnBoard);
    if (vals["hand"].size() != 0 && vals["board"].size() != 0)
    {
        CaptureCard captureAction(vals["hand"][0], vals["board"]);
    }
    vals = maximiseProfit(hand, cardsOnBoard);
    if (vals["hand"].size() != 0 && vals["board"].size() != 0)
    {
        CaptureCard captureAction(vals["hand"][0], vals["board"]);
    }

    int throwCard = throwStrategy(hand);
    ThrowCard throwAction(throwCard);
    // Execute the throw card logic (implementation dependent)
}

// Destructor
HeuristicAi::~HeuristicAi() {}

// // Case 3: Card in hand > 7 can capture a combination containing Sept Dinari
// if (boardIndex != -1) {
//     for (size_t i = 0; i < hand.size(); ++i) {
//         Card &cardInHand = hand[i];
//         if (cardInHand.getNumberCard() > 7) {
//             int targetSum = cardInHand.getNumberCard() - 7;

//             vector<vector<int>> allCombinations;
//             vector<int> combinationTemp;

//             findCombinationsIndices(indicesOnBoard, allCombinations, combinationTemp, 0);

//             for (auto &combination : allCombinations) {
//                 int sum = 0;
//                 bool containsSeptDinari = false;

//                 for (int idx : combination) {
//                     sum += cardsOnBoard[idx].getNumberCard();
//                     if (idx == boardIndex) {
//                         containsSeptDinari = true;
//                     }
//                 }

//                 if (sum == targetSum && containsSeptDinari) {
//                     vals["hand"] = {static_cast<int>(i)};
//                     vals["board"] = combination;
//                     return vals;
//                 }
//             }
//         }
//     }
// }