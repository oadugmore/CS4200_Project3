#pragma once

#include <array>
#include <vector>
#include <memory>

using std::vector;
using std::array;
using std::shared_ptr;

class Node
{
public:
    Node(array<array<char, 8>, 8> state, bool computerTurn, array<int, 2> lastMove);
	Node();
    array<array<char, 8>, 8> GetState();
	bool ComputerTurnNext();
	array<int, 2> LastMove();

private:
    array<array<char, 8>, 8> state;
	bool isComputerTurn;
	array<int, 2> lastMove;
};
