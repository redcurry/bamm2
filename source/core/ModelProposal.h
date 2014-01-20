#ifndef MODEL_PROPOSAL_H
#define MODEL_PROPOSAL_H

class Model;


class ModelProposal
{
public:

    ModelProposal(const Model* model);
    virtual ~ModelProposal();

    double acceptanceRatio() const;

protected:

    // This method is called by acceptanceRatio(),
    // and it calculates priorRatio * likelihoodRatio * qRatio
    virtual double productOfRatios() const = 0;

    const Model* _model;
};


#endif
