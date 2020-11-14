#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g, M;
vector<int> used;
int n;

void dfs1(int v) {
    used[v] = 1;
    for (int i = 0; i < n; i++) {
        if (g[v][i] && !used[i]) dfs1(i);
    }
}

void dfs2(int v) {
    used[v] = 1;
    for (int i = 0; i < n; i++) {
        if (g[i][v] && !used[i]) dfs2(i);
    }
}


int all_used() {
    for (int i = 0; i < n; i++) {
        if (!used[i]) return 0;
    }
    return 1;
}

inline void BS() {
    int l = 0, r = 1000000010, m;
    while (l < r) {
        m = (l + r) / 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = (M[i][j] <= m);
            }
        }
        used = vector<int>(n, 0);
        dfs1(0);
        if (all_used()) {
            used = vector<int>(n, 0);
            dfs2(0);
            if (!all_used())
                l = m + 1;
        } else {
            l = m + 1;
        }
        if (l != m + 1) r = m;
    }
    cout << l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int a;
    cin >> n;
    g = vector<vector<int>>(n, vector<int>(n));
    M = vector<vector<int>>(n, vector<int>(n));
    used = vector<int>(n + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a;
            M[i][j] = a;
        }
    }
    BS();
    return 0;
}
