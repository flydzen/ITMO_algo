#include <iostream>

using namespace std;

const int lb = 19;

int depth[500000];
int dp[500000][20];

int lca(int a, int b) {
    if (depth[a] < depth[b])
        swap(a, b);
    for (int i = lb; i >= 0; i--)
        if (depth[dp[a][i]] >= depth[b])
            a = dp[a][i];
    if (a == b)
        return a;
    for (int i = lb; i >= 0; i--)
        if (dp[a][i] != dp[b][i]) {
            a = dp[a][i];
            b = dp[b][i];
        }
    return dp[b][0];
}

void add(int a, int b) {
    dp[b][0] = a;
    depth[b] = depth[a] + 1;
    for (int i = 1; i < lb; i++)
        dp[b][i] = dp[dp[b][i - 1]][i - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    dp[0][0] = 0;
    string s;
    int a, b;
    for (int d = 0; d < n; d++) {
        cin >> s;
        cin >> a >> b;
        if (s == "ADD") {
            add(a - 1, b - 1);
        } else {
            cout << lca(a - 1, b - 1) + 1 << endl;
        }
    }
}
