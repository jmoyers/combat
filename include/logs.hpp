#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// enumerate all the files in a log directory
// Q: is it better to use an iterator to be c++ idiomatic?
vector<fs::path> find_files(const string directory) {
  vector<fs::path> files;
  for (auto const &f : fs::directory_iterator(directory)) {
    files.push_back(f.path());
  }
  return files;
}

// this is a function instead of a lambda because debugger was not working with
// lambda, big sad
bool is_eq_log(fs::path path) {
  return "eqlog" != path.filename().string().substr(0, 5);
}

// filter by files that look like logs based on their filename
void filter_logs(vector<fs::path> &files) {
  files.erase(remove_if(files.begin(), files.end(), is_eq_log), files.end());
}

// load a log into memory from a file, all at once
// this method seems to avoid extra copies and uses new c++17 feature to
// retrieve the file size in a platform independent way
// Q: is string return created like this RVO'd?
string read_log(fs::path path) {
  ifstream f(path, ios::in | ios::binary);

  const auto size = fs::file_size(path);
  string buffer(size, '\0');

  f.read(buffer.data(), size);

  return buffer;
}