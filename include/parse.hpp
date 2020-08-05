// define all the regular expressions for the known eq comat log types
// split a string into large enough chunks that we can dispatch to threadpool
// accumulate all the parsed and captured objects into a central store

#include <iostream>
#include <regex>
#include <string>

using namespace std;

namespace combat {

// day_of_week
// month
// day
// hour
// minute
// second
// year
// character
// verb
// target
// damage

void match_melee(string &line) {
  static regex pattern(
      R"regex(\[(\w+) (\w+) (\d+) (\d+):(\d+):(\d+) (\d+)\] (\w+[\w\s]+) (backstabs|bashes|bites|kicks|crushes|pierces|slashes|hits|hit) ([\w\s]+) for (\d+) point[s?] of damage\S)regex");

  smatch captures;

  if (regex_match(line, captures, pattern)) {
    for (auto &c : captures) {
      cout << c << endl;
    }
  }
}

} // namespace combat