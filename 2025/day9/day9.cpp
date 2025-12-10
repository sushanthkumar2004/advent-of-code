#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Coord {
  long long x;
  long long y;
};

using namespace std;

int main() {
  ifstream fin("day9.in");
  std::string line;

  vector<Coord> coords;

  while (std::getline(fin, line)) {
    if (!line.empty()) {
      istringstream ss(line);

      long long x;
      ss >> x;
      char c;
      ss >> c;
      long long y;
      ss >> y;

      coords.push_back({x, y});
    }
  }

  long long maxArea = 0;

  for (long long i = 0; i < coords.size(); i++) {
    for (long long j = i + 1; j < coords.size(); j++) {
      Coord p1 = coords[i];
      Coord p2 = coords[j];

      auto l1 = abs(p1.x - p2.x) + 1;
      auto l2 = abs(p1.y - p2.y) + 1;

      maxArea = max(maxArea, l1 * l2);
    }
  }

  cout << maxArea << endl;
}