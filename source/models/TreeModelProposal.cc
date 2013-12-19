#include "TreeModelProposal.h"
#include "TreeModel.h"
#include "Event.h"
#include "Node.h"
#include "Random.h"
#include "EventMover.h"
#include "Tree.h"


TreeModelProposal::TreeModelProposal(const TreeModel& model) :
    _model(model), _proposedModel(model), _config(Config::instance())
{
    setUpEventProposers();
}


void TreeModelProposal::setUpEventProposers()
{
    // Set up proposer for adding events
    _eventChangeNumberProposer = new StepProposer(1, 0);

    double windowSize = 0.0;

    // Set up proposer for moving events locally
    windowSize = _config.get<double>("event_local_move_proposer_window_size");
    maxTreeTime = maximumTreeTime(_model.tree());
    _eventLocalMoveProposer = new UniformProposer(windowSize, 0.0, maxTreeTime);

    // Set up proposer for moving events globally
    // TODO: Will need to set up a tree mapping
}


double TreeModelProposal::maximumTreeTime(const Tree& tree) const
{
    NodeList tips = tree.terminalNodes();

    if (!tips.empty()) {
        // Assumes tree is ultrametric
        return tips[0].pathLengthToRoot();
    } else {
        log(Error) << "Tree has no tip nodes.\n";
        std::exit(1);
    }
}


void TreeModelProposal::propose()
{
    if (Random::accept(0.5)) {
        proposeEventMove();
    } else {
        proposeEventAddRemove();
    }
}


void TreeModelProposal::proposeEventMove()
{
    if (_proposedModel->events().size() == 0) {
        return;
    }

    int randomEventIndex = int(Random::uniform(0,
                               _proposedModel->events().size()));
    Event randomEvent = _proposedModel->events()[randomEventIndex];

    // TODO: What if there are no events to move?

    double minTime = randomEvent.absoluteTime() - _window / 2.0;
    double maxTime = randomEvent.absoluteTime() + _window / 2.0;

    double proposedTime = std::abs(Random::uniform(minTime, maxTime));

    // TODO: Think about having the event move actually move the event
    // (not return a new event)
    static EventMover eventMover;
    Event movedEvent = eventMover.newMovedEvent(randomEvent, proposedTime);

    _proposedModel->events()[randomEventIndex] = movedEvent;
}


void TreeModelProposal::proposeEventAddRemove()
{
    if (Random::accept(0.5)) {
        proposeEventAdd();
    } else {
        proposeEventRemove();
    }
}


void TreeModelProposal::proposeEventAdd()
{
    NodeList tips = _model->tree()->terminalNodes();

    // Pick random tip node
    int index = (int)Random::uniform(0, tips.size());
    Node* randomTip = tips[index];

    // Pick random absolute time on tip node path
    int randomAbsoluteTime = Random::uniform(0, randomTip->pathLengthToRoot());

    // Move an event starting at the root to the random absolute time
    Event randomEvent(_model->tree()->rootNode(), 0.0);
    static EventMover eventMover;
    randomEvent = eventMover.newMovedEvent(randomEvent, randomAbsoluteTime);

    // Add event to proposed model
    _proposedModel->events().push_back(randomEvent);
}


void TreeModelProposal::proposeEventRemove()
{
    if (_model->events().size() == 0) {
        return;
    }

    // Pick a random event from the model
    int index = (int)Random::uniform(0, _model->events().size());

    // Remove this event
    _proposedModel->events().erase(_proposedModel->events().begin() + index);
}
