#pragma once
#include <random>

using namespace std;

class RandomGeneration
{
public:
	RandomGeneration();
	int RandomZeroToN(int n);

private:
	default_random_engine rng;
};

