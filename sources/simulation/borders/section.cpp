#include "section.hpp"

sml::Section::Section() : Section({0, 0}, {0, 0})
{
}
sml::Section::Section(const Point& p1, const Point& p2) : begin(p1), end(p2)
{
}