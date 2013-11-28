#ifndef MCMC_H
#define MCMC_H


template <typename ModelType>
class MCMC
{
  public:

    void run(const ModelType& model, int numSteps) const;

  protected:

    virtual ModelProposal* createModelProposal(Model* model) const = 0;
};

#endif
