#include "Model.h"


Model::~Model()
{
}


void Model::print(std::ostream& out) const
{
    write(out);
}


std::ostream& operator<<(std::ostream& out, const Model& model)
{
    model.print(out);
    return out;
}
