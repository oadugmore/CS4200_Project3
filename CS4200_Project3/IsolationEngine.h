#pragma once

#include <memory>
#include "UserInterface.h"
#include "GameEngine.h"
#include "MiniMax.h"
#include "Opponent.h"

using namespace std;

class IsolationEngine : public GameEngine
{
public:
	IsolationEngine();
	~IsolationEngine();
	void Start();
    vector<Node> GetSuccessors(Node n);
    int Utility(Node n);
    bool TerminalTest(Node n);

private: 
	UserInterface ui;
	unique_ptr<MiniMax> computer;
	unique_ptr<Opponent> opponent;
	Player* currentPlayer;
	bool computerTurn;
	void GameLoop();
	void SwitchTurns(bool computerTurn);
	void FindPlayer(Node n, int& x, int& y);
	Node Move(Node current, int currentX, int currentY, int newX, int newY);
};
