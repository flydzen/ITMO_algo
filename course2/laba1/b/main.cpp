#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> g, gr;
vector<int> used;
vector<int> topsort;
vector<int> result;

void dfs1(int v) {
    used[v] = 1;
    for (int i : g[v]) {
        if (!used[i]) dfs1(i);
    }
    topsort.push_back(v);
}

void dfs2(int v, int c) {
    used[v] = c;
    result.push_back(c);
    for (int i : gr[v]) {
        if (!used[i]) dfs2(i, c);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b, c = 0;
    cin >> n >> m;
    g = vector<vector<int>>(n);
    gr = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        gr[b - 1].push_back(a - 1);
    }
    used = vector<int>(n);
    for (int i = 0; i < n; i++)
        if (!used[i]) dfs1(i);
    used = vector<int>(n);
    reverse(topsort.begin(), topsort.end());
    for (int i : topsort) {
        if (!used[i]) dfs2(i, ++c);
    }
    cout << c << endl;
    for (int i : used) {
        cout << i << " ";
    }
    return 0;
}
