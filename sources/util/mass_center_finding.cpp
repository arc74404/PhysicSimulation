#include "mass_center_finding.hpp"


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