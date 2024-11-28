#include <gmock/gmock.h>
#include <gtest/gtest.h>

// #include "core/logging/logging.hpp"

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
