#ifndef TREE_MODEL_MCMC_H
#define TREE_MODEL_MCMC_H

#include <iosfwd>
#include "MCMC.h"
#include "TreeModelProposal.h"

class Model;
class ModelProposal;


class TreeModelMCMC : public MCMC
{
protected:

    virtual ModelProposal* createModelProposal(Model* model) const;
};


inline ModelProposal* TreeModelMCMC::createModelProposal(Model* model) const
{
    return new TreeModelProposal((TreeModel*)model);
}

#endif
