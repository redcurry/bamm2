#include "Node.h"

#include <string>
#include <algorithm>


Node::Node() : _name(""), _length(0.0), _parentNode(NULL)
{
    _childNodes.reserve(2);
}


Node::~Node()
{
    std::for_each(_childNodes.begin(), _childNodes.end(), deleteNode);
}


void Node::setName(const std::string &name)
{
    _name = name;
}


const std::string &Node::name() const
{
    return _name;
}


void Node::setBranchLength(double length)
{
    _length = length;
}


double Node::branchLength() const
{
    return _length;
}


double Node::pathLengthToRoot() const
{
    double length = branchLength();

    const Node *node = this;
    while(node->hasParentNode()) {
        node = node->parentNode();
        length += node->branchLength();
    }

    return length;
}


bool Node::isBranchNode() const
{
    return hasChildNodes();
}


bool Node::isTerminalNode() const
{
    return !hasChildNodes();
}


void Node::setParentNode(Node *parentNode)
{
    _parentNode = parentNode;
}


Node *Node::parentNode()
{
    return _parentNode;
}


const Node *Node::parentNode() const
{
    return _parentNode;
}


bool Node::hasParentNode() const
{
    return _parentNode != NULL;
}


NodeList &Node::childNodes()
{
    return _childNodes;
}


const NodeList &Node::childNodes() const
{
    return _childNodes;
}


void Node::addChildNode(Node *childNode)
{
    childNode->setParentNode(this);
    _childNodes.push_back(childNode);
}


int Node::childCount() const
{
    return _childNodes.size();
}


bool Node::hasChildNodes() const
{
    return _childNodes.size() > 0;
}


void Node::deleteNode(Node *node)
{
    delete node;
}
