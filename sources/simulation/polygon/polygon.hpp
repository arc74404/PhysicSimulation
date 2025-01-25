#ifndef POINTS_STORAGE_HPP
#define POINTS_STORAGE_HPP

#include "simulation/borders/base_border.hpp"

#include "bounds.hpp"

namespace sml
{

class Polygon
{
public:
    Polygon() = default;

    void addBorder(const BaseBorderPtr& border, bool is_final_border = false,
                   bool allign = false);
    void addPoint(const Point& point, bool is_final_point = false,
                  bool allign = false);

    void clear() noexcept;

    void copyWithOffset(std::vector<Point>& other_points, Bounds& other_bounds,
                        const sf::Vector2f& offset = {0, 0}) const;

private:
    void allignPoints() noexcept;

    Bounds m_bounds;

    std::vector<Point> m_points;
};

} // namespace sml

#endif // POINTS_STORAGE_HPP