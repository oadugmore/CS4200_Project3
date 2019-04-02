#include "IsolationEngine.h"



IsolationEngine::IsolationEngine()
{
}


IsolationEngine::~IsolationEngine()
{
}

void IsolationEngine::Start()
{
	// initialize game engine

	GameLoop();
}

vector<Node> IsolationEngine::GetSuccessors(Node n)
{
    vector<Node> successors;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

        }
    }

    return successors;
}

void IsolationEngine::GameLoop()
{
    bool gameOver = false;
	if (ui.ComputerStarts())
	{
        ComputerTurn();
	}
    while (!gameOver)
    {
        AdversaryTurn();
        ComputerTurn();
    }
}

void IsolationEngine::ComputerTurn()
{

}

void IsolationEngine::AdversaryTurn()
{
}


