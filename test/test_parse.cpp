#include "parse.hpp"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace combat;
using namespace chrono_literals;

BOOST_AUTO_TEST_SUITE(combat_test_suite)

BOOST_AUTO_TEST_CASE(test_melee_parse) {
  string melee = "[Thu May 28 18:47:41 2020] Kalos slashes orc legionnaire for "
                 "2 points of damage.";
  CombatEvent event = match_melee(melee).value();

  assert(event.character == "Kalos");
  assert(event.damage == 2);
  assert(event.verb == "slashes");
  assert(event.target == "orc legionnaire");
  assert(event.time == 1590716861);
}

BOOST_AUTO_TEST_SUITE_END()