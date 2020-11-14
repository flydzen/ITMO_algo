#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#define d dp[x][y]

using namespace std;

int check(int x, int y, vector<vector<int>> &dp, vector<int> &v) {
    if (d != -1)
        return d;
    d = 0;
    for (int i = 0; i <= x; i++) {
        if (v[i] <= y)
            d = max(d, check(x - i, y - v[i], dp, v) + 1);
    }
    return d;
}

int main() {
    ifstream fin("bridge.in");
    ofstream fout("bridge.out");
    int x, a, y, b, l;
    fin >> x >> a >> y >> b >> l;
    vector<int> v(x + 1);
    int left = -1;
    int right = (x * a + y * b) / l + 1;
    while (right - left > 1) {
        int m = (right + left) / 2;
        vector<vector<int>> dp(x + 1, vector<int>(y + 1, -1));
        for (int i = 0; i <= x; i++)
            v[i] = a * i < m ? (int) ceil((double) (m - a * i) / b) : 0;
        if (check(x, y, dp, v) >= l)
            left = m;
        else
            right = m;
    }
    cout << left;
    fin.close();
    fout.close();
    return 0;
}
