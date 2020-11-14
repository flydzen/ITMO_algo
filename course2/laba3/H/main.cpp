#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> ss;
vector<size_t> it;
unordered_set<int> edges;
vector<int> deg;

int num(int from, int to) {
    return from < to ? from + to * 20001 : to + from * 20001;
}

void dfs(int v, vector<int> &res) {
    for (; it[v] < ss[v].size(); it[v]++) {
        int to = ss[v][it[v]];
        auto iterator = edges.find(num(v, to));
        if (iterator != edges.end()) {
            edges.erase(iterator);
            deg[v]--, deg[to]--;
            dfs(to, res);
            break;
        }
    }
    res.push_back(v + 1);
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    ss = vector<vector<int>>(n);
    it = vector<size_t>(n);
    deg = vector<int>(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ss[--a].push_back(--b);
        ss[b].push_back(a);
        edges.insert(num(a, b));
        deg[a]++, deg[b]++;
    }
    vector<vector<int>> result;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            result.emplace_back();
            dfs(i, result.back());
        }
    }
    for (int i = 0; i < n; i++) {
        if (deg[i]) {
            result.emplace_back();
            dfs(i, result.back());
        }
    }
    cout << result.size() << '\n';
    for (auto &line : result) {
        for (auto i : line)
            cout << i << " ";
        cout << '\n';
    }
    return 0;
}
