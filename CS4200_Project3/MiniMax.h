#pragma once

#include "Player.h"
#include "Node.h"
#include "GameEngine.h"
#include <unordered_map>
#include <chrono>

using std::unordered_map;
namespace chrn = std::chrono;

class MiniMax : public Player
{
public:
    MiniMax(GameEngine* gameEngine, int timeout);
	Node GetMove(Node currentState) override;

private:
    unordered_map<int, Node> hashTable;
    GameEngine* gameEngine;
	bool firstMove;
	int timeout;
    chrn::time_point<chrn::steady_clock> startTime;
	Node AlphaBetaSearch(Node currentState, int depth);
	Node AlphaBetaRandomBest(Node currentState, int depth);
	int MaxValue(Node currentState, int alpha, int beta, int depth);
	int MinValue(Node currentState, int alpha, int beta, int depth);
	int Max(int a, int b);
	int Min(int a, int b);
	bool TimesUp();
};
