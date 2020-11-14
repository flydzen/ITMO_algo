#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<int> parent;
vector<int> h;
vector<vector<int>> up;

void dfs(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to]) {
            parent[to] = v;
            h[to] = h[v] + 1;
            dfs(to);
        }
    }
}

int lca(int n, int a, int b) {
    if (h[a] > h[b])
        swap(a, b);
    for (int i = (int) log2(n); i >= 0; i--)
        if (h[up[b][i]] - h[a] >= 0)
            b = up[b][i];
    if (a == b)
        return b;
    for (int i = (int) log2(n); i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return parent[a];
}

int takeCorrect(int x, int y, int z) {
    if (x == y)
        return z;
    else if (y == z)
        return x;
    else
        return y;
}

int main() {
    int n, a, b, x, y, z, m;
    char command;
    cin >> n;
    while (n != 0) {
        int root = 0;
        g = vector<vector<int>>(n);
        used = vector<bool>(n);
        parent = vector<int>(n);
        h = vector<int>(n);
        up = vector<vector<int>>(n, vector<int>((int)log2(n) + 1));
        for (int i = 0; i < n - 1; i++) {
            cin >> a >> b;
            g[--a].push_back(--b);
            g[b].push_back(a);
        }
        dfs(0);
        parent[0] = 0;
        dfs(root);
        for (int i = 1; i < n; i++)
            up[i][0] = parent[i];
        for (int i = 1; i < log2(n); i++)
            for (int j = 0; j < n; j++)
                up[j][i] = up[up[j][i - 1]][i - 1];
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> command;
            if (command == '?') {
                cin >> a >> b;
                a--;
                b--;
                if (root == 0) {
                    cout << lca(n, a, b) + 1 << endl;
                } else {
                    x = lca(n, a, b);
                    y = lca(n, a, root);
                    z = lca(n, b, root);
                    cout << takeCorrect(x, y, z) + 1 << endl;
                }
            } else if (command == '!') {
                cin >> root;
                --root;
            }
        }
        cin >> n;
    }
    return 0;
}
