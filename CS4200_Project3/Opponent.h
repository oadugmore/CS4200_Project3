#pragma once

#include "Player.h"
#include "Node.h"
#include "UserInterface.h"
#include "GameEngine.h"

class Opponent : public Player
{
public:
	Opponent(UserInterface* ui, GameEngine* engine);
	Node GetMove(Node currentState) override;
	~Opponent();

private:
	UserInterface* ui;
    GameEngine* engine;
};
