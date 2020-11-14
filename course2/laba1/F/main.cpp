#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

void dfs(int v, vector<unordered_set<int>> &g, vector<int> &used, vector<int> &ans) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to, g, used, ans);
        }
    }
    ans.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m;
    vector<unordered_set<int>> g(n);
    vector<int> used(n);
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a - 1].insert(b - 1);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i])
            dfs(i, g, used, ans);
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n - 1; i++) {
        if (g[ans[i]].count(ans[i + 1]) == 0) {
            cout << "NO";
            exit(0);
        }
    }
    cout << "YES";
    return 0;
}
