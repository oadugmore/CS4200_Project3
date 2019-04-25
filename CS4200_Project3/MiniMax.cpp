#include "MiniMax.h"
#include "RandomGeneration.h"


struct TimesUpException : public exception { };

MiniMax::MiniMax(GameEngine* gameEngine, int timeout)
{
    this->gameEngine = gameEngine;
	this->timeout = timeout;
	firstMove = true;
}

// Check if current search has taken more than the set timeout
bool MiniMax::TimesUp()
{
	auto currentTime = chrono::high_resolution_clock::now();
	auto elapsed = currentTime - startTime;
	float seconds = elapsed.count() / 1000000000;
	return (seconds > 19);
}

Node MiniMax::GetMove(Node currentState)
{
	// initialize hash table

	int depth = 1;
	startTime = chrono::high_resolution_clock::now();
	Node bestMove;

	// "if there are multiple optimal moves that result in the same evaluation value,
	// it must randomly choose from those moves"
	// (only reasonably need to do this for the first move)
	if (firstMove)
	{
		try
		{
			while (!TimesUp())
			{
				bestMove = AlphaBetaRandomBest(currentState, depth);
				depth++;
			}
		}
		catch (TimesUpException) {}
	}

	// if not first move, use normal AlphaBetaSearch
	else
	{
		try
		{
			while (!TimesUp())
			{
				bestMove = AlphaBetaSearch(currentState, depth);
				depth++;
			}
		}
		catch (TimesUpException) {}
	}

	return bestMove;
}

// Performs MiniMax search with AlphaBeta pruning,
// and returns the best move found.
Node MiniMax::AlphaBetaSearch(Node currentState, int depth)
{
	vector<Node> successors = gameEngine->GetSuccessors(currentState);

	// terminal test:
	// this is the current state of the board
	// so no need to check depth
	if (successors.empty())
	{
		return currentState;
	}

	int v = INT_MIN;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	for (int i = 0; i < successors.size(); i++)
	{
		int min = MinValue(successors[i], alpha, beta, depth - 1);

		v = Max(v, min);
		if (v >= beta)
			break;
		alpha = Max(alpha, v);
		hashTable[min] = successors[i];
	}

    return hashTable[v];
}

// Performs MiniMax search with AlphaBeta pruning,
// then chooses randomly between the best available moves.
Node MiniMax::AlphaBetaRandomBest(Node currentState, int depth)
{
	vector<Node> successors = gameEngine->GetSuccessors(currentState);
	vector<Node> bestOptions;

	// terminal test: shouldn't be necessary
	// because this is called for the first move
	if (successors.empty())
	{
		return currentState;
	}

	int v = INT_MIN;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	for (int i = 0; i < successors.size(); i++)
	{
		int min = MinValue(successors[i], alpha, beta, depth - 1);

		// if we found a better value than before,
		// clear the old "best" options
		if (min > v)
			bestOptions.clear();

		// if we found a value at least as good as before,
		// add it to the list of best options
		if (min >= v)
			bestOptions.push_back(successors[i]);

		v = Max(v, min);
		alpha = Max(alpha, v);
	}

	// choose randomly between the best options
	RandomGeneration randGen;
	int choice = randGen.RandomZeroToN(bestOptions.size() - 1);
	return bestOptions[choice];
}

int MiniMax::MaxValue(Node currentState, int alpha, int beta, int depth)
{
	if (TimesUp())
		throw TimesUpException();

	vector<Node> successors = gameEngine->GetSuccessors(currentState);

	// terminal test
    if (successors.empty() || depth == 0)
        return gameEngine->Utility(currentState);

    int v = INT_MIN;
    for (int i = 0; i < successors.size(); i++)
    {
        int min = MinValue(successors[i], alpha, beta, depth - 1);
        
        v = Max(v, min);
        if (v >= beta)
			break;
        alpha = Max(alpha, v);
    }
    return v;
}

int MiniMax::MinValue(Node currentState, int alpha, int beta, int depth)
{
	if (TimesUp())
		throw TimesUpException();

	vector<Node> successors = gameEngine->GetSuccessors(currentState);

	// terminal test
	if (successors.empty() || depth == 0)
        return gameEngine->Utility(currentState);

    int v = INT_MIN;
    for (int i = 0; i < successors.size(); i++)
    {
        v = Min(v, MaxValue(successors[i], alpha, beta, depth - 1));
        if (v <= alpha)
			break;
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
