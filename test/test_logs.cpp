#include "logs.hpp"
#include "gtest/gtest.h"
#include <unordered_set>

using namespace std;

TEST(logs, test_find_files) {
  auto files = find_files("fixtures");

  unordered_set<string> expected{
      "fixtures/test.txt",
      "fixtures/test2.txt",
      "fixtures/eqlog_test.txt",
      "fixtures/eqlog_something_server.txt",
  };

  for (auto const &f : files) {
    expected.erase(f);
  }

  EXPECT_EQ(expected.empty(), true);
}

TEST(logs, test_filter_files) {
  auto files = find_files("fixtures");
  filter_logs(files);

  unordered_set<string> expected{
      "fixtures/eqlog_test.txt",
      "fixtures/eqlog_something_server.txt",
  };

  int count = 0;

  for (auto const &f : files) {
    count++;
    expected.erase(f);
  }

  EXPECT_EQ(expected.empty(), true);
  EXPECT_EQ(count, 2);
}

TEST(logs,test_read_log) {
  string filename = "fixtures/eqlog_something_server.txt";
  string contents =
      R"([Thu May 28 18:47:41 2020] Kalos slashes orc legionnaire for 2 points of damage.
[Thu May 28 18:47:55 2020] Zanther tries to pierce orc centurion, but misses!
[Thu May 28 18:47:26 2020] You hit orc legionnaire for 5 points of physical damage by Elbow Strike.
[Thu May 28 18:47:27 2020] Orc legionnaire has taken 6 damage from Flame Lick by
Nekkon.
[Thu May 28 18:58:24 2020] Jenarie's Healing spell is interrupted.
[Thu May 28 18:58:22 2020] Jenarie begins casting Healing.)";

  auto read_contents = read_log(filename);

  auto compare = read_contents.compare(contents);

  EXPECT_EQ(compare, 0);
}
