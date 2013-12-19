#ifndef TREE_MODEL_PROPOSAL_H
#define TREE_MODEL_PROPOSAL_H

#include "ModelProposal.h"
#include "TreeModel.h"

class TreeModelProposal : public ModelProposal
{
public:

    TreeModelProposal(TreeModel* model);
    virtual ~TreeModelProposal() { }

    virtual void accept() const;

    //virtual double acceptanceRatio() const;
    //virtual double logPriorRatio() const;
    //virtual double logLikelihoodRatio() const;
    //virtual double logProposalRatio() const;

private:

    void proposeEventMove();
    void proposeEventAddRemove();
    void proposeEventAdd();
    void proposeEventRemove();

    TreeModel& _model;
    TreeModel& _proposedModel;


};


inline void TreeModelProposal::accept() const
{
    _model->events() = _proposedModel->events();
}

#endif
