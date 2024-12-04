#include "mass_center_finding.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

bool
utl::isPointInPolygon(const Point& p, const std::vector<Point>& polygon)
{
    int n = polygon.size();

    int intersections = 0;

    for (int i = 0; i < n; ++i)
    {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];

        // Пропускаем горизонтальные отрезки
        if (p1.y == p2.y) continue;

        // Пропускаем отрезки, которые не пересекаются с лучом
        if ((p.y < std::min(p1.y, p2.y)) || (p.y >= std::max(p1.y, p2.y)))
            continue;

        // Вычисляем точку пересечения луча с отрезком
        double vt = (p.y - p1.y) / (p2.y - p1.y);

        double intersectionX = p1.x + vt * (p2.x - p1.x);

        if (intersectionX > p.x) intersections++;
    }

    return intersections % 2 == 1;
}

// utl::Point
// utl::calculateCenterOfMassMonteCarlo(const std::vector<Point>& polygon,
//                                      int numSamples)
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     double minX = polygon[0].x, minY = polygon[0].y, maxX = polygon[0].x,
//            maxY = polygon[0].y;
//     for (const auto& p : polygon)
//     {
//         // minX = std::min(minX, p.x);
//         // minY = std::min(minY, p.y);
//         // maxX = std::max(maxX, p.x);
//         // maxY = std::max(maxY, p.y);
//     }

//     std::uniform_real_distribution<> distribX(minX, maxX);
//     std::uniform_real_distribution<> distribY(minY, maxY);

//     double totalX = 0.0, totalY = 0.0, numInside = 0.0;
//     for (int i = 0; i < numSamples; ++i)
//     {
//         // Point p = {distribX(gen), distribY(gen)};

//         if (isPointInPolygon(p, polygon))
//         {
//             totalX += p.x;
//             totalY += p.y;
//             numInside++;
//         }
//     }

//     return {totalX / numInside, totalY / numInside};
// }
