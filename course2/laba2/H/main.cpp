#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


class Dsu {
 private:
     vector<int> parents;
     bool ranked;
     vector<int> ranks;

 public:
     explicit Dsu(int n, bool rnkd = true) {
         n++;
         parents = vector<int>(n);
         ranked = rnkd;
         ranks = vector<int>(n);
         for (int i = 0; i < n; i++) {
             init(i);
         }
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

struct edge {
    int from;
    int to;
    int w;
    edge(int from, int to, int w) {
        this->from = from;
        this->to = to;
        this->w = w;
    }
};

bool comp(edge &e1, edge &e2) {
    return e1.w < e2.w;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<edge> e;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        e.emplace_back(a, b, w);
    }
    sort(e.begin(), e.end(), comp);
    int cou = 0;
    int result = 0;
    Dsu dsu(n);
    for (size_t i = 0; i < e.size() && cou < n; i++) {
        edge &uv = e[i];
        if (dsu.find(uv.from) != dsu.find(uv.to)) {
            dsu.onion(uv.from, uv.to);
            cou++;
            result += uv.w;
        }
    }
    cout << result;
    return 0;
}
