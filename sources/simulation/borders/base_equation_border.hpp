#ifndef BASE_EQUATION_BORDER_HPP
#define BASE_EQUATION_BORDER_HPP

#include "base_border.hpp"

namespace sml
{

using Point = sf::Vector2f;

class BaseEquationBorder : public BaseBorder
{
public:
    enum class EquationType
    {
        X_IS_CONST = 0,
        CIRCLE     = 1
    };
    BaseEquationBorder(EquationType, bool is_cl) noexcept;

    EquationType getEquationType();

    bool isClosed();

private:
    bool is_closed;

    EquationType m_equation_type;
};
} // namespace sml

#endif // !BASE_EQUATION_BORDER_HPP