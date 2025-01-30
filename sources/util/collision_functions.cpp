#include "collision_functions.hpp"

#include <cmath>

#include "extra_math_functions.hpp"

std::optional<utl::CollisionHandler::CollisionData>
utl::CollisionHandler::getCollisionData(const std::vector<Point>& left,
                                        const sf::Vector2f& left_direction,
                                        const std::vector<Point>& right)
{
    std::optional<CollisionData> result;

    auto left_handle = getCollisionData(left, left_direction, right, true);

    auto right_handle = getCollisionData(right, left_direction, left, false);

    sf::Vector2f max_displacement_vector;
    if (left_handle.has_value() && !right_handle.has_value())
    {
        result = left_handle;
    }
    else if (right_handle.has_value() && !left_handle.has_value())
    {
        result = right_handle;
    }
    else if (left_handle.has_value() && right_handle.has_value())
    {
        if (getDistance(Point(0, 0), right_handle.operator*().allign_vector) >
            getDistance(Point(0, 0), left_handle.operator*().allign_vector))
        {
            result = right_handle;
        }
        else
        {
            result = left_handle;
        }
    }

    return result;
}

std::optional<utl::Point>
utl::CollisionHandler::getIntersection(const Section& left,
                                       const Section& right) noexcept
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
utl::CollisionHandler::isIntersect(Section left, Section right)
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
utl::CollisionHandler::getCounterDirectionalRay(const sf::Vector2f& direction,
                                                const Point& p)
{
    Section res;
    res.first  = p;
    res.second = {(p.x - direction.x * 1000.f), (p.y - direction.y * 1000.f)};
    return res;
}

utl::Section
utl::CollisionHandler::getDirectionalRay(const sf::Vector2f& direction,
                                         const Point& p)
{
    Section res;
    res.first  = p;
    res.second = {(p.x + direction.x * 1000.f), (p.y + direction.y * 1000.f)};
    return res;
}

float
utl::CollisionHandler::getDistance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

sf::Vector2f
utl::CollisionHandler::getNormal(const Section& section)
{
    return {section.second.y - section.first.y,
            -(section.second.x - section.first.x)};
}

sf::Vector2f
utl::CollisionHandler::normalize(const sf::Vector2f& vec) noexcept
{
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    return (length == 0) ? sf::Vector2f({0.f, 0.f})
                         : sf::Vector2f(vec.x / length, vec.y / length);
}

float
utl::CollisionHandler::getScalarProduct(const sf::Vector2f& vec1,
                                        const sf::Vector2f& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

sf::Vector2f
utl::CollisionHandler::getReflectionVector(const sf::Vector2f& normal,
                                           const sf::Vector2f& movement_vector)
{
    float dot_product = getScalarProduct(normal, movement_vector);

    return normalize(movement_vector - 2 * dot_product * normal);
}

std::optional<utl::CollisionHandler::CollisionData>
utl::CollisionHandler::getCollisionData(const std::vector<Point>& first,
                                        const sf::Vector2f& direction,
                                        const std::vector<Point>& second,
                                        bool is_counter_directional)
{
    std::optional<CollisionData> result;

    auto first_points_count  = first.size();
    auto second_points_count = second.size();
    float max_distance       = std::numeric_limits<float>::min();

    auto* getRay =
        is_counter_directional ? getCounterDirectionalRay : getDirectionalRay;

    CollisionData collision_data = {
        {0, 0},
        {0, 0}
    };

    bool flag_was_intersection = false;

    for (int i = 0; i < first_points_count - 1; ++i)
    {
        // build the ray in the opposite direction
        Section ray = getRay(direction, first[i]);

        int intersections_count = 0;

        float max_local_distance = 0;

        Point intersection_point_with_max_distance;
        Section intersection_border;

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

                    intersection_border = border;
                }
                ++intersections_count;
            }
        }

        if (intersections_count > 0)
        {
            if (max_distance < max_local_distance)
            {
                max_distance = max_local_distance;

                collision_data.allign_vector = {
                    intersection_point_with_max_distance.x - first[i].x,
                    intersection_point_with_max_distance.y - first[i].y};

                collision_data.unit_normal =
                    normalize(getNormal(intersection_border));
            }
        }
        // odd intersections => point in the polygon
        if (intersections_count % 2 == 1)
        {
            flag_was_intersection = true;
        }
    }
    if (!is_counter_directional)
    {
        collision_data.allign_vector.x *= -1.f;
        collision_data.allign_vector.y *= -1.f;
    }
    if (flag_was_intersection)
    {
        result.emplace(collision_data);
    }

    return result;
}
