#include <iostream>
#include "IsolationEngine.h"
#include "Node.h"

using std::make_shared;

void testUtility(IsolationEngine* engine)
{
    array<array<char, 8>, 8> state;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            state[i][j] = '#';
        }
    }

    for (int i = 4; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            state[i][j] = '-';
        }
    }

    for (int i = 5; i < 8; i++)
    {
        state[i][2] = '#';
        state[i][4] = '#';
    }

    state[5][3] = 'X';
    state[7][5] = 'O';

    //state[0][0] = startChar;
    //state[7][7] = otherChar;
    array<int, 2> lastMove = { -1 };
    auto node = make_shared<Node>(state, false, lastMove);
    int value = engine->Utility(node, true);
    std::cout << "Value: " << value << std::endl;
}

int main()
{
    std::cout << "Welcome to ISOLATION." << std::endl << std::endl;
	IsolationEngine isolation;
	isolation.Start();
    //testUtility(&isolation);
	return 0;
}
