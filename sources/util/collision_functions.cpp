#include "collision_functions.hpp"

#include <cmath>

#include "extra_math_functions.hpp"

sf::Vector2f
utl::allignVector(std::vector<Point>& left, const sf::Vector2f& left_direction,
                  std::vector<Point>& right)
{
    sf::Vector2f max_displacement_vector_l =
        getDisplacementVector(left, left_direction, right, true);

    sf::Vector2f max_displacement_vector_r =
        getDisplacementVector(right, left_direction, left, false);

    sf::Vector2f max_displacement_vector;

    if (getDistance(Point(0, 0), max_displacement_vector_l) >
        getDistance(Point(0, 0), max_displacement_vector_r))
    {
        max_displacement_vector = max_displacement_vector_l;
    }
    else
    {
        max_displacement_vector = max_displacement_vector_r;
    }

    return max_displacement_vector;
}

std::optional<utl::Point>
utl::getIntersection(const Section& left, const Section& right) noexcept
{
    std::optional<Point> res;
    Point p;

    auto getCoefficientK = [](const Point& p1,
                              const Point& p2) noexcept -> float
    { return (p2.y - p1.y) / (p2.x - p1.x); };

    float left_K, left_B;
    float right_K, right_B;

    if (left.first.x - left.second.x == 0 &&
        right.first.x - right.second.x == 0)
    {
        return res;
    }
    else if (left.first.x - left.second.x != 0 &&
             right.first.x - right.second.x == 0)
    {
        left_K = getCoefficientK(left.first, left.second);
        left_B = left.first.y - left_K * left.first.x;

        p.x = right.first.x;
        p.y = left_K * p.x + left_B;
    }
    else if (left.first.x - left.second.x == 0 &&
             right.first.x - right.second.x != 0)
    {
        right_K = getCoefficientK(right.first, right.second);
        right_B = right.first.y - right_K * right.first.x;

        p.x = left.first.x;
        p.y = right_K * p.x + right_B;
    }
    else
    {
        left_K = getCoefficientK(left.first, left.second);
        left_B = left.first.y - left_K * left.first.x;
        //////////////
        right_K = getCoefficientK(right.first, right.second);
        right_B = right.first.y - right_K * right.first.x;

        if (utl::isFloatsEqual(left_K, right_K)) return res;

        p.x = (right_B - left_B) / (left_K - right_K);
        p.y = left_K * p.x + left_B;
    }
    res.emplace(p);
    return res;
}

std::optional<utl::Point>
utl::isIntersect(Section left, Section right)
{
    auto res = getIntersection(left, right);

    if (left.first.x > left.second.x) std::swap(left.first.x, left.second.x);
    if (left.first.y > left.second.y) std::swap(left.first.y, left.second.y);
    if (right.first.x > right.second.x)
        std::swap(right.first.x, right.second.x);
    if (right.first.y > right.second.y)
        std::swap(right.first.y, right.second.y);

    if (res.has_value())
    {
        bool x_axis_left = (res->x >= left.first.x && res->x <= left.second.x);

        bool y_axis_left = (res->y >= left.first.y && res->y <= left.second.y);

        bool x_axis_right =
            (res->x >= right.first.x && res->x <= right.second.x);

        bool y_axis_right =
            (res->y >= right.first.y && res->y <= right.second.y);

        if (!(x_axis_left && y_axis_left && x_axis_right && y_axis_right))
        {
            res.reset();
        }
    }

    return res;
}

utl::Section
utl::getCounterDirectionalRay(const sf::Vector2f& direction, const Point& p)
{
    Section res;
    res.first  = p;
    res.second = {(p.x - direction.x * 1000.f), (p.y - direction.y * 1000.f)};
    return res;
}

utl::Section
utl::getDirectionalRay(const sf::Vector2f& direction, const Point& p)
{
    Section res;
    res.first  = p;
    res.second = {(p.x + direction.x * 1000.f), (p.y + direction.y * 1000.f)};
    return res;
}

float
utl::getDistance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

sf::Vector2f
utl::getDisplacementVector(const std::vector<Point>& first,
                           const sf::Vector2f& direction,
                           const std::vector<Point>& second,
                           bool is_counter_directional)
{
    auto first_points_count  = first.size();
    auto second_points_count = second.size();
    float max_distance       = std::numeric_limits<float>::min();

    auto* getRay =
        is_counter_directional ? getCounterDirectionalRay : getDirectionalRay;

    sf::Vector2f max_displacement_vector = {0, 0};

    bool flag_was_intersection = false;

    for (int i = 0; i < first_points_count - 1; ++i)
    {
        // build the ray in the opposite direction
        Section ray = getRay(direction, first[i]);

        int intersections_count = 0;

        float max_local_distance = 0;

        Point intersection_point_with_max_distance;

        // check borders
        for (int j = 0; j < second_points_count - 1; ++j)
        {
            float distance;
            Section border = {second[j], second[j + 1]};

            auto intersection_point = isIntersect(border, ray);

            if (intersection_point.has_value())
            {
                distance = getDistance(first[i], *intersection_point);
                if (max_local_distance < distance)
                {
                    max_local_distance = distance;

                    intersection_point_with_max_distance = *intersection_point;
                }
                ++intersections_count;
            }
        }
        // odd intersections => point in the polygon
        if (intersections_count > 0)
        {
            if (max_distance < max_local_distance)
            {
                max_distance = max_local_distance;

                max_displacement_vector = {
                    intersection_point_with_max_distance.x - first[i].x,
                    intersection_point_with_max_distance.y - first[i].y};
            }
        }
        if (intersections_count % 2 == 1)
        {
            flag_was_intersection = true;
        }
    }
    if (!is_counter_directional)
    {
        max_displacement_vector.x *= -1.f;
        max_displacement_vector.y *= -1.f;
    }

    return flag_was_intersection ? max_displacement_vector : sf::Vector2f(0, 0);
}
