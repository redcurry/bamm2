#include "ModelProposal.h"
#include "Model.h"

#include <algorithm>


ModelProposal::ModelProposal(Model& model) : _model(model)
{
}


ModelPoprosal::~ModelProposal()
{
}


double ModelProposal::acceptanceRatio() const
{
    return std::min(1.0, productOfRatios());
}


void ModelProposal::accept() const
{
    matchModelToProposal();
}
