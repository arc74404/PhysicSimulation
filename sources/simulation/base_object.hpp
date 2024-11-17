#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/Graphics.hpp>

#include <cstdarg>

#include "base_border.hpp"

using BaseBorderPtr = std::unique_ptr<sml::BaseBorder>;

namespace sml
{
class BaseObject
{
public:
    BaseObject() = default;

    enum class UpdStatus
    {
        UPDATED   = 0,
        PERMANENT = 1
    };

    void printData() noexcept;

    template <typename... Args> void addBorders(Args&&... args) noexcept;

private:
    std::vector<BaseBorderPtr> m_border_vector;

    UpdStatus m_upd_status;
};

template <typename... Args>
void
BaseObject::addBorders(Args&&... args) noexcept
{
    (m_border_vector.emplace_back(std::move(args)), ...);
}

} // namespace sml
#endif // !BASE_OBJECT_HPP