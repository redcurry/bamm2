#ifndef MODEL_PROPOSAL_H
#define MODEL_PROPOSAL_H

class Model;


class ModelProposal
{
public:

    ModelProposal(Model& model);
    virtual ~ModelProposal();

    double acceptanceRatio() const;
    void accept() const;

protected:

    Model& _model;

private:

    // This method is called by acceptanceRatio(),
    // and it calculates priorRatio * likelihoodRatio * qRatio
    virtual double productOfRatios() const = 0;

    // This method is called by accept(),
    // and it makes the model match the proposal
    virtual void matchModelToProposal() const = 0;
};


#endif
