#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool checkEmpty(std::string s) {
  return std::all_of(s.begin(), s.end(), [&](char x) { return x == ' '; });
}

int main() {
  ifstream fin("day6.in");

  vector<vector<char>> grid;

  std::string line;
  while (std::getline(fin, line)) {
    if (line.size() != 0) {
      grid.push_back(vector<char>(line.begin(), line.end()));
    }
  }

  char potential_op = 0;

  long long total_sum = 0;
  long long prod = 1;
  long long sum = 0;

  bool sumFlag = false;

  for (size_t col = 0; col < grid[0].size(); col++) {
    std::string column = "";
    for (size_t row = 0; row < grid.size(); row++) {
      column += grid[row][col];
    }

    if (!checkEmpty(column)) {
      long long num = stoll(column);

      if (potential_op != 0) {
        // potential_op is either + or *
        if (potential_op == '*') {
          prod *= num;
        } else {
          sum += num;
        }
      } else {
        potential_op = column[grid.size() - 1];
        if (potential_op == '*') {
          prod *= num;
        } else {
          sumFlag = true;
          sum += num;
        }
      }
    } else {

      // cout << "BRUH" << ((sumFlag) ? sum : prod) << endl;
      total_sum += ((sumFlag) ? sum : prod);
      sum = 0;
      prod = 1;
      potential_op = 0;
      sumFlag = false;
    }
  }

  total_sum += ((sumFlag) ? sum : prod);

  cout << total_sum;
}