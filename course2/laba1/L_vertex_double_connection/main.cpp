#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;
vector<vector<pair<int, int>>> ss;
vector<unordered_map<int, int>> isE;
unordered_map<int, vector<int>> brothers;
vector<int> bk, en;
vector<bool> used;
set<int> vs;
vector<int> answer;
int COLOR;
int time;
int lastColor;

void pokras_lampas(int num, int color) {
    answer[num] = color;
    lastColor = max(color, lastColor);
    if (brothers.find(num) != brothers.end()) {
        for (auto i : brothers[num]) {
            answer[i] = color;
        }
    }
}


void paint(int v, int color, int p) {
    used[v] = true;
    for (pair e : ss[v]) {
        int u = e.first;
        int num = e.second;
        if (p != u) {
            if (!used[u]) {
                if (bk[u] >= en[v]) {
                    int nColor = COLOR++;
                    pokras_lampas(num, nColor);
                    paint(u, nColor, v);
                } else {
                    pokras_lampas(num, color);
                    paint(u, color, v);
                }
            } else if (en[u] < en[v]) {
                pokras_lampas(num, color);
            }
        }
    }
}

void dfs(int v, int p) {
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
                    vs.insert(v);
                ch++;
            }
        }
    }
    if (p == -1 && ch > 1)
        vs.insert(v);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    COLOR = 0;
    used = vector<bool>(n);
    answer = vector<int>(m);
    isE = vector<unordered_map<int, int>>(n);
    brothers = unordered_map<int, vector<int>>();
    vs = set<int>();
    ss = vector<vector<pair<int, int>>>(n);
    bk.reserve(n);
    en.reserve(n);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        ss[--a].push_back(make_pair(--b, i));
        ss[b].push_back(make_pair(a, i));
        if (a > b) {
            swap(a, b);
        }
        if (isE[a].find(b) == isE[a].end()) {
            isE[a][b] = i;
        } else {
            int num = isE[a][b];
            if (brothers.find(num) == brothers.end()) {
                brothers[num] = vector<int>();
            }
            brothers[num].push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    used = vector<bool>(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            COLOR = lastColor + 1;
            paint(i, COLOR, -1);
        }
    }
    cout << COLOR - 1 << endl;
    for (int i : answer)
        cout << i << " ";
    return 0;
}
