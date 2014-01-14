#ifndef TREE_H
#define TREE_H

#include <iostream>

#include "Node.h"


typedef vector<Node*>::const_iterator NodeConstIterator;


class Tree
{
public:

    Tree(Node *rootNode = NULL);
    ~Tree();

    // write copy constructor and assignment

    void setRootNode(Node *rootNode);

    Node* rootNode();
    const Node* rootNode() const;

    bool isUltrametric() const;

    NodeList terminalNodes() const;

    NodeConstIterator beginPostOrderTraversal() const;
    NodeConstIterator endPostOrderTraversal() const;

private:

    void findTerminalNodes(Node *node, NodeList &nodes) const;

    Node *_rootNode;

    // Mutable variables can be changed by const member functions
    mutable bool _postOrderTraversalCreated;
    mutable NodeList _postOrderTraversal;
};

#endif
