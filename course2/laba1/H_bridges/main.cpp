#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector<pair<int, int>>> ss;
vector<int> bk, en;
vector<bool> used;
set<int> answer;
int time;

int dfs(int v, int p) {
    used[v] = true;
    time++;
    en[v] = time;
    bk[v] = time;
    for (pair e : ss[v]) {
        int u = e.first;
        int num = e.second;
        if (u != p) {
            if (used[u]) {
                bk[v] = min(bk[v], en[u]);
            } else {
                dfs(u, v);
                bk[v] = min(bk[v], bk[u]);
                if (bk[u] > en[v]) {
                    answer.insert(num);
                }
            }
        }
    }
    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    used = vector<bool>(n);
    answer = set<int>();
    ss = vector<vector<pair<int, int>>>(n);
    bk.reserve(n);
    en.reserve(n);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        ss[--a].push_back(make_pair(--b, i));
        ss[b].push_back(make_pair(a, i));
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, i);
        }
    }
    cout << answer.size() << endl;
    for (int i : answer)
        cout << i + 1 << " ";
    return 0;
}