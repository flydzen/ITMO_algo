#include <iostream>
#include <vector>
using namespace std;

string::iterator pend;
string::iterator send;

bool check(string::iterator p, string::iterator s) {
    if (p == pend)
        return s == send;
    if (s == send) {
        while (p != pend) {
            if (*p++ != '*')
                return false;
        }
        return true;
    }

    if (*p == '*')
        return check(++p, s) || check(--p, ++s);
    if (*p == *s || *p == '?')
        return check(++p, ++s);
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string p, s;
    cin >> p >> s;
    if (p.empty()) {
        cout << (s.empty() ? "YES" : "NO");
        exit(0);
    }
    if (s.empty()) {
        for (char i : p) {
            if (i != '*') {
                cout << "NO";
                exit(0);
            }
        }
        cout << "YES";
        exit(0);
    }
    p = "#" + p;
    s = " " + s;
    int n = p.size();
    int m = s.size();
    vector<vector<bool>> dp = vector<vector<bool>>(m, vector<bool>(n));
    dp[0][0] = true;
    if (p[1] == '*') {
        for (int i = 0; i < m; i++) {
            dp[i][0] = true;
        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (p[j] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j] || dp[i - 1][j - 1];
            } else if (p[j] == '?' || p[j] == s[i]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    cout << (dp[m - 1][n - 1] ? "YES" : "NO") << endl;
    return 0;
}
