#include "MiniMax.h"
#include <chrono>


MiniMax::MiniMax(GameEngine* gameEngine)
{
    this->gameEngine = gameEngine;
	firstMove = true;
}


Node MiniMax::GetMove()
{
	int depth = 1;
	auto startTime = chrono::high_resolution_clock::now();
	if (firstMove)
	{
		return AlphaBetaRandomBest
	}

}

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
		if (v >= beta) break;
		alpha = Max(alpha, v);
		hashTable[min] = successors[i];
	}

    return hashTable[v];
}

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
	int bestValue = v;
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
		//if (v >= beta)
			//break;
		alpha = Max(alpha, v);
		//hashTable[min] = successors[i];
	}
}

int MiniMax::MaxValue(Node currentState, int alpha, int beta, int depth)
{
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
