#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

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

inline bool operator<(const edge &e1, const edge &e2) {
    if (e1.w != e2.w)
        return e1.w > e2.w;
    else if (e1.from != e2.from)
        return e1.from > e2.from;
    else
        return e1.to > e2.to;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;
    vector<vector<edge>> ss(n);
    for (size_t i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        ss[a].push_back({a, b, w});
    }
    long long res = 0;
    priority_queue<edge> q;
    for (size_t i = 0; i < ss[0].size(); i++) {
        q.push(ss[0][i]);
    }
    vector<bool> used(n);
    used[0] = true;
    size_t cou = 0;
    while (!q.empty() && cou != n - 1) {
        edge e = q.top();
        q.pop();
        if (used[e.to]) {
            continue;
        }
        cou++;
        used[e.to] = true;
        res += e.w;
        for (size_t i = 0; i < ss[e.to].size(); i++) {
            if (!used[ss[e.to][i].to]) {
                q.push(ss[e.to][i]);
            }
        }
    }
    if (cou != n - 1) {
        cout << "NO";
    } else {
        cout << "YES\n" << res;
    }
    return 0;
}
