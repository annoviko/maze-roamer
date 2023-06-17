#include <gtest/gtest.h>

#include "engine/level_finder.h"


TEST(ut_level_finder, no_levels) {
    level_finder finder("ut-resources");
    auto levels = finder.get_levels();

    ASSERT_EQ(0, levels.size());
}
