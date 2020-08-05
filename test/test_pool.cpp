#include "pool.hpp"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace combat;
using namespace chrono_literals;

BOOST_AUTO_TEST_SUITE(combat_test_suite)

BOOST_AUTO_TEST_CASE(test_all) {
  WorkQueue<int> q;

  q.subscribe([](int v) { cout << &v << ":" << v << endl; });

  q.push_work([]() { return 42; });
  q.push_work([]() { return 51; });
  q.push_work([]() {
    this_thread::sleep_for(5ms);
    return 53;
  });

  q.join();
}

BOOST_AUTO_TEST_SUITE_END()