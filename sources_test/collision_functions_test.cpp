#include <gtest/gtest.h>

#include "util/collision_functions.hpp"
#include "util/extra_math_functions.hpp"

void
getIntersectionTest(const utl::Section& sec1, const utl::Section& sec2,
                    const utl::Point& correct_point)
{
    auto res = utl::CollisionHandler::getIntersection(sec1, sec2);
    ASSERT_EQ(res.has_value(), true);
    ASSERT_EQ(utl::isPointsEqual(*res, correct_point), true);
}

void
isIntersectTest(const utl::Section& sec1, const utl::Section& sec2,
                const utl::Point& correct_point)
{
    auto res = utl::CollisionHandler::isIntersect(sec1, sec2);
    ASSERT_EQ(res.has_value(), true);
    ASSERT_EQ(utl::isPointsEqual(*res, correct_point), true);
}

void
getReflectionVectorTest(const utl::Section& line, sf::Vector2f direction,
                        sf::Vector2f correct_result)
{
    sf::Vector2f refl_vector =
        utl::CollisionHandler::getReflectionVector(line, direction);

    ASSERT_EQ(utl::isPointsEqual(refl_vector, correct_result), true);
}

// Simple tests for UtilCollisionHandlerGetIntersection
//------------------------------------------------------------------------------

TEST(UtilCollisionHandlerGetIntersection, get_intersection_regular_and_regular)
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

TEST(UtilCollisionHandlerGetIntersection, get_intersection_parallel)
{
    utl::Section s1, s2;
    s1.first  = {0, 7.33f};
    s1.second = {0 - 4.1f, 7.33f - 10.f};

    s2.first  = {0, -3.191};
    s2.second = {0 - 4.1f, -3.191 - 10.f};

    auto res = utl::CollisionHandler::getIntersection(s1, s2);
    ASSERT_EQ(res.has_value(), false);
    res = utl::CollisionHandler::getIntersection(s2, s1);
    ASSERT_EQ(res.has_value(), false);
}

TEST(UtilCollisionHandlerGetIntersection,
     get_intersection_perpendicular_and_regular)
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

TEST(UtilCollisionHandlerGetIntersection,
     get_intersection_perpendicular_and_perpendicular)
{
    utl::Section s1, s2;
    s1.first  = {-54.3278562f, 0.f};
    s1.second = {-54.3278562f, 1100.2444f};

    s2.first  = {4.f, 72.3672f};
    s2.second = {4.f, -22.f};

    auto res = utl::CollisionHandler::getIntersection(s1, s2);
    ASSERT_EQ(res.has_value(), false);

    res = utl::CollisionHandler::getIntersection(s2, s1);
    ASSERT_EQ(res.has_value(), false);
}

//------------------------------------------------------------------------------
// Simple tests for UtilCollisionHandlerIsIntersect
//------------------------------------------------------------------------------

TEST(UtilCollisionHandlerIsIntersect, is_intersect_regular_and_regular_true)
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

TEST(UtilCollisionHandlerIsIntersect, is_intersect_regular_and_regular_false)
{
    utl::Section sec1 = {
        {-3.f, -3.f},
        {6.f,  1.f }
    };
    utl::Section sec2 = {
        {2.f, 2.f},
        {1.f, 1.f}
    };
    auto res = utl::CollisionHandler::isIntersect(sec1, sec2);
    ASSERT_EQ(res.has_value(), false);

    res = utl::CollisionHandler::isIntersect(sec2, sec1);
    ASSERT_EQ(res.has_value(), false);
}

//------------------------------------------------------------------------------
// Simple tests for UtilCollisionHandlerGetDistance
//------------------------------------------------------------------------------

TEST(UtilCollisionHandlerGetDistance, get_distance_int_coordinates)
{
    utl::Point p1, p2;

    p1 = {0.f, 0.f};
    p2 = {4.f, 3.f};

    auto res = utl::CollisionHandler::getDistance(p1, p2);
    ASSERT_EQ(utl::isFloatsEqual(res, 5.f), true);
    res = utl::CollisionHandler::getDistance(p2, p1);
    ASSERT_EQ(utl::isFloatsEqual(res, 5.f), true);
    ////////////////////////
    p1  = {-1.f, -1.f};
    p2  = {11.f, 8.f};
    res = utl::CollisionHandler::getDistance(p1, p2);
    ASSERT_EQ(utl::isFloatsEqual(res, 15.f), true);
    res = utl::CollisionHandler::getDistance(p2, p1);
    ASSERT_EQ(utl::isFloatsEqual(res, 15.f), true);
}

//------------------------------------------------------------------------------
// Difficult tests for UtilCollisionHandlerGetDistance
//------------------------------------------------------------------------------

TEST(UtilCollisionHandlerGetDistance, get_distance_float_coordinates)
{
    utl::Point p1, p2;

    p1 = {12952.f / 27.f, -235.22f};
    p2 = {5.f / 7.f, -3.f / 53.f};

    float correct_res = std::sqrt(17856349967556372.f) / 250425.f;

    auto res = utl::CollisionHandler::getDistance(p1, p2);
    ASSERT_EQ(utl::isFloatsEqual(res, correct_res, 3), true);
    res = utl::CollisionHandler::getDistance(p2, p1);
    ASSERT_EQ(utl::isFloatsEqual(res, correct_res, 3), true);
}

//------------------------------------------------------------------------------
// Simple tests for UtilCollisionHandlerGetCounterDirectionalRay
//------------------------------------------------------------------------------

TEST(UtilCollisionHandlerGetCounterDirectionalRay,
     get_counter_directional_ray_int_coordinates)
{
    sf::Vector2f vec = {4.f, -3.f};

    utl::Point p = {-1.f, -2.f};

    utl::Section res = utl::CollisionHandler::getCounterDirectionalRay(vec, p);

    utl::Section correct_section;
    correct_section.first  = p;
    correct_section.second = {p.x - 4000.f, p.y + 3000.f};

    ASSERT_EQ(res, correct_section);
}

//------------------------------------------------------------------------------
// Simple tests for UtilCollisionHandlerGetReflectionVector
//------------------------------------------------------------------------------

TEST(UtilCollisionHandlerGetReflectionVector,
     get_reflection_vector_x1_0_y1_0_x1_10_y1_0_line)
{
    utl::Section line = {
        {0,  0},
        {10, 0}
    };
    sf::Vector2f direction      = {4, -3};
    sf::Vector2f correct_result = {4, 3};

    getReflectionVectorTest(line, direction, correct_result);

    direction      = {4.3, 3.2};
    correct_result = {4.3, -3.2};
    getReflectionVectorTest(line, direction, correct_result);

    direction      = {-4.3, 3.2};
    correct_result = {-4.3, -3.2};
    getReflectionVectorTest(line, direction, correct_result);

    direction      = {-4.3, -3.2};
    correct_result = {-4.3, 3.2};
    getReflectionVectorTest(line, direction, correct_result);
}

TEST(UtilCollisionHandlerGetReflectionVector,
     get_reflection_vector_x1_11_y1_11_x1_44_y1_44_line)
{
    utl::Section line = {
        {11, 11},
        {44, 44}
    };
    sf::Vector2f direction      = {10, 0};
    sf::Vector2f correct_result = {0, 10};

    getReflectionVectorTest(line, direction, correct_result);

    direction      = {4, -4};
    correct_result = {-4, 4};

    getReflectionVectorTest(line, direction, correct_result);
}