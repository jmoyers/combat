#include "parse.hpp"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace combat;
using namespace chrono_literals;

BOOST_AUTO_TEST_SUITE(combat_test_suite)

BOOST_AUTO_TEST_CASE(test_basic) {
  string melee = "[Thu May 28 18:47:41 2020] Kalos slashes orc legionnaire for "
                 "2 points of damage.";
  match_melee(melee);
}

BOOST_AUTO_TEST_SUITE_END()