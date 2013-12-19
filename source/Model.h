#ifndef MODEL_H
#define MODEL_H

#include "Event.h"
#include <vector>

class Tree;


class Model
{
public:

    Model(const Tree& tree);
    virtual ~Model() { }

    const Tree& tree() const;

    const std::vector<Event*>& events() const;
    std::vector<Event*>& events();

    double logLikelihood() const;

protected:

    virtual specificLogLikelihood() const = 0;

    const Tree& _tree;
    std::vector<Event*> _events;
};


inline const Tree& Model::tree() const
{
    return _tree;
}


inline const std::vector<Event*>& Model::events() const
{
    return _events;
}


inline std::vector<Event*>& Model::events()
{
    return _events;
}


#endif
