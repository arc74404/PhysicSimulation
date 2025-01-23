#ifndef POINTS_STORAGE_HPP
#define POINTS_STORAGE_HPP

#include "simulation/borders/base_border.hpp"

#include "bounds.hpp"

namespace sml
{

class PointsStorage
{
public:
    PointsStorage() = default;

    void addBorder(const BaseBorderPtr& border, bool is_final_border = false);
    void addPoint(const Point& point, bool is_final_point = false);

    void clear() noexcept;

    void copyWithOffset(std::vector<Point>&, const sf::Vector2f& offset);

private:
    void allignPoints() noexcept;

    Bounds m_bounds;

    std::vector<Point> m_points;
};

} // namespace sml

#endif // POINTS_STORAGE_HPP