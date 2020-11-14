#include <queue>
#include <vector>
#include <iostream>
#include <climits>
#include <unordered_set>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, a, b;
    long long c;
    cin >> n >> m >> s;
    s--;
    bool loop = false;
    queue<int> H;
    vector<bool> used(n);
    vector<pair<long long, pair<int, int>>> G;
    vector<vector<int>> V(n);
    vector<long long> d(n, LLONG_MAX);
    for (long long i = 0; i < m; i++) {
        cin >> a >> b >> c;
        a--, b--;
        if (a == b && c < 0) {
            H.push(a);
            d[a] = LLONG_MIN;
            loop = true;
        } else {
            G.push_back({c, {a, b}});
            V[a].push_back(b);
        }
    }
    vector<int> p(n, -1);
    d[s] = 0;
    int flag;
    for (int k = 0; k < n; k++) {
        flag = -1;
        for (pair<long long, pair<int, int>> e : G) {
            if (d[e.second.first] < LLONG_MAX) {
                if (d[e.second.second] > d[e.second.first] + e.first) {
                    d[e.second.second] = d[e.second.first] + e.first;
                    flag = e.second.second;
                    p[e.second.second] = e.second.first;
                }
            }
        }
    }
    if (loop) {
        int v;
        while (!H.empty()) {
            v = H.front();
            H.pop();
            for (int u : V[v]) {
                if (!used[u]) {
                    used[u] = true;
                    d[u] = LLONG_MIN;
                    H.push(u);
                }
            }
        }
    }
    if (flag != -1) {
        for (int i = 0; i < n; i++) {
            flag = p[flag];
        }
        int i = flag;
        int cnt = 0;
        while (i != flag || cnt == 0) {
            d[i] = LLONG_MIN;
            i = p[i];
            cnt++;
            used[i] = true;
            H.push(i);
            int v;
            while (!H.empty()) {
                v = H.front();
                H.pop();
                for (int u : V[v]) {
                    if (!used[u]) {
                        used[u] = true;
                        d[u] = LLONG_MIN;
                        H.push(u);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (d[i] == LLONG_MAX) {
            cout << '*' << endl;
        } else {
            if (d[i] == LLONG_MIN)
                cout << '-' << endl;
            else
                cout << d[i] << endl;
        }
    }
    return 0;
}
