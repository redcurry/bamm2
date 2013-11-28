#ifndef RANDOM_H
#define RANDOM_H

#include <random>

// TODO: Refactor this class so it doesn't use static methods;
// could make it a singleton, but one may want multiple instances.

class Random
{
public:

    static void setSeed(unsigned int seed);

    static double uniform();
    static double uniform(double a, double b);

    static bool trueWithProbability(double p);

private:

    static unsigned int _seed;
    static std::mt19937 _generator;
    static std::uniform_real_distribution<double> _unif;
};

#endif
