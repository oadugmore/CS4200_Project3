#include "RandomGeneration.h"
#include <iostream>



RandomGeneration::RandomGeneration()
{
	try
	{
		// tries to get a random device in different ways depending on platform.
		// could fail if not supported
		random_device device;

		// mersenne twister engine
		rng = default_random_engine(device());
	}
	catch (exception)
	{
		cout << "random_device not supported on this platform." << endl;
	}
}

// Returns a random integer between 0 and n, inclusive.
int RandomGeneration::RandomZeroToN(int n)
{
	auto intDist = uniform_int_distribution<int>(0, n);
	return intDist(rng);
}
