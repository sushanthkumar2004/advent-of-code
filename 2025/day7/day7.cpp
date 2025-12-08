#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using COORD = pair<int, int>;

COORD findStart(const vector<vector<char>> &grid) {
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 'S') {
        return {i, j};
      }
    }
  }
  return {-1, -1};
}

int main() {
  ifstream fin("day7.in");

  vector<vector<char>> grid;

  std::string line;
  while (std::getline(fin, line)) {
    if (line.size() != 0) {
      grid.push_back(vector<char>(line.begin(), line.end()));
    }
  }

  COORD start = findStart(grid);
  set<COORD> active_beams;
  active_beams.insert(start);
  int numSplits = 0;

  for (size_t i = 0; i < grid.size() - 1; i++) {
    vector<COORD> remove_beams;
    for (auto &beam : active_beams) {
      remove_beams.push_back(beam);
    }

    active_beams.clear();

    for (auto &beam : remove_beams) {
      auto [x, y] = beam;
      active_beams.insert({x + 1, y});
    }

    vector<COORD> split_beams;
    for (auto const &beam : active_beams) {
      auto [x, y] = beam;
      if (grid[x][y] == '^') {
        numSplits++;
        split_beams.push_back({x, y});
      }
    }

    for (auto &beam : split_beams) {
      auto [x, y] = beam;
      active_beams.erase(beam);
      if (y + 1 < grid[0].size())
        active_beams.insert({x, y + 1});
      if (y >= 1)
        active_beams.insert({x, y - 1});
    }
  }

  cout << numSplits << endl;
}