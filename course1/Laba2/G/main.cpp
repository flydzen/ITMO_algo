#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define ui unsigned int
#define ull unsigned long long
#define us unsigned long long
#pragma GCC optimize("03")

using namespace std;

ui cur = 0;
ui a, b;

inline ui nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

inline ui nextRand32() {
    return (nextRand24() << 8) ^ nextRand24();
}

inline ui digit(ui num, ui i) {
    return (num >> (i * 8) & 0xFF);
}

void lsd(vector<ui> &v) {
    ui k = 256;
    ui m = 4;
    ui n = v.size();
    vector<ui> nV(n);
    for (ui i = 0; i < m; i++) {
        vector<ui> c(k);
        for (ui j = 0; j < n; j++) {
            c[digit(v[j], i)]++;
        }
        ui count = 0;
        for (ui j = 0; j < k; j++) {
            ui temp = c[j];
            c[j] = count;
            count += temp;
        }
        for (ui j = 0; j < n; j++) {
            ui d = digit(v[j], i);
            nV[c[d]] = v[j];
            c[d]++;
        }
        v = nV;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ui t, n;
    cin >> t >> n;
    for (ui i = 0; i < t; i++) {
        cin >> a >> b;
        vector<ui> vec(n);
        for (ui j = 0; j < n; j++) {
            vec[j] = nextRand32();
        }
        lsd(vec);
        unsigned long long summ = 0;
        for (ui ij = 0; ij < n; ij++) {
            summ += (unsigned long long) (ij + 1) * vec[(size_t) ij];
        }
        cout << summ << endl;
        vec.clear();
    }
    return 0;
}
