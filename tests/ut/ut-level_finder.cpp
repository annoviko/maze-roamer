#include <gtest/gtest.h>

#include "engine/level_finder.h"


TEST(ut_level_finder, two_levels) {
    level_finder finder("ut-resources/ut-level_finder");
    auto levels = finder.get_levels();

    ASSERT_EQ(2, levels.size());
    for (int i = 0; i < levels.size(); i++) {
        ASSERT_TRUE(levels[i].is_valid());

        auto map = levels[i].load();
        ASSERT_FALSE(map.empty());
    }
}


TEST(ut_level_finder, no_levels) {
    level_finder finder("ut-resources");
    auto levels = finder.get_levels();

    ASSERT_EQ(0, levels.size());
}
