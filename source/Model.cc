#include "Model.h"
#include "Tree.h"


Model::Model(const Tree& tree) : _tree(tree)
{
}


double Model::logLikelihood() const
{
    return specificLogLikelihood();
}
