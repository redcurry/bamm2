#include <iostream>
#include "Random.h"
#include "TestModel.h"
#include "TreeModelMCMC.h"
#include "Node.h"
#include "Tree.h"

Node* newNodeWithBranchLength(double branchLength)
{
    Node* node = new Node();
    node->setBranchLength(branchLength);
    return node;
}

int main(int argc, char *argv[])
{
    int seed = std::atoi(argv[1]);
    int numSteps = std::atoi(argv[2]);

    Random::setSeed(std::atoi(argv[1]));

    Node* node1 = newNodeWithBranchLength(2.0);
    Node* node2 = newNodeWithBranchLength(1.0);
    Node* node3 = newNodeWithBranchLength(1.0);
    Node* node4 = newNodeWithBranchLength(1.0);
    node4->addChildNode(node2);
    node4->addChildNode(node3);
    Node* node5 = newNodeWithBranchLength(2.0);
    node5->addChildNode(node1);
    node5->addChildNode(node4);
    Node* node6 = newNodeWithBranchLength(4.0);
    Node* node7 = newNodeWithBranchLength(0.0);
    node7->addChildNode(node5);
    node7->addChildNode(node6);
    Tree* tree = new Tree(node7);

    TreeModel* model = new TreeModel(tree);

    TreeModelMCMC mcmc;
    mcmc.run(model, numSteps, std::cout);

    delete model;
    delete tree;

    return 0;
}
