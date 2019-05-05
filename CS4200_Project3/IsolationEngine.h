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
    shared_ptr<Node> GetInitialBoard(bool computerStarts);
    vector<shared_ptr<Node>> GetSuccessors(shared_ptr<Node> n) override;
    int Utility(shared_ptr<Node> n, bool forComputer) override;
	void FindActivePlayer(shared_ptr<Node> n, int& x, int& y) override;
    shared_ptr<Node> Move(shared_ptr<Node> current, int currentX, int currentY, int newX, int newY) override;
    bool TerminalTest(shared_ptr<Node> state);

private: 
	UserInterface ui;
	unique_ptr<MiniMax> computer;
	unique_ptr<Opponent> opponent;
	Player* currentPlayer;
    bool IsOccupied(shared_ptr<Node> n, int x, int y);
    bool PositionExists(int x, int y);
    void GameLoop(shared_ptr<Node> initialState);
	void SwitchTurns(bool computerTurn);
};
