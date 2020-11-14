#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<pair<int, int>>> g;
vector<bool> used;
vector<pair<int, int>> parent;
vector<int> h;
vector<vector<int>> up;
vector<vector<int>> minw;

void dfs(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to.first]) {
            parent[to.first] = {v, to.second};
            h[to.first] = h[v] + 1;
            dfs(to.first);
        }
    }
}

int lca(int n, int a, int b) {
    if (h[a] > h[b])
        swap(a, b);
    int mini = INT_MAX;
    for (int i = (int)log2(n); i >= 0; i--) {
        if (h[up[b][i]] - h[a] >= 0) {
            mini = min(mini, minw[b][i]);
            b = up[b][i];
        }
    }
    if (a == b)
        return mini;
    for (int i = (int)log2(n); i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            mini = min(min(mini, minw[a][i]), minw[b][i]);
            a = up[a][i];
            b = up[b][i];
        }
    mini = min(min(mini, minw[a][0]), minw[b][0]);
    return mini;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b, w;
    cin >> n;
    g = vector<vector<pair<int, int>>>(n);
    used = vector<bool>(n, false);
    parent = vector<pair<int, int>>(n);
    h = vector<int>(n);
    up = vector<vector<int>>(n, vector<int>((int) log2(n) + 1));
    minw = vector<vector<int>>(n, vector<int>((int) log2(n) + 1));
    int root = 0;
    for (int i = 1; i < n; i++) {
        cin >> a >> w;
        a--;
        g[a].push_back({i, w});
    }
    int m;
    cin >> m;
    parent[0] = {0, INT_MAX};
    dfs(root);
    for (int i = 0; i < n; i++) {
        up[i][0] = parent[i].first;
        minw[i][0] = parent[i].second;
    }
    for (int i = 1; i < log2(n); i++) {
        for (int j = 0; j < n; j++) {
            up[j][i] = up[up[j][i - 1]][i - 1];
            minw[j][i] = min(minw[j][i - 1], minw[up[j][i - 1]][i - 1]);
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;
        cout << lca(n, a, b) << endl;
    }
    return 0;
}
