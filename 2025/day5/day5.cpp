#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  ifstream fin("day5.in");

  vector<pair<long long, long long>> ranges;

  vector<long long> nums;

  std::string line;
  while (std::getline(fin, line)) {
    if (!line.empty()) {
      size_t num_parsed;
      long long parsed_int = std::stoll(line, &num_parsed);

      if (num_parsed == line.size()) {
        nums.push_back(parsed_int);
      } else {
        long long next = std::stoll(line.substr(num_parsed + 1), &num_parsed);
        ranges.push_back(std::make_pair(parsed_int, next));
      }
    }
  }

  long long cnt = 0;

  for (auto const &num : nums) {
    bool valid = false;
    for (auto const &range : ranges) {
      if (range.first <= num && num <= range.second) {
        valid = true;
        break;
      }
    }
    if (valid)
      cnt++;
  }

  cout << cnt << endl;
}
