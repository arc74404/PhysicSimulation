#include <gtest/gtest.h>

#include "util/collision_functions.hpp"
#include "util/extra_math_functions.hpp"

void
getIntersectionTest(utl::Section sec1, utl::Section sec2,
                    utl::Point correct_point)
{
    auto res = utl::getIntersection(sec1, sec2);
    ASSERT_EQ(res.has_value(), true);
    ASSERT_EQ(utl::isPointsEqual(*res, correct_point), true);
}

void
isIntersectTest(utl::Section sec1, utl::Section sec2, utl::Point correct_point)
{
    auto res = utl::isIntersect(sec1, sec2);
    ASSERT_EQ(res.has_value(), true);
    ASSERT_EQ(utl::isPointsEqual(*res, correct_point), true);
}

// Simple tests for UtilGetIntersection
//------------------------------------------------------------------------------

TEST(UtilGetIntersection, get_intersection_regular_and_regular)
{
    utl::Section s1, s2;
    s1.first  = {-1.f, 8.f};
    s1.second = {4.f, 0.2};

    s2.first  = {-2.f, -6.f};
    s2.second = {6.f, 3.f};

    utl::Point correct_point = {2038.f / 537.f, 93.f / 179.f};

    getIntersectionTest(s1, s2, correct_point);
    getIntersectionTest(s2, s1, correct_point);
}

TEST(UtilGetIntersection, get_intersection_parallel)
{
    utl::Section s1, s2;
    s1.first  = {0, 7.33f};
    s1.second = {0 - 4.1f, 7.33f - 10.f};

    s2.first  = {0, -3.191};
    s2.second = {0 - 4.1f, -3.191 - 10.f};

    auto res = utl::getIntersection(s1, s2);
    ASSERT_EQ(res.has_value(), false);
    res = utl::getIntersection(s2, s1);
    ASSERT_EQ(res.has_value(), false);
}

TEST(UtilGetIntersection, get_intersection_perpendicular_and_regular)
{
    utl::Section s1, s2;
    s1.first  = {-2.f, 0.f};
    s1.second = {6.f, -4.f};

    s2.first  = {4.f, 72.3672f};
    s2.second = {4.f, -22.f};

    utl::Point correct_point = {4.f, -3.f};
    getIntersectionTest(s1, s2, correct_point);
    getIntersectionTest(s2, s1, correct_point);
}

TEST(UtilGetIntersection, get_intersection_perpendicular_and_perpendicular)
{
    utl::Section s1, s2;
    s1.first  = {-54.3278562f, 0.f};
    s1.second = {-54.3278562f, 1100.2444f};

    s2.first  = {4.f, 72.3672f};
    s2.second = {4.f, -22.f};

    auto res = utl::getIntersection(s1, s2);
    ASSERT_EQ(res.has_value(), false);

    res = utl::getIntersection(s2, s1);
    ASSERT_EQ(res.has_value(), false);
}

//------------------------------------------------------------------------------
// Simple tests for UtilIsIntersect
//------------------------------------------------------------------------------

TEST(UtilIsIntersect, is_intersect_regular_and_regular_true)
{
    utl::Section sec1 = {
        {-4.f, 3.f},
        {5.f,  0.f}
    };
    utl::Section sec2 = {
        {-1.f, -8.f},
        {4.f,  10.f}
    };

    utl::Point correct_point({91.f / 59.f, 68.f / 59.f});

    isIntersectTest(sec1, sec2, correct_point);
    isIntersectTest(sec2, sec1, correct_point);

    std::swap(sec1.first, sec1.second);
    isIntersectTest(sec1, sec2, correct_point);
    isIntersectTest(sec2, sec1, correct_point);

    std::swap(sec2.first, sec2.second);
    isIntersectTest(sec1, sec2, correct_point);
    isIntersectTest(sec2, sec1, correct_point);
}

TEST(UtilIsIntersect, is_intersect_regular_and_regular_false)
{
    utl::Section sec1 = {
        {-3.f, -3.f},
        {6.f,  1.f }
    };
    utl::Section sec2 = {
        {2.f, 2.f},
        {1.f, 1.f}
    };
    auto res = utl::isIntersect(sec1, sec2);
    ASSERT_EQ(res.has_value(), false);

    res = utl::isIntersect(sec2, sec1);
    ASSERT_EQ(res.has_value(), false);
}

//------------------------------------------------------------------------------
// Simple tests for UtilGetDistance
//------------------------------------------------------------------------------

TEST(UtilGetDistance, get_distance_int_coordinates)
{
    utl::Point p1, p2;

    p1 = {0.f, 0.f};
    p2 = {4.f, 3.f};

    auto res = utl::getDistance(p1, p2);
    ASSERT_EQ(utl::isFloatsEqual(res, 5.f), true);
    res = utl::getDistance(p2, p1);
    ASSERT_EQ(utl::isFloatsEqual(res, 5.f), true);
    ////////////////////////
    p1  = {-1.f, -1.f};
    p2  = {11.f, 8.f};
    res = utl::getDistance(p1, p2);
    ASSERT_EQ(utl::isFloatsEqual(res, 15.f), true);
    res = utl::getDistance(p2, p1);
    ASSERT_EQ(utl::isFloatsEqual(res, 15.f), true);
}

//------------------------------------------------------------------------------
// Difficult tests for UtilGetDistance
//------------------------------------------------------------------------------

TEST(UtilGetDistance, get_distance_float_coordinates)
{
    utl::Point p1, p2;

    p1 = {12952.f / 27.f, -235.22f};
    p2 = {5.f / 7.f, -3.f / 53.f};

    float correct_res = std::sqrt(17856349967556372.f) / 250425.f;

    auto res = utl::getDistance(p1, p2);
    ASSERT_EQ(utl::isFloatsEqual(res, correct_res, 3), true);
    res = utl::getDistance(p2, p1);
    ASSERT_EQ(utl::isFloatsEqual(res, correct_res, 3), true);
}

//------------------------------------------------------------------------------
// Simple tests for UtilGetCounterDirectionalRay
//------------------------------------------------------------------------------

TEST(UtilGetCounterDirectionalRay, get_counter_directional_ray_int_coordinates)
{
    sf::Vector2f vec = {4.f, -3.f};

    utl::Point p = {-1.f, -2.f};

    utl::Section res = utl::getCounterDirectionalRay(vec, p);

    utl::Section correct_section;
    correct_section.first  = p;
    correct_section.second = {-5000, 1000};

    ASSERT_EQ(res, correct_section);
}
