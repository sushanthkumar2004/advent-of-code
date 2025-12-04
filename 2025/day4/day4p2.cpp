#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool done_simplifying(vector<string> *grid) {
  long long fork_liftable = 0;
  for (long long i = 0; i < grid->size(); i++) {
    for (long long j = 0; j < (*grid)[0].size(); j++) {
      long long dirx[] = {0, 1, 1, 1, 0, -1, -1, -1};
      long long diry[] = {1, 1, 0, -1, -1, -1, 0, 1};

      long long boxes_around = 0;

      for (long long dir = 0; dir < 8; dir++) {
        long long ni = i + dirx[dir];
        long long nj = j + diry[dir];

        if (ni >= 0 && nj >= 0 && ni < grid->size() && nj < (*grid)[0].size() &&
            (*grid)[ni][nj] == '@') {
          boxes_around++;
        }
      }

      if (boxes_around < 4 && (*grid)[i][j] == '@') {
        fork_liftable++;
        (*grid)[i][j] = '.';
      }
    }
  }
  return fork_liftable == 0;
}

int main() {
  ifstream fin("day4.in");

  vector<string> grid;

  std::string line;
  while (std::getline(fin, line)) {
    if (!line.empty()) {
      grid.push_back(line);
    }
  }

  long long starting = 0;
  for (long long i = 0; i < grid.size(); i++) {
    for (long long j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == '@') {
        starting++;
      }
    }
  }

  while (!done_simplifying(&grid)) {
  }

  long long left_over = 0;
  for (long long i = 0; i < grid.size(); i++) {
    for (long long j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == '@') {
        left_over++;
      }
    }
  }

  cout << starting - left_over << endl;
}