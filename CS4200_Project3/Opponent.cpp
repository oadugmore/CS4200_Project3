#include "Opponent.h"



Opponent::Opponent(UserInterface* ui)
{
	this->ui = ui;
}


Opponent::~Opponent()
{
}

Node Opponent::GetMove(Node currentState)
{
	auto move = ui->GetMove();

}
