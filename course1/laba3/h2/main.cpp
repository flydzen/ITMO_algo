#include <iostream>
#include <vector>
using namespace std;

class Dsu {
 private:
  vector<int> p;
  vector<int> colors;
  vector<unsigned long long> ranks;

 public:
  Dsu(int _n) {
    p.reserve(_n);
    colors.reserve(_n);
    ranks.reserve(_n);
    for (int i = 0; i < _n; i++) {
      init(i);
    }
  }

  void init(int v) {
    colors[v] = 0;
    p[v] = v;
    ranks[v] = 0;
  }

  int find(int v) {
    if (v != p[v]) {
      colors[v] = (colors[v] + colors[p[v]])%2;
      p[v] = find(p[v]);
    }
    return p[v];
  }

  void onion(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (a != b) {
      if (ranks[a] < ranks[b]) {
        swap(a, b);
      }
      p[b] = a;
      colors[b] = 1 - (colors[x] + colors[y])%2;
      if (ranks[a] == ranks[b]) {
        ranks[a] += 1;
      }
    }
  }

  bool color(int x, int y) {
    find(x);
    find(y);
    return colors[x] == colors[y];
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
