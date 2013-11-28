#include "TestModelProposal.h"
#include "TestModel.h"
#include "Random.h"
#include <cmath>


TestModelProposal::TestModelProposal(TestModel* model) : _model(model)
{
  _proposedModel = new TestModel(_model);

  if (Random::accept(0.5))
    proposeNumberOfEvents();
  else
    proposeEventRate();
}


void TestModelProposal::proposeNumberOfEvents()
{
  int proposedNumEvents;

  if (Random::accept(0.5))
    proposedNumEvents = _model->numberOfEvents() + 1;
  else
    proposedNumEvents = std::abs(_model->numberOfEvents() - 1);

  _proposedModel->setNumberOfEvents(proposedNumEvents);
}


void TestModelProposal::proposeEventRate()
{
  double minRate = _model->eventRate() - _eventRateWindow / 2.0;
  double maxRate = _model->eventRate() + _eventRateWindow / 2.0;
  double proposedEventRate = std::abs(Random::uniform(minRate, maxRate));
  _proposedModel->setEventRate(proposedEventRate);
}


void TestModelProposal::accept() const
{
  if (_proposedModel->numberOfEvents() != _model->numberOfEvents())
    _model->setNumberOfEvents(_proposedModel->numberOfEvents());
  else
    _model->setEventRate(_proposedModel->eventRate());
}


double TestModelProposal::logPriorRatio() const
{
  if (_proposedModel->numberOfEvents() != _model->numberOfEvents())
    return logNumEventsPriorRatio();
  else
    return logEventRatePriorRatio();
}


double TestModelProposal::logNumEventsPriorRatio() const
{
  if (_proposedModel->numberOfEvents() > _model->numberOfEvents())
    return std::log(_model->eventRate()) -
      std::log(_proposedModel->numberOfEvents());
  else
    return std::log(_model->numberOfEvents()) - std::log(_model->eventRate());
}


double TestModelProposal::logEventRatePriorRatio() const
{
  return 0.01 * (_model->eventRate() - _proposedModel->eventRate());
}


double TestModelProposal::logProposalRatio() const
{
  if (_proposedModel->numberOfEvents() != _model->numberOfEvents())
    return logNumEventsProposalRatio();
  else
    return logEventRateProposalRatio();
}


double TestModelProposal::logNumEventsProposalRatio() const
{
  if (_model->numberOfEvents() == 0 && _proposedModel->numberOfEvents() == 1)
    return -0.6931472;    // log(0.5)
  else
    return 0.0;
}


double TestModelProposal::logEventRateProposalRatio() const
{
  return 0.0;
}
