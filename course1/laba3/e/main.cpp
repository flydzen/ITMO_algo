#include <iostream>
#include <vector>

using namespace std;

class Dsu {
 private:
     vector<int> parents;
     bool ranked;
     vector<int> ranks;

 public:
     Dsu(int n, bool rnkd) {
         parents.reserve(n);
         ranked = rnkd;
         ranks.reserve(n);
     }

     void init(int v) {
         parents[v] = v;
         ranks[v] = 0;
     }

     int find(int v) {
         if (v == parents[v]) {
             return v;
         } else {
             parents[v] = find(parents[v]);
             return parents[v];
         }
     }

     void onion(int a, int b) {
         a = find(a);
         b = find(b);
         if (a != b) {
             if (ranked) {
                 if (ranks[a] < ranks[b]) {
                     swap(a, b);
                 }
                 parents[b] = a;
                 if (ranks[a] == ranks[b]) {
                     ranks[a] += 1;
                 }
             } else {
                 parents[a] = b;
             }
         }
     }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    Dsu dsu(n, true);
    Dsu lines(n, false);
    for (int i = 0; i < n; i++) {
        dsu.init(i);
        lines.init(i);
    }
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        x--;
        y--;
        if (t == 1) {
            dsu.onion(x, y);
        } else if (t == 2) {
            while (x < y) {
                x = lines.find(x);
                if (x >= y) {
                    break;
                }
                lines.onion(x, x + 1);
                dsu.onion(x, x + 1);
            }
        } else {
            if (dsu.find(x) == dsu.find(y)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
