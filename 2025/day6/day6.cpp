#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int numIntRow = 4;

int main() {
  ifstream fin("day6.in");

  vector<vector<long long>> all_ints;

  for (long long i = 0; i < numIntRow; i++) {
    vector<long long> next_row;
    std::string line;
    std::getline(fin, line);

    istringstream ss(line);
    long long x;
    while (ss >> x) {
      next_row.push_back(x);
    }
    all_ints.push_back(next_row);
  }

  vector<char> chars;
  char c;
  while (fin >> c) {
    chars.push_back(c);
  }

  long long sum = 0;
  for (long long j = 0; j < chars.size(); j++) {

    if (chars[j] == '*') {
      long long prod = 1;
      for (long long i = 0; i < numIntRow; i++) {
        prod *= all_ints[i][j];
      }
      sum += prod;
    } else {
      long long newSum = 0;
      for (long long i = 0; i < numIntRow; i++) {
        newSum += all_ints[i][j];
      }
      sum += newSum;
    }
  }
  cout << sum << endl;
}