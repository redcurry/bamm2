#include "gtest/gtest.h"

#include "Tree.h"
#include "Node.h"
#include "Random.h"


class BasicTreeFixture : public testing::Test
{
  protected:

    virtual void SetUp()
    {
      // Create a tree that looks like:
      //
      //                       2
      //                  ----------- 1
      //           2     |
      //       ----------|        1
      //      |         /|  1   ----- 2
      //      |        5  -----|  1  
      //    7 |               / ----- 3
      //      |              4
      //      |          4
      //       ---------------------- 6

      node1 = newNodeWithBranchLength(2.0);
      node2 = newNodeWithBranchLength(1.0);
      node3 = newNodeWithBranchLength(1.0);
      node4 = newNodeWithBranchLength(1.0);
      node4->addChildNode(node2);
      node4->addChildNode(node3);
      node5 = newNodeWithBranchLength(2.0);
      node5->addChildNode(node1);
      node5->addChildNode(node4);
      node6 = newNodeWithBranchLength(4.0);
      node7 = newNodeWithBranchLength(0.0);
      node7->addChildNode(node5);
      node7->addChildNode(node6);

      tree = new Tree(node7);
    }

    Node* newNodeWithBranchLength(double branchLength)
    {
      Node* node = new Node();
      node->setBranchLength(branchLength);
      return node;
    }

    virtual void TearDown()
    {
      delete tree;
    }

    Tree* tree;
    Node* node1;
    Node* node2;
    Node* node3;
    Node* node4;
    Node* node5;
    Node* node6;
    Node* node7;
};
