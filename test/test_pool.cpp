#include "pool.hpp"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace combat;

BOOST_AUTO_TEST_SUITE(combat_test_suite)

BOOST_AUTO_TEST_CASE(test_all) {
  WorkQueue<int> q;
  q.push_work([]() { return 42; });
}

BOOST_AUTO_TEST_SUITE_END()