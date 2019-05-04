#include "IsolationEngine.h"
#include <limits>
#include <array>

const int ROW_COUNT = 8;
using std::array;
using std::numeric_limits;

IsolationEngine::IsolationEngine()
{
    currentPlayer = &*computer;
}

void IsolationEngine::Start()
{
    // initialize game engine
    int timeout = ui.GetTimeLimit();
    computer = make_unique<MiniMax>(this, timeout);
    opponent = make_unique<Opponent>(&ui, this);
    bool computerStarts = ui.ComputerStarts();
    SwitchTurns(!computerStarts);
    GameLoop(GetInitialBoard(computerStarts));
}

Node IsolationEngine::GetInitialBoard(bool computerStarts)
{
    array<array<char, 8>, 8> state;
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < ROW_COUNT; j++)
        {
            state[i][j] = '-';
        }
    }

    char startChar = computerStarts ? 'X' : 'O';
    char otherChar = computerStarts ? 'O' : 'X';
    state[0][0] = startChar;
    state[7][7] = otherChar;
    return Node(state, computerStarts, { -1 });
}

void IsolationEngine::GameLoop(Node initialState)
{
    Node currentState = initialState;

    while (true)
    {
        currentState = currentPlayer->GetMove(currentState);

        // only display UI after computer moves
        if (!currentState.ComputerTurnNext())
        {
            ui.DisplayBoard(currentState);
        }

        SwitchTurns(!currentState.ComputerTurnNext());
    }
}

void IsolationEngine::SwitchTurns(bool opponentTurnNext)
{
    if (opponentTurnNext)
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
    char player = current.ComputerTurnNext() ? 'X' : 'O';
    array<array<char, 8>, 8> newState = current.GetState();
    newState[currentX][currentY] = '#';
    newState[newX][newY] = player;
    return Node(newState, !current.ComputerTurnNext(), { newX, newY });
}

void IsolationEngine::FindActivePlayer(Node n, int& x, int& y)
{
    char player = n.ComputerTurnNext() ? 'X' : 'O';
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
        return numeric_limits<int>::max();
    }

    // This is a theoretical state where it is this player's move again.
    // This allows us to estimate how many move options this player would have.
    Node alternateMove = Node(n.GetState(), !n.ComputerTurnNext(), n.LastMove());
    int thisPlayersOptions = GetSuccessors(alternateMove).size();

    if (thisPlayersOptions == 0)
    {
        return numeric_limits<int>::min();
    }

    // use heuristic

}

//bool IsolationEngine::TerminalTest(Node n)
//{
//
//}



