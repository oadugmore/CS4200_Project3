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
	array<array<char, 8>, 8> state = n.GetState();
	int posX, posY;
	findPlayer(n, posX, posY);

	// check top right
	int checkX = posX + 1, checkY = posY + 1;
	while (positionExists(checkX, checkY))
	{
		if (!isOccupied(n, checkX, checkY))
		{
			successors.push_back(move(n, posX, posY, checkX, checkY));
		}
		checkX++;
		checkY++;
	}

	// check bottom right
	int checkX = posX + 1, checkY = posY - 1;
	while (positionExists(checkX, checkY))
	{
		if (!isOccupied(n, checkX, checkY))
		{
			successors.push_back(move(n, posX, posY, checkX, checkY));
		}
		checkX++;
		checkY--;
	}

	// check bottom left
	int checkX = posX - 1, checkY = posY - 1;
	while (positionExists(checkX, checkY))
	{
		if (!isOccupied(n, checkX, checkY))
		{
			successors.push_back(move(n, posX, posY, checkX, checkY));
		}
		checkX--;
		checkY--;
	}

	// check top left
	int checkX = posX - 1, checkY = posY + 1;
	while (positionExists(checkX, checkY))
	{
		if (!isOccupied(n, checkX, checkY))
		{
			successors.push_back(move(n, posX, posY, checkX, checkY));
		}
		checkX--;
		checkY++;
	}

    return successors;
}

bool positionExists(int x, int y)
{
	return (x < 8 && x > -1 && y < 8 && y > -1);
}

Node move(Node current, int currentX, int currentY, int newX, int newY)
{
	char player = current.IsPlayerTurn() ? 'X' : 'O';
	array<array<char, 8>, 8> newState = current.GetState();
	newState[currentX][currentY] = '#';
	newState[newX][newY] = player;
	return Node(newState, !current.IsPlayerTurn());
}

void findPlayer(Node n, int& x, int& y)
{
	char player = n.IsPlayerTurn() ? 'X' : 'O';
	array<array<char, 8>, 8> state = n.GetState();
	//int posX, posY;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (state[i][j] == player)
			{
				x = i;
				y = j;
				return;
			}
		}
	}
}

bool isOccupied(Node n, int x, int y)
{
	char value = n.GetState()[x][y];
	return (value == '#' || value == 'X' || value == 'O');
}

int IsolationEngine::Utility(Node n)
{
    return 0;
}

bool IsolationEngine::TerminalTest(Node n)
{
    
}

void IsolationEngine::GameLoop()
{
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


