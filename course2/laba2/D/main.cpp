#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n, m, a, b, w;
    cin >> n >> m;
    vector<vector<pair<int, int>>> ss(n);
    vector<int> d(n, INT_MAX);
    d[0] = 0;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        a--, b--;
        ss[a].emplace_back(b, w);
        ss[b].emplace_back(a, w);
    }
    vector<bool> used(n);
    set<pair<int, int>> q;
    q.insert({0, 0});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto &i : ss[v]) {
            if (d[v] + i.second < d[i.first]) {
                q.erase({d[i.first], i.first});
                d[i.first] = d[v] + i.second;
                q.insert({d[i.first], i.first});
            }
        }
    }
    for (int i : d) {
        cout << i << " ";
    }

    return 0;
}
