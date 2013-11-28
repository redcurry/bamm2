#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Model.h"
#include <iosfwd>

class ModelProposal;


class TestModel : public Model
{
  public:

    TestModel(const TestModel* model);
    TestModel(int numEvents, double eventRate);
    virtual ~TestModel() { }

    virtual ModelProposal* newProposal();
    virtual std::ostream& print(std::ostream& out) const;

    int numberOfEvents() const;
    void setNumberOfEvents(int numEvents);

    double eventRate() const;
    void setEventRate(double eventRate);

  private:

    int _numEvents;
    double _eventRate;
};


inline int TestModel::numberOfEvents() const
{
  return _numEvents;
}


inline void TestModel::setNumberOfEvents(int numEvents)
{
  _numEvents = numEvents;
}


inline double TestModel::eventRate() const
{
  return _eventRate;
}


inline void TestModel::setEventRate(double eventRate)
{
  _eventRate = eventRate;
}


#endif
