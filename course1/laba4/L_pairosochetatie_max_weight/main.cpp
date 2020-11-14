#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<pair<int, int>>> ss;
vector<long long> a;
vector<long long> b;
vector<long long> c;
void discrete_finger_simulation(int i, int from) {
    for (pair<int, int> p : ss[i]) {
        if (p.first == from)
            continue;
        discrete_finger_simulation(p.first, i);
        a[i] = max(a[i], b[p.first] + p.second - c[p.first]);
        b[i] += c[p.first];
    }
    a[i] += b[i];
    c[i] = max(a[i], b[i]);
}

int main() {
    ifstream fin("matching.in");
    ofstream fout("matching.out");
    int n;
    fin >> n;
    ss = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
    a = vector<long long>(n);
    b = vector<long long>(n);
    c = vector<long long>(n);
    for (int i = 0; i < n - 1; i++) {
        int f, t, w;
        fin >> f >> t >> w;
        ss[f - 1].push_back(make_pair(t - 1, w));
        ss[t - 1].push_back(make_pair(f - 1, w));
    }
    discrete_finger_simulation(0, -1);
    fout << c[0];
    return 0;
}
