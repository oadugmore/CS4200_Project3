#pragma once

#include <memory>
#include <vector>
#include "UserInterface.h"
#include "GameEngine.h"
#include "MiniMax.h"
#include "Opponent.h"

using std::unique_ptr;
using std::vector;

class IsolationEngine : public GameEngine
{
public:
	IsolationEngine();
	~IsolationEngine();
	void Start();
    vector<Node> GetSuccessors(Node n) override;
    int Utility(Node n) override;
    //bool TerminalTest(Node n);
	void FindActivePlayer(Node n, int& x, int& y) override;
	Node Move(Node current, int currentX, int currentY, int newX, int newY) override;

private: 
	UserInterface ui;
	unique_ptr<MiniMax> computer;
	unique_ptr<Opponent> opponent;
	Player* currentPlayer;
    bool IsOccupied(Node n, int x, int y);
    bool PositionExists(int x, int y);
	//bool computerTurn;
	void GameLoop();
	void SwitchTurns(bool computerTurn);
};
