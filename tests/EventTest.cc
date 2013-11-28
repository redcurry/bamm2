#include "gtest/gtest.h"

#include "Event.h"
#include "Node.h"


TEST(EventTest, Construction)
{
    Node* node = new Node();
    Event event(node, 2.0);

    EXPECT_EQ(node, event.node());
    EXPECT_EQ(2.0, event.absoluteTime());

    delete node;
}


TEST(EventTest, Properties)
{
    Node* node = new Node();
    Event event(node, 2.0);

    Node* node2 = new Node();
    event.setNode(node2);
    event.setAbsoluteTime(4.0);

    EXPECT_EQ(node2, event.node());
    EXPECT_EQ(4.0, event.absoluteTime());

    delete node;
    delete node2;
}
