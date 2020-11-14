#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> g_base;
vector<int> used;
vector<int> topsort;

void dfsTopsort(int v) {
    used[v] = 1;
    for (auto i : g[v]) {
        if (!used[i]) dfsTopsort(i);
    }
    topsort.push_back(v);
}

void dfs(int v) {
    used[v] = 1;
    for (auto i : g[v]) {
        g[v].push_back(i);
        if (!used[i]) dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t, a, b, w;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    vector<long long> result(n, (long long) INT_MAX);
    result[s] = 0;
    g_base = vector<vector<int>>(n);
    vector<vector<int>> weights(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        g_base[a - 1].push_back(b - 1);
        weights[a - 1][b - 1] = w;
    }
    g = vector<vector<int>>(n);
    used = vector<int>(n);
    dfs(s);
    used = vector<int>(n);
    for (int i = 0; i < n; i++)
        if (!used[i]) dfsTopsort(i);
    reverse(topsort.begin(), topsort.end());
    int i = 0;
    for (; topsort[i] != s; i++) {}
    for (; i < n; i++) {
        for (auto j : g[topsort[i]]) {
            result[j] = min(result[j], result[topsort[i]] + weights[topsort[i]][j]);
        }
    }
    if (result[t] != INT_MAX)
        cout << result[t];
    else
        cout << "Unreachable";
    return 0;
}
