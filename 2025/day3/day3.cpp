#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int get_max(const std::string &line) {
  int max_val = 0;
  for (int i = 0; i < line.size(); i++) {
    for (int j = i + 1; j < line.size(); j++) {
      int first = line[i] - '0';
      int second = line[j] - '0';

      max_val = std::max(max_val, first * 10 + second);
    }
  }
  return max_val;
}

int main() {
  ifstream fin("day3.in");

  std::string line;
  int sum = 0;
  while (std::getline(fin, line)) {
    if (line.size() > 0) {
      sum += get_max(line);
    }
  }
  cout << sum << endl;
}