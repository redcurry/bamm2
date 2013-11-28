#ifndef MODEL_PROPOSAL_H
#define MODEL_PROPOSAL_H


class ModelProposal
{
public:

    virtual ~ModelProposal() { }

    virtual void accept() const = 0;

    virtual double acceptanceRatio() const;
    virtual double logPriorRatio() const;
    virtual double logLikelihoodRatio() const;
    virtual double logProposalRatio() const;
};

#endif
