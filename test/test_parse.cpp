#include "parse.hpp"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;
using namespace combat;
using namespace chrono_literals;

TEST(parse, test_melee_parse) {
  string melee = "[Thu May 28 18:47:41 2020] Kalos slashes orc legionnaire for "
                 "2 points of damage.";
  CombatEvent event = match_melee(melee).value();

  EXPECT_EQ(event.character, "Kalos");
  EXPECT_EQ(event.damage, 2);
  EXPECT_EQ(event.verb, "slashes");
  EXPECT_EQ(event.target, "orc legionnaire");
  EXPECT_EQ(event.time, 1590716861);
}