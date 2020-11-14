#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ofstream fout;

void print(int i, int j, vector<vector<int>> &way) {
    if (i != j) {
        fout << "(";
        print(i, way[i][j], way);
        print(way[i][j] + 1, j, way);
        fout << ")";
    } else {
        fout << "A";
    }
}

int main() {
    int n;
    ifstream fin("matrix.in");
    fout.open("matrix.out");
    fin >> n;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> way(n + 1, vector<int>(n + 1, 0));
    vector<pair<int, int>> matrix;

    for (int i = 0; i < n; i++) {
        int a, b;
        fin >> a >> b;
        matrix.emplace_back(a, b);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            int k = i + j;
            dp[j][k] = INT_MAX;
            for (int l = j; l < k; ++l) {
                int q = min(dp[j][k], dp[j][l] + dp[l + 1][k] +
                    matrix[j].first * matrix[l].second * matrix[k].second);
                if (q < dp[j][k]) {
                    dp[j][k] = q;
                    way[j][k] = l;
                }
            }
        }
    }
    print(0, n - 1, way);
    return 0;
}
