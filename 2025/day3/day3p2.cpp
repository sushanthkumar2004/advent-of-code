#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long get_max(const std::string &line) {
  long long expected_digits = 12;

  vector<vector<long long>> dp(expected_digits + 1,
                               vector<long long>(line.size() + 1, 0));

  for (long long num_digits = 1; num_digits <= expected_digits; num_digits++) {
    for (long long i = 1; i <= line.size(); i++) {

      long long best_seen = 0;
      for (long long j = 0; j <= i - 1; j++) {
        best_seen = max(best_seen, dp[num_digits - 1][j]);
      }

      dp[num_digits][i] = best_seen * 10 + (line[i - 1] - '0');
    }
  }

  return *std::max_element(dp.back().begin(), dp.back().end());
}

int main() {
  ifstream fin("day3.in");

  std::string line;
  long long sum = 0;
  while (std::getline(fin, line)) {
    if (line.size() > 0) {
      sum += get_max(line);
    }
  }
  cout << sum << endl;
}