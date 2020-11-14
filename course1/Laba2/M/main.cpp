#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void increment(vector<short> &a, int k) {
    int i = 0;
    while (i < k && a[i] == 1) {
        a[i++] = 0;
    }
    if (i < k) {
        a[i] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> net;
    for (int i = 0; i < k; i++) {
        int cou;
        cin >> cou;
        for (int j = 0; j < cou; j++) {
            int v1, v2;
            cin >> v1 >> v2;
            net.emplace_back(v1 - 1, v2 - 1);
        }
    }
    vector<short> line(n);
    vector<short> oldLine(n);
    for (int i = 0; i < n; i++) {
        line[i] = 0;
    }
    int lines = (int) pow(2, n);
    for (int i = 0; i < lines; i++) {
        oldLine = line;
        for (auto &l : net) {
            int v1 = l.first;
            int v2 = l.second;
            if (v2 < v1) {
                int temp = v1;
                v1 = v2;
                v2 = temp;
            }
            if (line[v1] > line[v2]) {
                swap(line[v1], line[v2]);
            }
        }
        for (int j = 0; j < n - 1; j++) {
            if (line[j] > line[j + 1]) {
                cout << "NO";
                exit(0);
            }
        }
        increment(oldLine, n);
        line = oldLine;
    }
    cout << "YES";
    return 0;
}
