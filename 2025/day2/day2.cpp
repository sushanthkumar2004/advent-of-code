#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

constexpr int MAXDIGITS = 7;

// ll version of pow a^b
long long pow(long long a, long long b) {
  if (b == 0)
    return 1;
  if (b % 2 == 1) {
    long long x = pow(a, b / 2);
    return x * x * a;
  } else {
    long long x = pow(a, b / 2);
    return x * x;
  }
}

// returns all invalid nums with at least 20 digits
vector<long long> get_all_invalids() {
  vector<long long> ans;
  for (long long num_digits = 1; num_digits <= MAXDIGITS; num_digits++) {
    long long lower_range = pow(10, num_digits - 1);
    long long upper_range = pow(10, num_digits) - 1;

    for (long long num = lower_range; num <= upper_range; num++) {
      ans.push_back(num * (1 + pow(10, num_digits)));
    }
  }
  return ans;
}

int main() {
  ifstream fin("day2.in");

  std::string line;
  fin >> line;

  auto invalids = get_all_invalids();

  vector<vector<long long>> all_bounds;
  for (auto part : std::views::split(line, ',')) {
    vector<long long> bounds;
    for (auto num : std::views::split(part, '-')) {
      std::string n;
      for (char c : num) {
        n.push_back(c);
      }

      bounds.push_back(stoll(n));
    }
    all_bounds.push_back(bounds);
  }

  long long invalid_sum = 0;

  for (auto const &inv : invalids) {
    for (auto const &bound : all_bounds) {
      if (inv >= bound[0] && inv <= bound[1])
        invalid_sum += inv;
    }
  }

  cout << invalid_sum << endl;
}