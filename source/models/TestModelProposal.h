#ifndef TEST_MODEL_PROPOSAL_H
#define TEST_MODEL_PROPOSAL_H

#include "ModelProposal.h"
class TestModel;


class TestModelProposal : public ModelProposal
{
public:

    TestModelProposal(TestModel* model);
    virtual ~TestModelProposal() { }

    virtual void accept() const;

    virtual double logPriorRatio() const;
    virtual double logProposalRatio() const;

private:

    void proposeNumberOfEvents();
    void proposeEventRate();

    double logNumEventsPriorRatio() const;
    double logEventRatePriorRatio() const;

    double logNumEventsProposalRatio() const;
    double logEventRateProposalRatio() const;

    TestModel* _model;
    TestModel* _proposedModel;

    double _eventRateWindow = 40.0;
};

#endif
