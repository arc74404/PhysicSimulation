#ifndef FIELD_HPP
#define FIELD_HPP

#include <unordered_map>

#include "simulation/objects/base_object.hpp"

namespace sml
{

using BaseObjectPtr = std::unique_ptr<BaseObject>;

class Field
{
public:
    void update();

    const std::unordered_map<int, BaseObjectPtr>& getObjectsData()
        const noexcept;

private:
    std::unordered_map<int, BaseObjectPtr> objects;
};
} // namespace sml

#endif // !FIELD_HPP