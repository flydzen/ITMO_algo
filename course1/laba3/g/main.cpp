#include <iostream>
#include <vector>
#include <algorithm>

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
         for (int i = 0; i < n; i++) {
             init(i);
         }
     }

     void init(int v) {
         parents[v] = v;
         ranks[v] = 0;
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

bool comp(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2) {
    return p1.second > p2.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dsu dsu(n, false);
    vector<int> wghs(n);
    for (int i = 0; i < n; i++) {
        wghs[i] = 1488;
    }
    vector<pair<pair<int, int>, int>> req;
    for (int i = 0; i < m; i++) {
        int l, r, w;
        cin >> l >> r >> w;
        req.emplace_back(make_pair(l - 1, r - 1), w);
    }
    sort(req.begin(), req.end(), comp);
    for (int i = 0; i < m; i++) {
        int l = req[i].first.first;
        int r = req[i].first.second;
        int w = req[i].second;
        while (l <= r) {
            l = dsu.find(l);
            if (l > r) {
                break;
            }
            if (wghs[l] == 1488) {
                wghs[l] = w;
            }
            if (l == n - 1) {
                break;
            }
            dsu.onion(l, l + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << wghs[i] << " ";
    }
    return 0;
}
