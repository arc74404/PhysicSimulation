#ifndef FIELD_HPP
#define FIELD_HPP

#include "simulation/objects/base_object.hpp"

namespace sml
{

using BaseObjectPtr = std::unique_ptr<BaseObject>;

class Field
{
public:
    void update() noexcept;

private:
    std::vector<BaseObjectPtr> objects;
};
} // namespace sml

#endif // !FIELD_HPP