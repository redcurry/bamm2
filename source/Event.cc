#include "Event.h"
class Node;

Event::Event(const Node* node, double absoluteTime) :
    _node(node), _absoluteTime(absoluteTime)
{
}
