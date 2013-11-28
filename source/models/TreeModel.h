#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include <iosfwd>
#include <vector>

#include "Model.h"
#include "Event.h"

class Tree;


class TreeModel : public Model
{
  public:

    TreeModel(const Tree* tree);    // TODO: Consider "const Tree&" instead
    virtual ~TreeModel() { }

    const Tree* tree() const;

    virtual std::ostream& print(std::ostream& out) const;

    const std::vector<Event>& events() const;
    std::vector<Event>& events();

  private:

    const Tree* _tree;
    std::vector<Event> _events;
};


inline const Tree* TreeModel::tree() const
{
  return _tree;
}


inline const std::vector<Event>& TreeModel::events() const
{
  return _events;
}


inline std::vector<Event>& TreeModel::events()
{
  return _events;
}


#endif
