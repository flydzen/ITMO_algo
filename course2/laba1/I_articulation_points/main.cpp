#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector<pair<int, int>>> ss;
vector<int> bk, en;
vector<bool> used;
std::set<int> answer;
int time;

int dfs(int v, int p) {
    used[v] = true;
    time++;
    en[v] = time;
    bk[v] = time;
    int ch = 0;
    for (pair e : ss[v]) {
        int u = e.first;
        if (u != p) {
            if (used[u]) {
                bk[v] = min(bk[v], en[u]);
            } else {
                dfs(u, v);
                bk[v] = min(bk[v], bk[u]);
                if (bk[u] >= en[v] && p != -1)
                    answer.insert(v);
                ch++;
            }
        }
    }
    if (p == -1 && ch > 1)
        answer.insert(v);
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
            dfs(i, -1);
        }
    }
    cout << answer.size() << endl;
    for (int i : answer)
        cout << i + 1 << endl;
    return 0;
}
