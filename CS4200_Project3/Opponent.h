#pragma once

#include "Player.h"
#include "Node.h"
#include "UserInterface.h"
#include "GameEngine.h"

class Opponent : public Player
{
public:
	Opponent(UserInterface* ui, GameEngine* engine);
    shared_ptr<Node> GetMove(shared_ptr<Node> currentState) override;

private:
	UserInterface* ui;
    GameEngine* engine;
};
