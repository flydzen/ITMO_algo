#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> v;
int lcs(int start1, int l1, int start2, int l2){
    vector<vector<int>> lcs(l1, vector<int>(0, l2));
    if (l1 == 0)
        return 0;
    for (int i = 1; i < l1; i++) {
        for (int j = 1; j < l2; j++) {
            if (v[start1+i] == v[start2 + j]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }else {
                lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
            }
        }
    }
    return lcs[l1-1][l2-1];
}

int main() {
    int n;
    cin >> n;
    v = vector<int>(n);
    for (int i = 0; i < n; i++){
        cin >> v[i];
    }
    long long cou = 0;
    for(int i = 0; i < n; i++){
        int len = min(i, n-i-1);
        reverse(v.begin()+i-len, v.begin()+i);
        cou += lcs(i-len, len, i+1, len);
        cou %= 1000000000;
        reverse(v.begin()+i-len, v.begin()+i);
        reverse(v.begin()+i-len, v.begin()+i+1);
        cou += lcs(i-len, len+1, i+1, len+1);
        reverse(v.begin()+i-len, v.begin()+i+1);
        cou %= 1000000000;
    }
    cout << cou;
    return 0;
}