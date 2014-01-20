#include "Model.h"
#include "Tree.h"


Model::Model(const Tree& tree) : _tree(tree)
{
}


double Model::logLikelihood() const
{
    return specificLogLikelihood();
}


ModelProposal* Model::createProposal() const
{
    return specificCreateProposal();
}


void Model::acceptProposal(const ModelProposal* proposal)
{
    specificAcceptProposal(proposal);
}
