#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <SFML/Graphics.hpp>

#if __cplusplus > 201703L
#    include <concepts>
#endif //__cplusplus 20

#include <cstdarg>

#include "base_border.hpp"

namespace sml
{
using BaseBorderPtr = std::unique_ptr<sml::BaseBorder>;

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

    bool addBorder(BaseBorderPtr&& b);

    // template <IsMovable... Args> void addBorders(Args&&... args);

private:

    std::vector<BaseBorderPtr> m_border_vector;

    UpdStatus m_upd_status;
};

// template <IsMovable... Args>
// void
// BaseObject::addBorders(Args&&... args);
// {
//     (m_border_vector.emplace_back(std::move(args)), ...);
// }

} // namespace sml
#endif // !BASE_OBJECT_HPP