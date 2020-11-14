#include <vector>
#include <iostream>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a;
    cin >> n;
    vector<bool> used(n);
    vector<pair<int, pair<int, int>>> G;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a;
            if (i == j && a < 0) {
                cout << "YES" << endl << 2 << endl << 1 + i << " " << i + 1 << endl;
                exit(0);
            }
            if (a != 1e9)
                G.push_back({a, {i, j}});
        }
    }
    vector<int> d(n, INT_MAX);
    vector<int> p(n, -1);
    int flag = -1;
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
        d[i] = 0;
        used[i] = true;
        for (int k = 0; k < n; k++) {
            flag = -1;
            for (pair<int, pair<int, int>> e : G) {
                if (d[e.second.first] < INT_MAX) {
                    used[e.second.second] = true;
                    if (d[e.second.second] > d[e.second.first] + e.first) {
                        d[e.second.second] = d[e.second.first] + e.first;
                        flag = e.second.second;
                        p[e.second.second] = e.second.first;
                    }
                }
            }
        }
    }
    if (flag == -1) {
        cout << "NO" << endl;
        exit(0);
    }
    cout << "YES" << endl;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        flag = p[flag];
    }
    int i = flag;
    while (i != flag || ans.size() <= 1) {
        ans.push_back(i + 1);
        i = p[i];
    }
    cout << ans.size() + 1 << endl << ans[0] << " ";
    for (size_t j = ans.size(); j > 0; j--) {
        cout << ans[j - 1] << ' ';
    }
    return 0;
}
