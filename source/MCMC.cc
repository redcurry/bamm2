#include "MCMC.h"
#include "Random.h"
#include "Log.h"


template <typename ModelType>
void MCMC::run(const ModelType& initialModel, int numSteps) const
{
    typedef typename ModelType::Proposal ModelProposalType;

    ModelType model = initialModel;

    while (numSteps-- > 0) {
        ModelProposalType proposal(model);

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
