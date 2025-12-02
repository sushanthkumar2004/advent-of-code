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
        int turns = 0;
        if (pos + n >= 100) {
          turns = (pos + n) / 100;
        }

        cnt += turns;

        pos = (pos + n) % 100;
      } else {
        int turns = 0;
        if (pos - n <= 0 && pos != 0) {
          turns = (n - pos + 100) / 100;
        } else if (pos - n <= 0 && pos == 0) {
          turns = (n - pos) / 100;
        }
        cnt += turns;
        pos = (100 + (pos - n) % 100) % 100;
      }
    }
  }

  cout << cnt << endl;
}
