#ifndef MODEL_H
#define MODEL_H

#include <iosfwd>


// TODO: Potentially make Model a template, where the type of the proposal
// is specified, which is then typedef'ed inside the class as Proposal
class Model
{
public:

    virtual ~Model();

    void print(std::ostream& out) const;

private:

    virtual void write(std::ostream& out) const = 0;
};


std::ostream& operator<<(std::ostream& out, const Model& model);


#endif
