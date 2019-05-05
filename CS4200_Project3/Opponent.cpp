#include "Opponent.h"
#include <vector>

using std::vector;


Opponent::Opponent(UserInterface* ui, GameEngine * engine)
{
	this->ui = ui;
    this->engine = engine;
}


Opponent::~Opponent()
{
}

shared_ptr<Node> Opponent::GetMove(shared_ptr<Node> currentState)
{
    vector<shared_ptr<Node>> possibleMoves = engine->GetSuccessors(currentState);
    for (;;)
    {
	    auto move = ui->GetMove();
        for (int i = 0; i < possibleMoves.size(); i++)
        {
            if (possibleMoves[i]->LastMove() == move)
            {
                int x, y;
                engine->FindActivePlayer(currentState, x, y);
                return engine->Move(currentState, x, y, move[0], move[1]);
            }
        }
        // move is invalid
        ui->InvalidMove();
    }
    
}
