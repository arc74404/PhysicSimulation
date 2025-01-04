#include <gtest/gtest.h>

#include "util/collision_functions.hpp"
#include "util/extra_math_functions.hpp"

TEST(GetIntersectionTests, get_intersection_regular_and_regular)
{
    utl::Section s1, s2;
    s1.first  = {-1.f, 8.f};
    s1.second = {4.f, 0.2};

    s2.first  = {-2.f, -6.f};
    s2.second = {6.f, 3.f};

    auto p = utl::getIntersection(s1, s2);

    ASSERT_EQ(p.has_value(), true);
    ASSERT_EQ(
        utl::isPointsEqual(*p, utl::Point({2038.f / 537.f, 93.f / 179.f})),
        true);

    p = utl::getIntersection(s2, s1);
    ASSERT_EQ(p.has_value(), true);
    ASSERT_EQ(
        utl::isPointsEqual(*p, utl::Point({2038.f / 537.f, 93.f / 179.f})),
        true);
}

TEST(GetIntersectionTests, get_intersection_parallel)
{
    utl::Section s1, s2;
    s1.first  = {0, 7.33f};
    s1.second = {0 - 4.1f, 7.33f - 10.f};

    s2.first  = {0, -3.191};
    s2.second = {0 - 4.1f, -3.191 - 10.f};

    auto p = utl::getIntersection(s1, s2);
    ASSERT_EQ(p.has_value(), false);

    p = utl::getIntersection(s2, s1);
    ASSERT_EQ(p.has_value(), false);
}

TEST(GetIntersectionTests, get_intersection_perpendicular_and_regular)
{
    utl::Section s1, s2;
    s1.first  = {-2.f, 0.f};
    s1.second = {6.f, -4.f};

    s2.first  = {4.f, 72.3672f};
    s2.second = {4.f, -22.f};

    auto p = utl::getIntersection(s1, s2);

    ASSERT_EQ(p.has_value(), true);
    ASSERT_EQ(utl::isPointsEqual(*p, utl::Point(4.f, -3.f)), true);

    p = utl::getIntersection(s2, s1);
    ASSERT_EQ(p.has_value(), true);
    ASSERT_EQ(utl::isPointsEqual(*p, utl::Point(4.f, -3.f)), true);
}

TEST(GetIntersectionTests, get_intersection_perpendicular_and_perpendicular)
{
    utl::Section s1, s2;
    s1.first  = {-54.3278562f, 0.f};
    s1.second = {-54.3278562f, 1100.2444f};

    s2.first  = {4.f, 72.3672f};
    s2.second = {4.f, -22.f};

    auto p = utl::getIntersection(s1, s2);
    ASSERT_EQ(p.has_value(), false);

    p = utl::getIntersection(s2, s1);
    ASSERT_EQ(p.has_value(), false);
}