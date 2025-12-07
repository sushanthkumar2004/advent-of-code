#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

bool non_intersect(pair<unsigned long long, unsigned long long> A,
                   pair<unsigned long long, unsigned long long> B) {
  return (A.second < B.first);
}

int main() {
  ifstream fin("day5.in");

  vector<pair<unsigned long long, unsigned long long>> ranges;

  std::string line;
  while (std::getline(fin, line)) {
    if (!line.empty()) {
      size_t num_parsed;
      unsigned long long parsed_int = std::stoll(line, &num_parsed);

      if (num_parsed == line.size()) {
        break;
      } else {
        unsigned long long next =
            std::stoll(line.substr(num_parsed + 1), &num_parsed);
        ranges.push_back(std::make_pair(parsed_int, next));
      }
    }
  }

  vector<pair<unsigned long long, unsigned long long>> union_ranges;

  sort(ranges.begin(), ranges.end());

  for (auto const &range : ranges) {
    if (union_ranges.empty() || non_intersect(union_ranges.back(), range)) {
      union_ranges.push_back(range);
    } else {
      union_ranges.back().second =
          max(union_ranges.back().second, range.second);
    }
  }

  unsigned long long len = 0;
  for (auto const &range : union_ranges) {
    len += range.second - range.first + 1;
  }

  cout << len << endl;
}
