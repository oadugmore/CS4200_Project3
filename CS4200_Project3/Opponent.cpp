#include "Opponent.h"



Opponent::Opponent(UserInterface* ui, GameEngine * engine)
{
	this->ui = ui;
    this->engine = engine;
}


Opponent::~Opponent()
{
}

Node Opponent::GetMove(Node currentState)
{
	auto move = ui->GetMove();
    int x, y;
    engine->FindActivePlayer(currentState, x, y);
    return engine->Move(currentState, x, y, move[0], move[1]);
}
