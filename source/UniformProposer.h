#ifndef UNIFORM_PROPOSER_H
#define UNIFORM_PROPOSER_H


#include "Proposer.h"


class UniformProposer : public Proposer
{
public:
    
    UniformProposer(double windowSize);    // Unconstrained
    UniformProposer(double windowSize, double min, double max);

    virtual double propose(double value) const;
    virtual double proposalRatio() const;

private:

    double _windowRadius;

    bool _constrained;
    double _min;
    double _max;
};


#endif
