#pragma once

#include "UserInterface.h"
#include "Node.h"
#include <vector>

using namespace std;

class IsolationEngine
{
public:
	IsolationEngine();
	~IsolationEngine();
	void Start();
    vector<Node> GetSuccessors(Node n);

private: 
	UserInterface ui;
	void GameLoop();
	void ComputerTurn();
	void AdversaryTurn();
};
