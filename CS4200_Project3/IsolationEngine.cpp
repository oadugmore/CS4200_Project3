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

// Initializes the game engine and begins the game.
void IsolationEngine::Start()
{
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
            ui.PrintResults(currentState);
            break;
        }

        SwitchTurns(!currentState->ComputerTurnNext());
    }
}

// Switches the active player.
void IsolationEngine::SwitchTurns(bool opponentTurnNext)
{
    if (opponentTurnNext)
    {
        currentPlayer = &*opponent;
    }
    else
    {
        currentPlayer = &*computer;
    }
}

// Gets a collection of states that can be reached on the next move.
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
}

bool IsolationEngine::TerminalTest(shared_ptr<Node> state)
{
    return GetSuccessors(state).size() == 0;
}

void IsolationEngine::FindActivePlayer(shared_ptr<Node> n, int& row, int& column)
{
    char player = n->ComputerTurnNext() ? 'X' : 'O';
    array<array<char, 8>, 8> state = n->GetState();
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

// Evaluates the state. 'forComputer' specifies if the value should be calculated
// from the point of view of the computer or the opponent.
int IsolationEngine::Utility(shared_ptr<Node> n, bool forComputer)
{
    int otherPlayersOptions = 0, thisPlayersOptions = 0; 
    
    // determine if the successors of this state are 'this' player's options or
    // the other player's options.
    if (forComputer == n->ComputerTurnNext())
    {
        thisPlayersOptions = GetSuccessors(n).size();
    }
    else
    {
        otherPlayersOptions = GetSuccessors(n).size();
    }

    // This is a theoretical state where it is this player's move again.
    // This allows us to estimate how many move options this player has.
    auto alternateMove = make_shared<Node>(n->GetState(), !n->ComputerTurnNext(), n->LastMove());
    
    // determine if the successors of the alternate state are 'this' player's options
    // or the other player's options.
    if (forComputer == alternateMove->ComputerTurnNext())
    {
        thisPlayersOptions = GetSuccessors(alternateMove).size();
    }
    else
    {
        otherPlayersOptions = GetSuccessors(alternateMove).size();
    }

    // check if this player won
    if (otherPlayersOptions == 0)
    {
        return numeric_limits<int>::max();
    }

    // check if this player lost
    if (thisPlayersOptions == 0)
    {
        return numeric_limits<int>::min();
    }

    // not a terminal state, so evaluate based on the number of this player's options compared to
    // the opponent's number of options, giving twice as much weight to the opponent's options.
    int optionScore = thisPlayersOptions - 2 * otherPlayersOptions;

    int row, col;
    auto state = n->GetState();
    FindActivePlayer(forComputer && n->ComputerTurnNext() ? n : alternateMove, row, col);

    int emptySpaces = 0;
    for (int j = col - 1; j < col + 2; j++)
    {
        if (row + 1 < 8 && j > -1 && j < 8 && state[row + 1][j] == '-')
        {
            emptySpaces++;
        }
        if (row - 1 > -1 && j > -1 && j < 8 && state[row - 1][j] == '-')
        {
            emptySpaces++;
        }
    }
    if (col - 1 > -1 && state[row][col - 1] == '-')
    {
        emptySpaces++;
    }
    if (col + 1 < 8 && state[row][col + 1] == '-')
    {
        emptySpaces++;
    }

    int rowDistance = static_cast<int>(abs(3.5f - row));
    int colDistance = static_cast<int>(abs(3.5f - col));
    return optionScore - (rowDistance + colDistance) + emptySpaces;
}
