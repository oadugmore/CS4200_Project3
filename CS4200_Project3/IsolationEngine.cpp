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
	int timeout = ui.GetTimeLimit();
	computer = make_unique<MiniMax>(this, timeout);
	opponent = make_unique<Opponent>(&ui, this);

	GameLoop();
}

void IsolationEngine::GameLoop()
{
	Node currentState;
	SwitchTurns(ui.ComputerStarts());

	while (true)
	{
		currentState = currentPlayer->GetMove(currentState);
        //if (currentState.)
		ui.DisplayBoard(currentState);
		SwitchTurns(!currentState.IsPlayerTurn());
	}
}

void IsolationEngine::SwitchTurns(bool playerTurnNext)
{
	if (playerTurnNext)
	{
		currentPlayer = &*opponent;
		//computerTurn = true;
	}
	else
	{
		currentPlayer = &*computer;
		//computerTurn = false;
	}
}

vector<Node> IsolationEngine::GetSuccessors(Node n)
{
	vector<Node> successors;
	array<array<char, 8>, 8> state = n.GetState();
	int posX, posY;
	FindActivePlayer(n, posX, posY);

	// check horizontal
	for (int x = 0; x < 8; x++)
	{
		if (!IsOccupied(n, x, posY))
		{
			successors.push_back(Move(n, posX, posY, x, posY));
		}
	}

	// check vertical
	for (int y = 0; y < 8; y++)
	{
		if (!IsOccupied(n, posX, y))
		{
			successors.push_back(Move(n, posX, posY, posX, y));
		}
	}

	// check top right
    int checkX = posX + 1;
    int checkY = posY + 1;
	while (PositionExists(checkX, checkY))
	{
		if (!IsOccupied(n, checkX, checkY))
		{
			successors.push_back(Move(n, posX, posY, checkX, checkY));
		}
		checkX++;
		checkY++;
	}

	// check bottom right
    checkX = posX + 1;
    checkY = posY - 1;
	while (PositionExists(checkX, checkY))
	{
		if (!IsOccupied(n, checkX, checkY))
		{
			successors.push_back(Move(n, posX, posY, checkX, checkY));
		}
		checkX++;
		checkY--;
	}

	// check bottom left
    checkX = posX - 1;
    checkY = posY - 1;
	while (PositionExists(checkX, checkY))
	{
		if (!IsOccupied(n, checkX, checkY))
		{
			successors.push_back(Move(n, posX, posY, checkX, checkY));
		}
		checkX--;
		checkY--;
	}

	// check top left
    checkX = posX - 1;
    checkY = posY + 1;
	while (PositionExists(checkX, checkY))
	{
		if (!IsOccupied(n, checkX, checkY))
		{
			successors.push_back(Move(n, posX, posY, checkX, checkY));
		}
		checkX--;
		checkY++;
	}

	return successors;
}

bool IsolationEngine::PositionExists(int x, int y)
{
	return (x < 8 && x > -1 && y < 8 && y > -1);
}

Node IsolationEngine::Move(Node current, int currentX, int currentY, int newX, int newY)
{
	char player = current.IsPlayerTurn() ? 'X' : 'O';
	array<array<char, 8>, 8> newState = current.GetState();
	newState[currentX][currentY] = '#';
	newState[newX][newY] = player;
	return Node(newState, !current.IsPlayerTurn(), { newX, newY });
}

void IsolationEngine::FindActivePlayer(Node n, int& x, int& y)
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

bool IsolationEngine::IsOccupied(Node n, int x, int y)
{
	char value = n.GetState()[x][y];
	return (value == '#' || value == 'X' || value == 'O');
}

int IsolationEngine::Utility(Node n)
{
	int otherPlayersOptions = GetSuccessors(n).size();

	// check if this player won
	if (otherPlayersOptions == 0)
	{
		return INFINITY;
	}

	// This is a theoretical state where it is this player's move again.
	// This allows us to estimate how many move options this player would have.
	Node alternateMove = Node(n.GetState(), !n.IsPlayerTurn(), n.LastMove());
	int thisPlayersOptions = GetSuccessors(alternateMove).size();

	if (thisPlayersOptions == 0)
	{
		return -INFINITY;
	}

	// use heuristic

}

//bool IsolationEngine::TerminalTest(Node n)
//{
//
//}



