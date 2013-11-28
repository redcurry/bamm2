#include "TreeModel.h"
#include "Tree.h"

#include <iostream>


TreeModel::TreeModel(const Tree* tree) : _tree(tree)
{
}


std::ostream& TreeModel::print(std::ostream& out) const
{
  return out << _events.size();
}
