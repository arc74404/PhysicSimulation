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
    Field();

    void update(float time);

    const std::unordered_map<int, BaseObjectPtr>& getObjectsData(
        bool is_updatable) const noexcept;

private:
    std::unordered_map<int, BaseObjectPtr> m_updatable_objects;

    std::unordered_map<int, BaseObjectPtr> m_const_objects;
};
} // namespace sml

#endif // !FIELD_HPP