#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    ifstream fin("levenshtein.in");
    ofstream fout("levenshtein.out");
    fin >> s1 >> s2;
    int l1 = s1.size();
    int l2 = s2.size();
    vector<vector<int>> d(l1 + 1, vector<int>(l2 + 1, 0));

    for (int i = 1; i <= l2; i++)
        d[0][i] = i;
    for (int i = 1; i <= l1; i++)
        d[i][0] = i;
    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = min(d[i - 1][j - 1] + 1, min(d[i - 1][j] + 1, d[i][j - 1] + 1));
            }
        }
    }
    fout << d[l1][l2];
    return 0;
}
