#ifndef PROPOSER_H
#define PROPOSER_H


class Proposer
{
public:
    
    virtual ~Proposer() {};
    virtual double propose(double value) const = 0;
    virtual double proposalRatio() const = 0;
};


#endif
