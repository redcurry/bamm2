#include <iostream>
#include "Random.h"
#include "TestModel.h"
#include "TestModelProposal.h"
#include "MCMC.h"

int main(int argc, char *argv[])
{
  int seed = std::atoi(argv[1]);
  int numSteps = std::atoi(argv[2]);

  Random::setSeed(std::atoi(argv[1]));
  TestModel* model = new TestModel(10, 10.0);

  MCMC mcmc;
  mcmc.run(model, numSteps, std::cout);

  delete model;

  return 0;
}
