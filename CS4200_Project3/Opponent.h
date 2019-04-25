#pragma once

#include "Player.h"
#include "UserInterface.h"

class Opponent : public Player
{
public:
	Opponent(UserInterface* ui);
	Node GetMove(Node currentState) override;
	~Opponent();

private:
	UserInterface* ui;
};
