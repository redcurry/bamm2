#include "gtest/gtest.h"
#include "UniformProposer.h"
#include <iostream>

TEST(UniformProposerTest, Unconstrained)
{
    double value = 5.0;
    double windowSize = 1.0;
    double windowRadius = windowSize / 2.0;

    UniformProposer proposer(windowSize);

    for (int i = 0; i < 10000; i++) {
        double proposedValue = proposer.propose(value);
        EXPECT_NE(value, proposedValue);
        EXPECT_GT(proposedValue, value - windowRadius);
        EXPECT_LT(proposedValue, value + windowRadius);
    }
}


TEST(UniformProposerTest, Constrained)
{
    double value = 5.0;
    double windowSize = 1.0;
    double windowRadius = windowSize / 2.0;
    double min = 4.75;
    double max = 5.25;

    UniformProposer proposer(windowSize, min, max);

    for (int i = 0; i < 10000; i++) {
        double proposedValue = proposer.propose(value);
        EXPECT_NE(value, proposedValue);
        EXPECT_GT(proposedValue, value - windowRadius);
        EXPECT_LT(proposedValue, value + windowRadius);
        EXPECT_GT(proposedValue, min);
        EXPECT_LT(proposedValue, max);
    }
}
