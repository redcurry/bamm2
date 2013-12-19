#include "UniformProposer.h"
#include "Random.h"


UniformProposer::UniformProposer(double windowSize) :
    _windowRadius(windowSize / 2.0), _constrained(false), _min(0.0), _max(0.0)
{
}


UniformProposer::UniformProposer(double windowSize, double min, double max) :
    _windowRadius(windowSize / 2.0), _constrained(true), _min(min), _max(max)
{
}


double UniformProposer::propose(double value) const
{
    double windowMin = value - _windowRadius;
    double windowMax = value + _windowRadius;

    double proposedValue = Random::uniform(windowMin, windowMax);

    if (_constrained) {
        if (proposedValue < _min) {
            // TODO: Possibly optimize 2 * min/max
            proposedValue = 2 * _min - proposedValue;
        } else if (proposedValue > _max) {
            proposedValue = 2 * _max - proposedValue;
        }
    }

    return proposedValue;
}


double UniformProposer::proposalRatio() const
{
    return 1.0;
}
