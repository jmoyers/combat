
#include "logs.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <unordered_set>

using namespace std;

BOOST_AUTO_TEST_SUITE(combat_test_suite)

BOOST_AUTO_TEST_CASE(test_find_files) {
  auto files = find_files("test/fixtures");

  unordered_set<string> expected{
      "test/fixtures/test.txt",
      "test/fixtures/test2.txt",
      "test/fixtures/eqlog_test.txt",
      "test/fixtures/eqlog_something_server.txt",
  };

  for (auto const &f : files) {
    expected.erase(f);
  }

  BOOST_ASSERT(expected.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_filter_files) {
  auto files = find_files("test/fixtures");
  filter_logs(files);

  unordered_set<string> expected{
      "test/fixtures/eqlog_test.txt",
      "test/fixtures/eqlog_something_server.txt",
  };

  int count = 0;

  for (auto const &f : files) {
    count++;
    expected.erase(f);
  }

  BOOST_ASSERT(expected.size() == 0);
  BOOST_ASSERT(count == 2);
}

BOOST_AUTO_TEST_CASE(test_read_log) {
  string filename = "test/fixtures/eqlog_something_server.txt";
  string contents =
      R"([Thu May 28 18:47:41 2020] Kalos slashes orc legionnaire for 2 points of damage.
[Thu May 28 18:47:55 2020] Zanther tries to pierce orc centurion, but misses!
)";

  auto read_contents = read_log(filename);

  auto compare = read_contents.compare(contents);

  // BOOST_ASSERT(compare == 0);
}
BOOST_AUTO_TEST_SUITE_END()