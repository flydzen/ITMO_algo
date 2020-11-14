#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<vector<int>> g, gr;
vector<int> used;
vector<int> topsort;
vector<int> result;
map<pair<int, int>, int> indx;

void dfs1(int v, int p) {
    used[v] = 1;
    for (int i : g[v]) {
        if (i != p)
            gr[i].push_back(v);
        if (!used[i]) dfs1(i, v);
    }
    topsort.push_back(v);
}

void dfs2(int v, int c) {
    used[v] = c;
    for (int i : gr[v]) {
        if (used[i] != c && used[i] != 0) {
            result.push_back(indx[{i, v}]);
        }
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
        g[b - 1].push_back(a - 1);
        indx[{a - 1, b - 1}] = i + 1;
        indx[{b - 1, a - 1}] = i + 1;
    }
    used = vector<int>(n);
    for (int i = 0; i < n; i++)
        if (!used[i]) dfs1(i, -1);
    used = vector<int>(n);
    reverse(topsort.begin(), topsort.end());
    for (int i : topsort) {
        if (!used[i]) dfs2(i, ++c);
    }
    cout << result.size() << endl;
    sort(result.begin(), result.end());
    for (int i : result) {
        cout << i << " ";
    }
    return 0;
}
