#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int>> g;
vector<int> used;

void dfs(int v, int c) {
    used[v] = c;
    for (auto i : g[v]) {
        if (!used[i]) dfs(i, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b, c = 0;
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
            dfs(i, ++c);
        }
    }
    cout << c << endl;
    for (int i : used) {
        cout << i << " ";
    }
    return 0;
}
