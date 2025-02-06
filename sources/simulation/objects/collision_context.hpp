#ifndef COLLISION_CONTEXT_HPP
#define COLLISION_CONTEXT_HPP

#include <SFML/System/Vector2.hpp>

#include <mutex>
#include <optional>

class BaseObject;

namespace sml
{
struct CollisionContext
{
    sf::Vector2f collision_unit_normal;

    std::shared_ptr<BaseObject> collision_object;

    bool is_const;
};
} // namespace sml

#endif // COLLISION_CONTEXT_HPP