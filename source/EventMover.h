#ifndef EVENT_MOVER_H
#define EVENT_MOVER_H

class Event;
class Node;


class EventMover
{
public:

    Event newMovedEvent(const Event& event, double newAbsoluteTime);

private:

    void moveForwardUpToBranch();
    void moveBackwardUpToBranch();

    const Node* chooseRandomChildNode(const Node* node);
    const Node* chooseParentOrRandomSibling(const Node* node);

    double reflect(double value, double wall);

    const Node* _eventNode;
    double _eventAbsoluteTime;
    double _newAbsoluteTime;
};

#endif
