// define all the regular expressions for the known eq comat log types
// split a string into large enough chunks that we can dispatch to threadpool
// accumulate all the parsed and captured objects into a central store

#include <ctime>
#include <iostream>
#include <optional>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;

namespace combat {

unordered_map<string, int> months{
    {"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3}, {"May", 4},  {"Jun", 5},
    {"Jul", 6}, {"Aug", 7}, {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dev", 11},
};

class CombatEvent {
public:
  time_t time;

  string character;
  string verb;
  string target;

  int damage;

  CombatEvent(smatch &captures) {
    // 1 day_of_week
    // 2 month
    // 3 day
    // 4 hour
    // 5 minute
    // 6 second
    // 7 year
    // 8 character
    // 9 verb
    // 10 target
    // 11 damage

    struct tm info;

    info.tm_mon = months[captures[2]];
    info.tm_mday = stoi(captures[3]);
    info.tm_hour = stoi(captures[4]);
    info.tm_min = stoi(captures[5]);
    info.tm_sec = stoi(captures[6]);
    info.tm_year = stoi(captures[7]) - 1900;

    time = mktime(&info);

    character = captures[8];
    verb = captures[9];
    target = captures[10];
    damage = stoi(captures[11]);
  }
};

optional<CombatEvent> match_melee(string &line) {
  static regex pattern(
      R"regex(\[(\w+) (\w+) (\d+) (\d+):(\d+):(\d+) (\d+)\] (\w+[\w\s]+) (backstabs|bashes|bites|kicks|crushes|pierces|slashes|hits|hit) ([\w\s]+) for (\d+) point[s?] of damage\S)regex");

  smatch captures;

  if (regex_match(line, captures, pattern)) {
    return optional{CombatEvent(captures)};
  } else {
    return nullopt;
  }
}

} // namespace combat