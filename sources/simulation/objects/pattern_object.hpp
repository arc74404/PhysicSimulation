#ifndef PATTERN_OBJECT_HPP
#define PATTERN_OBJECT_HPP

#include "base_object.hpp"

namespace sml
{
class PatternObject : public BaseObject
{
public:
    enum class PatternType
    {
        RECTANGLE = 0,
        CIRCLE    = 1
    };

    PatternObject(PatternType pt) noexcept;

private:
    PatternType m_pattern_type;
};
} // namespace sml
#endif // !PATTERN_OBJECT_HPP