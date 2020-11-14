
#include<iostream>
#include<vector>
using namespace std;
bool check(int a, int b, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int a1 = (a >> i)&1;
        int a2 = (a >> (i+1))&1;
        if (a1 == a2 && a1 == ((b >> i)&1) && a2 == ((b >> (i + 1)) &1)) {
            return false;
        }
    }
    return true;
}
int main() {
    int n, m, mod;
    cin >> n >> m >> mod;
    if (m < n)
        swap(n, m);
    vector<vector<int> > dp(m, vector<int> ((1 << n), 0));
    for (int mask = 0; mask < (1 << n); ++mask) {
        dp[0][mask] = 1;
    }
    for (int i = 1; i < m; ++i) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int mask2 = 0; mask2 < (1 << n); ++mask2) {
                if (check(mask, mask2, n)) {
                    dp[i][mask] += dp[i - 1][mask2];
                }
            }
        }
    }
    long long ret = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        ret += dp[m - 1][mask];
    }
    cout << ret;
}