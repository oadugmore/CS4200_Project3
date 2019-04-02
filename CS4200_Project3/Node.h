#pragma once

#include <array>

using namespace std;

class Node
{
public:
    Node();
    ~Node();
    int GetValue();
    array<array<char, 8>, 8> GetState();
    bool IsTerminal();

private:
    array<array<char, 8>, 8> state;
    int value;
    bool isTerminal;

};

