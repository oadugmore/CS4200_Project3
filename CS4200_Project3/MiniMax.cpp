#include "MiniMax.h"
#include "RandomGeneration.h"
#include <limits>
#include <iostream>

struct TimesUpException : public exception { };

MiniMax::MiniMax(GameEngine* gameEngine, int timeout)
{
    this->gameEngine = gameEngine;
    this->timeout = timeout;
    firstMove = true;
    movesGenerated = 0;
}

// Check if current search has taken over (1 second less than) the set timeout.
bool MiniMax::TimesUp()
{
    auto currentTime = high_resolution_clock::now();
    auto elapsed = currentTime - startTime;
    float seconds = elapsed.count() / 1000000000;
    return (seconds > timeout - 1);
}

shared_ptr<Node> MiniMax::GetMove(shared_ptr<Node> currentState)
{
    // initialize hash table
    hashTable.clear();

    movesGenerated++;
    int depth = 0;
    startTime = high_resolution_clock::now();
    int bestMoveValue;

    cout << endl << "Thinking..." << endl;

    // "if there are multiple optimal moves that result in the same evaluation value,
    // it must randomly choose from those moves"
    // (do this for the first 3 moves)
    if (movesGenerated < 4)
    {
        shared_ptr<Node> bestMove(nullptr);
        try
        {
                while (!TimesUp())
            {
                depth++;
                bestMove = AlphaBetaRandomBest(currentState, depth);
            }
        }
        catch (TimesUpException) {}
        return bestMove;
    }

    // use normal AlphaBetaSearch
    else
    {
        try
        {
                while (!TimesUp())
            {
                depth++;
                bestMoveValue = AlphaBetaSearch(currentState, depth);
                if (bestMoveValue <= numeric_limits<int>::min() || bestMoveValue >= numeric_limits<int>::max())
                {
                    cout << endl << "FOUND TERMINAL STATE" << endl;
                    if (bestMoveValue > 0) cout << ";)" << endl;
                    break;
                }
            }
        }
        catch (TimesUpException) {}

        cout << endl << "I searched to a depth of " << depth << endl;
        cout << "and hashed " << hashTable.size() << " options." << endl;

        return hashTable[bestMoveValue];
    }
}

// Performs MiniMax search with AlphaBeta pruning,
// and returns the value of the best move found.
int MiniMax::AlphaBetaSearch(shared_ptr<Node> currentState, int depth)
{
    vector<shared_ptr<Node>> successors = gameEngine->GetSuccessors(currentState);

    // if there are no successors, we lose :(
    if (successors.empty())
    {
        return numeric_limits<int>::min();
    }

    int v = numeric_limits<int>::min();
    int alpha = v;
    constexpr int beta = numeric_limits<int>::max();
    for (int i = 0; i < successors.size(); i++)
    {
        int min = MinValue(successors[i], alpha, beta, depth - 1);
        v = Max(v, min);
        hashTable[min] = successors[i];
        alpha = Max(alpha, v);

        if (v >= beta)
        {
            break;
        }
    }
    cout << "Current value: " << v << endl;
    return v;
}

// Performs MiniMax search with AlphaBeta pruning,
// then chooses randomly between the best available moves.
shared_ptr<Node> MiniMax::AlphaBetaRandomBest(shared_ptr<Node> currentState, int depth)
{
    vector<shared_ptr<Node>> successors = gameEngine->GetSuccessors(currentState);
    vector<shared_ptr<Node>> bestOptions;

    // terminal test: shouldn't be necessary
    // because this is called for the first few moves
    if (successors.empty())
    {
        return currentState;
    }

    int v = numeric_limits<int>::min();
    int alpha = v;
    constexpr int beta = numeric_limits<int>::max();
    for (int i = 0; i < successors.size(); i++)
    {
        int min = MinValue(successors[i], alpha, beta, depth - 1);

        // if we found a better value than before,
        // clear the old "best" options
        if (min > v)
        {
            bestOptions.clear();
        }

        // if we found a value at least as good as before,
        // add it to the list of best options
        if (min >= v)
        {
            bestOptions.push_back(successors[i]);
        }

        v = Max(v, min);
        alpha = Max(alpha, v);
    }

    // choose randomly between the best options
    RandomGeneration randGen;
    int choice = randGen.RandomZeroToN(bestOptions.size() - 1);
    cout << "Current value: " << v << endl;
    return bestOptions[choice];
}

int MiniMax::MaxValue(shared_ptr<Node> currentState, int alpha, int beta, int depth)
{
    if (TimesUp())
    {
        throw TimesUpException();
    }

    vector<shared_ptr<Node>> successors = gameEngine->GetSuccessors(currentState);

    // terminal test
    if (successors.empty() || depth == 0)
    {
        return gameEngine->Utility(currentState, true);
    }

    int v = numeric_limits<int>::min();
    for (int i = 0; i < successors.size(); i++)
    {
        int min = MinValue(successors[i], alpha, beta, depth - 1);
        v = Max(v, min);
        if (v >= beta)
        {
            break;
        }
        alpha = Max(alpha, v);
    }
    return v;
}

int MiniMax::MinValue(shared_ptr<Node> currentState, int alpha, int beta, int depth)
{
    if (TimesUp())
    {
        throw TimesUpException();
    }

    vector<shared_ptr<Node>> successors = gameEngine->GetSuccessors(currentState);

    // terminal test
    if (successors.empty() || depth == 0)
    {
        return gameEngine->Utility(currentState, true);
    }

    int v = numeric_limits<int>::max();
    for (int i = 0; i < successors.size(); i++)
    {
        int max = MaxValue(successors[i], alpha, beta, depth - 1);
        v = Min(v, max);
        if (v <= alpha)
        {
            break;
        }
        beta = Min(beta, v);
    }
    return v;
}

int MiniMax::Max(int a, int b)
{
    return a >= b ? a : b;
}

int MiniMax::Min(int a, int b)
{
    return a <= b ? a : b;
}
