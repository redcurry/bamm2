#include "gtest/gtest.h"
#include "BasicTreeFixture.h"

#include "TreeModelProposal.h"
#include "TreeModel.h"
#include "Event.h"


typedef BasicTreeFixture TreeModelPoposalTest; 


TEST_F(TreeModelPoposalTest, Construction)
{
  TreeModel model(tree);
  Event event(node4, 2.5);
  model.events().push_back(event);

  TreeModelProposal modelProposal(&model);
}
