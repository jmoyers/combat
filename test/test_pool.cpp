#include "pool.hpp"
#include <iostream>
#include <unordered_set>
#include "gtest/gtest.h"

using namespace std;
using namespace combat;
using namespace chrono_literals;

TEST(pool, test_push_work_subscribe) {
  WorkQueue<int> q;

  unordered_set<int> expected{42, 51, 53};

  q.subscribe([&](int v) {
    expected.erase(v);
  });

  q.push_work([]() { return 42; });
  q.push_work([]() { return 51; });
  q.push_work([]() {
    this_thread::sleep_for(5ms);
    return 53;
  });

  q.join();

  EXPECT_EQ(expected.empty(), true);
}