#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node;
typedef std::vector<Node *> NodeList;

class Node
{
  public:

    Node();
    ~Node();

    void setName(const std::string &name);
    const std::string &name() const;

    void setBranchLength(double length);
    double branchLength() const;

    double pathLengthToRoot() const;

    bool isBranchNode() const;
    bool isTerminalNode() const;

    void setParentNode(Node *parentNode);
    Node *parentNode();
    const Node *parentNode() const;
    bool hasParentNode() const;

    NodeList &childNodes();
    const NodeList &childNodes() const;

    void addChildNode(Node *childNode);

    int  childCount() const;
    bool hasChildNodes() const;

  private:

    static void deleteNode(Node *node);

    std::string _name;
    double _length;
    Node *_parentNode;
    NodeList _childNodes;
};

#endif
