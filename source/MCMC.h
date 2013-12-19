#ifndef MCMC_H
#define MCMC_H


class Model;
class ModelProposer;


class MCMC
{
public:

    MCMC(const Model& initialModel, const ModelProposer& modelProposer);

    void run(int numSteps) const;

private:

    const Model& _initialModel;
    const ModelProposer& _modelProposer;
};


#endif
