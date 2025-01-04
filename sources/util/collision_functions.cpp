#include "collision_functions.hpp"

#include "extra_math_functions.hpp"
void
utl::allign(std::vector<Point>& left, std::vector<Point>& right)
{
    std::vector<Point*> left_points_ptr_into_right;
    std::vector<Point*> right_points_ptr_into_left;

    int left_points_count  = left.size();
    int right_points_count = right.size();

    for (int l = 0; l < left_points_count; ++l)
    {
        Point& lp1 = left[l];
        Point& lp2 = left[l + 1];

        for (int r = 0; r < right_points_count; ++r)
        {
            Point& rp1 = right[r];
            Point& rp2 = right[r + 1];
        }
    }
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