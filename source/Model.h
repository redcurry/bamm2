#ifndef MODEL_H
#define MODEL_H

#include <iosfwd>
class ModelProposal;


class Model
{
public:

    virtual ~Model() { }

    virtual std::ostream& print(std::ostream& out) const = 0;
};


inline std::ostream& operator<<(std::ostream& out, const Model* model)
{
    return model->print(out);
}


#endif
