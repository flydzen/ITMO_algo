#include <iostream>
#include <vector>
using namespace std;

class Dsu {
 private:
  vector<int> parents;
  vector<int> ranks;
  vector<int> weights;

 public:
  explicit Dsu(int n) {
    for (int i = 0; i < n; i++) {
      init(i);
    }
  }

  void init(int v) {
    parents.push_back(v);
    ranks.push_back(1);
    weights.push_back(0);
  }

  int find(int v) {
    if (v != parents[v]) {
      weights[v] = (weights[v] + weights[parents[v]]) % 2;
      parents[v] = find(parents[v]);
    }
    return parents[v];
  }

  bool color(int x, int y) {
    find(x);
    find(y);
    return weights[x] == weights[y];
  }

  void onion(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (a != b) {
      if (ranks[a] < ranks[b]) {
        swap(a, b);
      }
      parents[b] = a;
      weights[b] = 1 - (weights[x] + weights[y]) % 2;
      if (ranks[a] == ranks[b]) {
        ranks[a] += 1;
      }
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  Dsu dsu(n);
  int shift = 0;
  for (int i = 0; i < m; i++) {
    int t, x, y;
    cin >> t >> x >> y;
    x = (x + shift) % n;
    y = (y + shift) % n;
    if (t == 0) {
      dsu.onion(x, y);
    } else {
      bool value = dsu.color(x, y);
      if (value) {
        shift++;
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }
  return 0;
}
