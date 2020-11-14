#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define it vector<char>::iterator
using namespace std;

vector<char> answer;

vector<int> lcs(char *a, int sa, char *b, int sb) {
    if (sa < sb){
        swap(a, b);
        swap(sa, sb);
    }
    vector<vector<int>> l(2, vector<int>(sb, 0));
    for (int i = 1; i <= sa; i++) {
        for (int j = 1; j <= sb; j++) {
            if (a[i - 1] == b[j - 1])
                l[i % 2][j] = l[(i - 1) % 2][j - 1] + 1;
            else
                l[i % 2][j] = max(l[(i - 1) % 2][j], l[i % 2][j - 1]);
        }
    }
    return l[sa % 2];
}

vector<int> rlcs(char *a, int sa, char *b, int sb) {
    if (sa < sb){
        swap(a, b);
        swap(sa, sb);
    }
    vector<vector<int>> l(2, vector<int>(sb+1, 0));
    for (int i = 1; i <= sa; i++) {
        for (int j = 1; j <= sb; j++) {
            if (a[sa - i - 1] == b[sb - j - 1])
                l[i % 2][j] = l[(i - 1) % 2][j - 1] + 1;
            else
                l[i % 2][j] = max(l[(i - 1) % 2][j], l[i % 2][j - 1]);
        }
    }
    return l[sa % 2];
}

void heisenberg(char *a, int sa, char *b, int sb) {
    if (sb == 0)
        return;
    if (sa == 1)
        for (int i = 0; i < sb; i++)
            if (a[0] == b[i])
                answer.push_back(a[0]);
    else {
        int m = sa / 2;
        vector<int> f = lcs(a, m, b, sb);
        vector<int> s = rlcs(a+m+1, sa-m-1, b, sb);
        int max = s[0];
        int it_max = -1;
        for (int j = 0; j <= sb; j++)
            if (f[j] + s[j+1] > max) {
                max = f[j] + s[j + 1];
                it_max = j;
            }
        if (f[sb - 1] > max){
            it_max = sb-1;
        }
        heisenberg()
    }


}

int main() {
    string a, b;
    cin >> a >> b;
    if (a.size() < b.size())
        swap(a, b);
    cout << lcs(&a[0], a.size(), &b[0], b.size())[b.size()];
    return 0;
}