#include "MCMC.h"
#include "Model.h"
#include "ModelProposal.h"
#include "Random.h"

#include <iostream>
#include <algorithm>
#include <cmath>


template <typename ModelType>
void MCMC::run(const ModelType& initialModel, int numSteps) const
{
    ModelType model = initialModel;

    while (numSteps-- > 0) {
        typename ModelType::Proposal proposal = model.createProposal();

        double acceptanceProb = proposal.acceptanceRatio();
        if (Random::trueWithProbability(acceptanceProb)) {
            proposal.accept();
        }

        // Print model parameters
        if (numSteps % 1000 == 0) {
            log() << model << "\n";
        }
    }
}
