#include <cmath>
#include <iostream>

#include "Tree.h"
#include "Node.h"


Tree::Tree(Node *rootNode) : _rootNode(rootNode)
{
}


Tree::~Tree()
{
    delete _rootNode;
}


void Tree::setRootNode(Node *rootNode)
{
    _rootNode = rootNode;
}


Node *Tree::rootNode()
{
    return _rootNode;
}


const Node *Tree::rootNode() const
{
    return _rootNode;
}


bool Tree::isUltrametric() const
{
    const NodeList &nodes = terminalNodes();

    if(nodes.size() == 0) {
        return false;
    }

    double pathLength = nodes[0]->pathLengthToRoot();

    NodeList::const_iterator it;
    for(it = nodes.begin() + 1; it != nodes.end(); ++it) {
        if(std::fabs((*it)->pathLengthToRoot() - pathLength) > 1e-4) {
            std::cout << (*it)->pathLengthToRoot() << ", " << pathLength << std::endl;
            return false;
        }
    }

    return true;
}


NodeList Tree::terminalNodes() const
{
    NodeList nodes;
    findTerminalNodes(const_cast<Node *>(rootNode()), nodes);
    return nodes;
}


void Tree::findTerminalNodes(Node *node, NodeList &nodes) const
{
    if(node->hasChildNodes()) {
        const NodeList &childNodes = node->childNodes();
        NodeList::const_iterator it;
        for(it = childNodes.begin(); it != childNodes.end(); ++it) {
            findTerminalNodes(*it, nodes);
        }
    } else {
        nodes.push_back(node);
    }
}
