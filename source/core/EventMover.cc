#include "EventMover.h"
#include "Node.h"
#include "Event.h"
#include "Random.h"


Event EventMover::newMovedEvent(const Event& event, double newAbsoluteTime)
{
    _eventNode = event.node();
    _eventAbsoluteTime = event.absoluteTime();
    _newAbsoluteTime = newAbsoluteTime;

    while (_eventAbsoluteTime != _newAbsoluteTime) {
        if (_eventAbsoluteTime < _newAbsoluteTime) {
            moveForwardUpToBranch();
        } else if (_eventAbsoluteTime > _newAbsoluteTime) {
            moveBackwardUpToBranch();
        }
    }

    return Event(_eventNode, _eventAbsoluteTime);
}


void EventMover::moveForwardUpToBranch()
{
    double eventNodeAbsoluteTime = _eventNode->pathLengthToRoot();
    if (eventNodeAbsoluteTime < _newAbsoluteTime) {
        _eventAbsoluteTime = eventNodeAbsoluteTime;

        // Switch to a child node or, if no children (tip), reflect
        if (_eventNode->hasChildNodes()) {
            _eventNode = chooseRandomChildNode(_eventNode);
        } else {
            _newAbsoluteTime = reflect(_newAbsoluteTime, _eventAbsoluteTime);
        }
    } else {
        _eventAbsoluteTime = _newAbsoluteTime;
    }
}


const Node* EventMover::chooseRandomChildNode(const Node* node)
{
    return node->childNodes()[(int)Random::uniform(0, node->childCount())];
}


void EventMover::moveBackwardUpToBranch()
{
    if (_eventNode->hasParentNode()) {
        const Node* parentNode = _eventNode->parentNode();
        double parentAbsoluteTime = parentNode->pathLengthToRoot();
        if (_newAbsoluteTime < parentAbsoluteTime) {
            _eventAbsoluteTime = parentAbsoluteTime;
            _eventNode = chooseParentOrRandomSibling(_eventNode);
            if (_eventNode != parentNode) {
                _newAbsoluteTime = reflect(_newAbsoluteTime, _eventAbsoluteTime);
            }
        } else {
            _eventAbsoluteTime = _newAbsoluteTime;
        }
    } else {
        _newAbsoluteTime = reflect(_newAbsoluteTime, _eventAbsoluteTime);
    }
}


const Node* EventMover::chooseParentOrRandomSibling(const Node* node)
{
    const Node* parentNode = node->parentNode();
    int index = (int)Random::uniform(0, parentNode->childCount());

    // Trick to get parent randomly: because this method should never return
    // the given node, make its index "be" the parent
    if (parentNode->childNodes()[index] != node) {
        return parentNode->childNodes()[index];
    } else {
        return parentNode;
    }
}

double EventMover::reflect(double value, double wall)
{
    return 2 * wall - value;
}
