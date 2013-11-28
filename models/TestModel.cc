#include "TestModel.h"
#include "TestModelProposal.h"
#include <iostream>


TestModel::TestModel(const TestModel *model) :
  _numEvents(model->numberOfEvents()), _eventRate(model->eventRate())
{
}


TestModel::TestModel(int numEvents, double eventRate) :
  _numEvents(numEvents), _eventRate(eventRate)
{
}


ModelProposal* TestModel::newProposal()
{
  return new TestModelProposal(this);
}


std::ostream& TestModel::print(std::ostream& out) const
{
  return out << _numEvents << " " << _eventRate;
}
