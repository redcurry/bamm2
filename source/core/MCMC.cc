#include "MCMC.h"
#include "Model.h"
#include "ModelProposer.h"
#include "Random.h"


MCMC::MCMC(const Model& initialModel, const ModelProposer& modelProposer) :
    _initialModel(initialModel), _modelProposer(modelProposer)
{
}


// TODO: Need to fix reference vs. pointer
void MCMC::run(int numSteps) const
{
    const Model* model = &initialModel;

    for (int step = 0; step < numSteps; step++)
        // Propose a new model state
        const ModelProposal* proposal = _modelProposer.propose(*model);

        // Accept the proposal with probability "acceptance ratio"
        double acceptanceProb = proposal->acceptanceRatio();
        if (Random::trueWithProbability(acceptanceProb)) {
            model = proposal->accept();
        }

        // Print model parameters
        // TODO: Because there are many kinds of things to print,
        // and each may be printed at different frequencies,
        // create a separate class that prints out info;
        // the class's print method is called here
        if (step % 1000 == 0) {
            log() << *model << "\n";
        }

        delete model;
    }
}


#endif
