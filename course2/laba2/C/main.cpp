//  floyd
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, a, b, w;
    cin >> n >> m;
    vector<vector<int>> d(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        a--, b--;
        d[a][b] = w;
    }
    for (int k = 0; k < n; k++) {
        d[k][k] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for (auto &i : d) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}
