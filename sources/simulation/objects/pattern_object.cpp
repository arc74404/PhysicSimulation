#include "pattern_object.hpp"

sml::PatternObject::PatternObject(PatternType pt) noexcept
    : BaseObject(FormType::PATTERN), m_pattern_type(pt)
{
}