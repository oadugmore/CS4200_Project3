#pragma once

#include "UserInterface.h"
#include "GameEngine.h"

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
	bool gameOver;
	void GameLoop();
	void ComputerTurn();
	void AdversaryTurn();
};
