#pragma once

#include "Player.h"
#include "Node.h"
#include "GameEngine.h"
#include <unordered_map>

using namespace std;

class MiniMax : public Player
{
public:
    MiniMax(GameEngine* gameEngine);
	Node GetMove() override;

private:
    unordered_map<int, Node> hashTable;
    GameEngine* gameEngine;
	bool firstMove;
	Node AlphaBetaSearch(Node currentState, int depth);
	Node AlphaBetaRandomBest(Node currentState, int depth);
	int MaxValue(Node currentState, int alpha, int beta, int depth);
	int MinValue(Node currentState, int alpha, int beta, int depth);
	int Max(int a, int b);
	int Min(int a, int b);
};
