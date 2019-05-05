#pragma once

#include "Player.h"
#include "Node.h"
#include "GameEngine.h"
#include <unordered_map>
#include <chrono>
#include <memory>

using std::shared_ptr;
using std::unordered_map;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;

class MiniMax : public Player
{
public:
    MiniMax(GameEngine* gameEngine, int timeout);
	shared_ptr<Node> GetMove(shared_ptr<Node> currentState) override;

private:
    unordered_map<int, shared_ptr<Node>> hashTable;
    GameEngine* gameEngine;
    int movesGenerated;
	bool firstMove;
	int timeout;
    time_point<high_resolution_clock> startTime;
    int AlphaBetaSearch(shared_ptr<Node> currentState, int depth);
    shared_ptr<Node> AlphaBetaRandomBest(shared_ptr<Node> currentState, int depth);
	int MaxValue(shared_ptr<Node> currentState, int alpha, int beta, int depth);
	int MinValue(shared_ptr<Node> currentState, int alpha, int beta, int depth);
	int Max(int a, int b);
	int Min(int a, int b);
	bool TimesUp();
};
