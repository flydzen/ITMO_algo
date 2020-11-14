#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, f, w;
    cin >> n >> s >> f;
    vector<vector<pair<int, int>>> ss(n);
    vector<long long> d(n, LONG_LONG_MAX);
    s--, f--;
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w;
            if (w >= 0 && i != j)
                ss[i].emplace_back(j, w);
        }
    }
    vector<bool> used(n);
    set<pair<long long, int>> q;
    q.insert({0, s});
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
    cout << (d[f] == LONG_LONG_MAX ? -1 : d[f]) << " ";
    return 0;
}
