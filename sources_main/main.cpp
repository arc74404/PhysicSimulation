#include <iostream>
#include <memory>

#include "simulation/base_object.hpp"
#include "simulation/linear_border.hpp"
#include "simulation/x_const_border.hpp"

using DefScope = sml::BaseFunctionBorder::DefScope;
using YLimit   = sml::XisConstBorder::YLimit;

int
main()
{

    std::cout << __cplusplus << '\n';

    // sml::LinearBorder linear_b1(DefScope(0, 10), 1, 0);

    // sml::BaseBorderPtr linear_b2 =
    //     std::make_unique<sml::XisConstBorder>(0, YLimit(0, 10));

    // std::cout << linear_b1.canConnect(
    //                  linear_b2,
    //                  sml::BaseBorder::ConnectionWay::BEGIN_TO_BEGIN)
    //           << '\n';

    std::cout << "End\n";
}