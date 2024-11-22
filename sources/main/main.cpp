#include <iostream>
#include <memory>

#include "simulation/base_object.hpp"
#include "simulation/linear_border.hpp"

using DefScope = sml::BaseBorder::DefScope;

int
main()
{

    std::cout << __cplusplus << '\n';

    // sml::LinearBorder linear_b1(DefScope(0, 10), 2, 5);

    // sml::BaseBorderPtr linear_b2 =
    //     std::make_unique<sml::LinearBorder>(DefScope(0, 10), -1, 35);

    // std::cout << linear_b1.canConnect(
    //                  linear_b2, sml::BaseBorder::ConnectionWay::BEGIN_TO_END)
    //           << '\n';

    std::cout << "End\n";
}