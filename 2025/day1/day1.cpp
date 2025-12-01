#include <fstream>
#include <iostream>
#include <ranges>
#include <string_view>

using namespace std;

int main() {
  ifstream fin("day1.in");

  std::string line;
  int pos = 50;
  int cnt = 0;
  while (getline(fin, line)) {

    if (line.size() > 0) {
      char dir = line[0];

      std::string num = line.substr(1);
      int n = stoi(num);

      if (dir == 'R') {
        pos = (pos + n) % 100;
      } else {
        pos = (pos - n) % 100;
      }

      if (pos == 0) {
        cnt++;
      }
    }
  }

  cout << cnt << endl;
}
