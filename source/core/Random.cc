#include "Random.h"

#include <random>


unsigned int Random::_seed(0);
std::mt19937 Random::_generator;
std::uniform_real_distribution<double> Random::_unif(0, 1.0);


void Random::setSeed(unsigned int seed)
{
    _seed = seed;
    _generator.seed(_seed);
}


double Random::uniform()
{
    return _unif(_generator);
}


double Random::uniform(double a, double b)
{
    return a + uniform() * (b - a);
}


bool Random::trueWithProbability(double p)
{
    return uniform() < p;
}
