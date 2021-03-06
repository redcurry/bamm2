#ifndef SP_EX_MODEL_H
#define SP_EX_MODEL_H


#include "Model.h"


class SpExModel : public Model
{
protected:

    virtual double specificLogLikelihood() const;

    virtual ModelProposal* specificCreateProposal() const;
    virtual void specificAcceptProposal(const ModelProposal* proposal);
};


#endif
