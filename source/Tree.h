#ifndef TREE_H
#define TREE_H

#include <iostream>

#include "Node.h"

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

  private:

    void findTerminalNodes(Node *node, NodeList &nodes) const;

    Node *_rootNode;
};

#endif
