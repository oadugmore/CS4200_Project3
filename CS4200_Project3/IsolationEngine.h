#pragma once
#include "GameEngine.h"
#include "UserInterface.h"
#include "MiniMax.h"
#include "Opponent.h"
#include <memory>
#include <vector>

using std::unique_ptr;
using std::make_unique;
using std::vector;

class IsolationEngine : public GameEngine
{
public:
	IsolationEngine();
	void Start();
    Node GetInitialBoard(bool computerStarts);
    vector<Node> GetSuccessors(Node n) override;
    int Utility(Node n) override;
	void FindActivePlayer(Node n, int& x, int& y) override;
	Node Move(Node current, int currentX, int currentY, int newX, int newY) override;
    bool TerminalTest(Node state);

private: 
	UserInterface ui;
	unique_ptr<MiniMax> computer;
	unique_ptr<Opponent> opponent;
	Player* currentPlayer;
    bool IsOccupied(Node n, int x, int y);
    bool PositionExists(int x, int y);
    void GameLoop(Node initialState);
	void SwitchTurns(bool computerTurn);
};
