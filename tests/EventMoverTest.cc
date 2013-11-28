#include "gtest/gtest.h"
#include "BasicTreeFixture.h"

#include "EventMover.h"
#include "Event.h"
#include "Node.h"
#include "Random.h"

#include <chrono>

#include <iostream>


// In the following comments, "E" is the current event,
// and "P" is the proposed event, where it should to move to.
// But "P" is not necessarily where it will move to,
// because that depends on whether the proposed position is reflected.

// TODO: Need to test boundary conditions (like events at tip)

// Test 1:
//
//                       2
//                  ----------- 1
//           2     |
//       --E----P--|        1
//      |         /|  1   ----- 2
//      |        5  -----|  1
//    7 |               / ----- 3
//      |              4
//      |          4
//       ---------------------- 6

TEST_F(BasicTreeFixture, MoveEvent1)
{
    Event event(node5, 0.5);
    double newAbsoluteTime = 1.5;

    EventMover eventMover;
    Event movedEvent = eventMover.newMovedEvent(event, newAbsoluteTime);

    EXPECT_EQ(node5, movedEvent.node());
    EXPECT_EQ(1.5, movedEvent.absoluteTime());
}


// Test 2:
//
//                       2
//                  ----------- 1
//           2     |
//       --E-------|    P   1
//      |         /|  1   ----- 2
//      |        5  -----|  1
//    7 |               / ----- 3
//      |              4
//      |          4
//       ---------------------- 6

TEST_F(BasicTreeFixture, MoveEvent2)
{
    // TODO: Change Random class so that I can instantiate one,
    // where I specify the sequence of numbers in order to test
    // specific cases

    // Note: Conversion from 64-bit (count method) to 32-bit (unsigned int)
    unsigned int seed =
        std::chrono::system_clock::now().time_since_epoch().count();
    Random::setSeed(seed);

    Event event(node5, 0.5);
    double newAbsoluteTime = 2.9;

    EventMover eventMover;
    Event movedEvent = eventMover.newMovedEvent(event, newAbsoluteTime);

    const Node* movedEventNode = movedEvent.node();

    std::cout << "Test 2: ended in node ";
    if (movedEventNode == node1) {
        std::cout << "node1";
    } else if (movedEventNode == node4) {
        std::cout << "node4";
    }
    std::cout << "\n";

    EXPECT_TRUE(movedEventNode == node1 || movedEventNode == node4);
    EXPECT_EQ(2.9, movedEvent.absoluteTime());
}

// Test 3:
//
//                       2
//                  ----------- 1
//           2     |
//       --E-------|        1      P
//      |         /|  1   ----- 2
//      |        5  -----|  1
//    7 |               / ----- 3
//      |              4
//      |          4
//       ---------------------- 6

TEST_F(BasicTreeFixture, MoveEvent3)
{
    Event event(node5, 0.5);
    double newAbsoluteTime = 4.5;

    EventMover eventMover;
    Event movedEvent = eventMover.newMovedEvent(event, newAbsoluteTime);

    const Node* movedEventNode = movedEvent.node();

    std::cout << "Test 3: ended in node ";
    if (movedEventNode == node1) {
        std::cout << "node1";
    } else if (movedEventNode == node2) {
        std::cout << "node2";
    } else if (movedEventNode == node3) {
        std::cout << "node3";
    }
    std::cout << "\n";

    EXPECT_TRUE(movedEventNode == node1 || movedEventNode == node2 ||
                movedEventNode == node3);
    EXPECT_EQ(3.5, movedEvent.absoluteTime());
}

// Test 4:
//
//                       2
//                  ----------- 1
//           2     |
//       --E-------|        1             P
//      |         /|  1   ----- 2
//      |        5  -----|  1
//    7 |               / ----- 3
//      |              4
//      |          4
//       ---------------------- 6

TEST_F(BasicTreeFixture, MoveEvent4)
{
    Event event(node5, 0.5);
    double newAbsoluteTime = 5.5;

    EventMover eventMover;
    Event movedEvent = eventMover.newMovedEvent(event, newAbsoluteTime);

    const Node* movedEventNode = movedEvent.node();

    std::cout << "Test 4: ended in node ";
    if (movedEventNode == node1) {
        std::cout << "node1";
        EXPECT_TRUE(movedEventNode == node1);
        EXPECT_EQ(2.5, movedEvent.absoluteTime());
    } else if (movedEventNode == node4) {
        std::cout << "node4";
        EXPECT_TRUE(movedEventNode == node4);
        EXPECT_EQ(2.5, movedEvent.absoluteTime());
    } else if (movedEventNode == node2) {
        std::cout << "node2";
        EXPECT_TRUE(movedEventNode == node2);
        EXPECT_EQ(3.5, movedEvent.absoluteTime());
    } else if (movedEventNode == node3) {
        std::cout << "node3";
        EXPECT_TRUE(movedEventNode == node3);
        EXPECT_EQ(3.5, movedEvent.absoluteTime());
    }
    std::cout << "\n";
}
