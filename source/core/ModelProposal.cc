#include "ModelProposal.h"
#include "Model.h"

#include <algorithm>


ModelProposal::ModelProposal(const Model* model) : _model(model)
{
}


ModelPoprosal::~ModelProposal()
{
}


double ModelProposal::acceptanceRatio() const
{
    return std::min(1.0, productOfRatios());
}
