#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dfs(int v, vector<vector<int>> &g, vector<int> &used, vector<int> &ans) {
    used[v] = 1;
    for (auto to : g[v]) {
        if (used[to] == 0) {
            int r = dfs(to, g, used, ans);
            if (r != -1) {
                ans.push_back(v + 1);
                if (r == v) {
                    reverse(ans.begin(), ans.end());
                    for (int i : ans) {
                        cout << i << ' ';
                    }
                    exit(0);
                }
                return r;
            }
        } else if (used[to] == 1) {
            cout << "YES" << endl;
            ans.push_back(v + 1);
            return to;
        }
    }
    used[v] = 2;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> used(n);
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) dfs(i, g, used, ans);
    }
    cout << "NO";

    return 0;
}
