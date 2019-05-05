#include "IsolationEngine.h"
#include <limits>
#include <array>
#include <iostream>

const int ROW_COUNT = 8;
using std::array;
using std::numeric_limits;
using std::make_shared;

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

shared_ptr<Node> IsolationEngine::GetInitialBoard(bool computerStarts)
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
    array<int, 2> lastMove = { -1 };
    return make_shared<Node>(state, computerStarts, lastMove);
}

void IsolationEngine::GameLoop(shared_ptr<Node> initialState)
{
    shared_ptr<Node> currentState = initialState;

    while (true)
    {
        currentState = currentPlayer->GetMove(currentState);

        // only display UI after computer moves
        if (!currentState->ComputerTurnNext())
        {
            ui.DisplayBoard(currentState);
        }

        // test if game over
        if (TerminalTest(currentState))
        {
            ui.PrintResults(currentPlayer == &*opponent ? 'O' : 'X');
            break;
        }

        SwitchTurns(!currentState->ComputerTurnNext());
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

vector<shared_ptr<Node>> IsolationEngine::GetSuccessors(shared_ptr<Node> n)
{
    vector<shared_ptr<Node>> successors;
    array<array<char, 8>, 8> state = n->GetState();
    int playerRow, playerColumn;
    FindActivePlayer(n, playerRow, playerColumn);

    // check right
    for (int col = playerColumn + 1; col < 8; col++)
    {
        if (!IsOccupied(n, playerRow, col))
        {
            successors.push_back(Move(n, playerRow, playerColumn, playerRow, col));
        }
        else
        {
            break;
        }
    }

    // check left
    for (int col = playerColumn - 1; col > -1; col--)
    {
        if (!IsOccupied(n, playerRow, col))
        {
            successors.push_back(Move(n, playerRow, playerColumn, playerRow, col));
        }
        else
        {
            break;
        }
    }

    // check up
    for (int row = playerRow - 1; row > -1; row--)
    {
        if (!IsOccupied(n, row, playerColumn))
        {
            successors.push_back(Move(n, playerRow, playerColumn, row, playerColumn));
        }
        else
        {
            break;
        }
    }

    // check down
    for (int row = playerRow + 1; row < 8; row++)
    {
        if (!IsOccupied(n, row, playerColumn))
        {
            successors.push_back(Move(n, playerRow, playerColumn, row, playerColumn));
        }
        else
        {
            break;
        }
    }

    // check top right
    int checkX = playerRow + 1;
    int checkY = playerColumn + 1;
    while (PositionExists(checkX, checkY))
    {
        if (!IsOccupied(n, checkX, checkY))
        {
            successors.push_back(Move(n, playerRow, playerColumn, checkX, checkY));
            checkX++;
            checkY++;
        }
        else
        {
            break;
        }
    }

    // check bottom right
    checkX = playerRow + 1;
    checkY = playerColumn - 1;
    while (PositionExists(checkX, checkY))
    {
        if (!IsOccupied(n, checkX, checkY))
        {
            successors.push_back(Move(n, playerRow, playerColumn, checkX, checkY));
            checkX++;
            checkY--;
        }
        else
        {
            break;
        }
    }

    // check bottom left
    checkX = playerRow - 1;
    checkY = playerColumn - 1;
    while (PositionExists(checkX, checkY))
    {
        if (!IsOccupied(n, checkX, checkY))
        {
            successors.push_back(Move(n, playerRow, playerColumn, checkX, checkY));
            checkX--;
            checkY--;
        }
        else
        {
            break;
        }
    }

    // check top left
    checkX = playerRow - 1;
    checkY = playerColumn + 1;
    while (PositionExists(checkX, checkY))
    {
        if (!IsOccupied(n, checkX, checkY))
        {
            successors.push_back(Move(n, playerRow, playerColumn, checkX, checkY));
            checkX--;
            checkY++;
        }
        else
        {
            break;
        }
    }

    /*for (int i = 0; i < successors.size(); i++)
    {
        std::cout << successors[i].LastMove()[0] << ", " << successors[i].LastMove()[1] << std::endl;
    }*/
    return successors;
}

bool IsolationEngine::PositionExists(int x, int y)
{
    return (x < 8 && x > -1 && y < 8 && y > -1);
}

shared_ptr<Node> IsolationEngine::Move(shared_ptr<Node> current, int currentRow, int currentColumn, int newRow, int newColumn)
{
    char player = current->ComputerTurnNext() ? 'X' : 'O';
    array<array<char, 8>, 8> newState = current->GetState();
    newState[currentRow][currentColumn] = '#';
    newState[newRow][newColumn] = player;
    array<int, 2> lastMove = { newRow, newColumn };
    return make_shared<Node>(newState, !current->ComputerTurnNext(), lastMove);
    //auto node2 = make_shared<Node>(newState, !current->ComputerTurnNext(), { newRow, newColumn });
}

bool IsolationEngine::TerminalTest(shared_ptr<Node> state)
{
    return GetSuccessors(state).size() == 0;
}

void IsolationEngine::FindActivePlayer(shared_ptr<Node> n, int& row, int& column)
{
    char player = n->ComputerTurnNext() ? 'X' : 'O';
    array<array<char, 8>, 8> state = n->GetState();
    //int posX, posY;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (state[i][j] == player)
            {
                row = i;
                column = j;
                return;
            }
        }
    }
}

bool IsolationEngine::IsOccupied(shared_ptr<Node> n, int row, int column)
{
    char value = n->GetState()[row][column];
    return (value == '#' || value == 'X' || value == 'O');
}

int IsolationEngine::Utility(shared_ptr<Node> n)
{
    int otherPlayersOptions = GetSuccessors(n).size();

    // check if this player won
    if (otherPlayersOptions == 0)
    {
        return numeric_limits<int>::max();
    }

    // This is a theoretical state where it is this player's move again.
    // This allows us to estimate how many move options this player has.
    auto alternateMove = make_shared<Node>(n->GetState(), !n->ComputerTurnNext(), n->LastMove());
    int thisPlayersOptions = GetSuccessors(alternateMove).size();

    // check if this player lost
    if (thisPlayersOptions == 0)
    {
        return numeric_limits<int>::min();
    }

    // not a terminal state, so evaluate based on the number of this player's options compared to
    // the opponent's number of options, giving twice as much weight to the opponent's options.
    return thisPlayersOptions - 2 * otherPlayersOptions;

}
