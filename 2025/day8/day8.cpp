#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <print>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

constexpr int NUM_CONNECTED = 1000;

class DSU {
public:
  vector<long long> parents;
  vector<long long> weights;
  long long size;
  long long num_islands;

  DSU(long long N) {
    size = N;
    parents = vector<long long>(N, 0);
    weights = vector<long long>(N, 1);

    for (long long i = 0; i < N; i++) {
      parents[i] = i;
    }
    num_islands = N;
  }

  long long getParent(long long A) {
    if (parents[A] == A) {
      return A;
    }

    auto X = getParent(parents[A]);
    parents[A] = X;
    return X;
  }

  bool isConnected(long long A, long long B) {
    return getParent(A) == getParent(B);
  }

  void connect(long long A, long long B) {
    long long pa = getParent(A);
    long long pb = getParent(B);
    if (pa != pb) {
      num_islands--;
      //   cout << pa << " " << pb << "!" << endl;
      //   cout << A << " " << B << "!" << endl;
      auto wa = weights[pa];
      auto wb = weights[pb];

      if (wa <= wb) {
        weights[pb] += wa;
        parents[pa] = pb;
      } else {
        parents[pb] = pa;
        weights[pa] += wb;
      }
    }
  }

  long long topThreeProduct() {
    for (long long i = 0; i < size; i++) {
      getParent(i);
    }

    map<long long, long long> cnts;

    vector<long long> cntsTop;

    for (int i = 0; i < size; i++) {
      cnts[parents[i]]++;
    }

    for (auto const &q : cnts) {
      cntsTop.push_back(q.second);
    }

    sort(cntsTop.begin(), cntsTop.end(), greater<long long>());

    // cout << cntsTop[0] << " " << cntsTop[1] << " " << cntsTop[2] << endl;

    return cntsTop[0] * cntsTop[1] * cntsTop[2];
  }
};

struct Coord {
  long long x;
  long long y;
  long long z;
};

int main() {
  ifstream fin("day8.in");

  vector<Coord> coords;

  string line;
  while (std::getline(fin, line)) {
    if (!line.empty()) {
      std::stringstream ss(line);
      std::string item;
      std::vector<long long> vals;

      while (std::getline(ss, item, ',')) {
        vals.push_back(std::stoll(item));
      }

      coords.push_back({vals[0], vals[1], vals[2]});
    }
  }

  vector<vector<long long>> distances(coords.size(),
                                      vector<long long>(coords.size()));

  map<long long, pair<long long, long long>> traversal;
  auto dsu = DSU(coords.size());

  for (long long i = 0; i < coords.size(); i++) {
    for (long long j = i + 1; j < coords.size(); j++) {
      auto A = coords[i];
      auto B = coords[j];
      distances[i][j] = (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) +
                        (A.z - B.z) * (A.z - B.z);
      traversal[distances[i][j]] = {i, j};
    }
  }

  long long num_connected = 0;
  for (auto const &pairs : traversal) {
    long long d = pairs.first;
    auto [i, j] = pairs.second;

    num_connected += 1;

    if (!dsu.isConnected(i, j)) {
      //   cout << "!" << i << " " << j << " " << distances[i][j] << endl;
      dsu.connect(i, j);
    }

    if (num_connected == NUM_CONNECTED) {
      break;
    }
  }

  std::println("{}", dsu.topThreeProduct());
}