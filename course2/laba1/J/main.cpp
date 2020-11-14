#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> g;
vector<int> used;
vector<int> topsort;

void dfs(int v, int c) {
    used[v] = c;
    for (auto i : g[v]) {
        if (!used[i]) {
            dfs(i, 3 - c);
        } else if (used[i] == c) {
            cout << "NO" << endl;
            exit(0);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m;
    g = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    used = vector<int>(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
    cout << "YES" << endl;
    return 0;
}
