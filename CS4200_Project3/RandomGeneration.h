#pragma once
#include <random>

using std::default_random_engine;

class RandomGeneration
{
public:
	RandomGeneration();
	int RandomZeroToN(int n);

private:
	default_random_engine rng;
};

