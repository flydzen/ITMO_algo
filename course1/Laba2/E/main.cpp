#include <iostream>
#include <list>
#include <vector>

using namespace std;
int n, m;
int power = 'z' - 'a' + 1;

void radixSort(int[] A) {
    for (int i = 0; i < m; i++) {

    }
    for
    j = 0
    to
    k - 1
    C[j] = 0
    for
    j = 0
    to
    n - 1
    d = digit(A[j], i)
    C[d]++
    count = 0
    for
    j = 0
    to
    k - 1
    tmp = C[j]
    C[j] = count
    count += tmp
    for
    j = 0
    to
    n - 1
    d = digit(A[j], i)
    B[C[d]] = A[j]
    C[d]++
    A = B
}

void lsd(char v, int k) {
    vector<list<char *>> temp(power);
    for (int i = m - 1; i >= m - k; i--) {
        for (int j = 0; j < m; j++) {
            int key = v[i][j]-'a';
            temp[key] = v[i];
        }
    }
}

struct line{
    char* value[];
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    cin >> n >> m >> k;
    vector<line> s(n);
    for (int i = 0; i < n; i++) {
        line *temp = new line;
        char *x[m];
        for (int j = 0; j < m; j++) {
            cin >> x[j];
        }
        temp->value = x;
        s[i] = &temp;
    }
    lsd(s, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}