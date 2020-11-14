#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> answer;
vector<vector<int>> a;
vector<int> w;

void rev(int k, int s) {
    if (a[k][s] == 0)
        return;
    if (a[k - 1][s] == a[k][s]) {
        rev(k - 1, s);
    } else {
        rev(k - 1, s - w[k]);
        answer.push_back(k);
    }
}

int main() {
    ifstream inp("knapsack.in");
    ofstream oup("knapsack.out");
    int N, W;
    inp >> N >> W;
    answer = vector<int>();
    w = vector<int>(N + 2);
    a = vector<vector<int>>(N + 2, vector<int>(W + 2, 0));
    vector<int> c(N + 2);
    for (int i = 1; i < N + 1; i++) {
        inp >> w[i];
    }
    for (int i = 1; i < N + 1; i++) {
        inp >> c[i];
    }
    for (int k = 1; k < N + 1; k++) {
        for (int s = 1; s < W + 1; s++) {
            if (s >= w[k]) {
                a[k][s] = max(a[k - 1][s], a[k - 1][s - w[k]] + c[k]);
            } else {
                a[k][s] = a[k - 1][s];
            }
        }
    }
    rev(N, W);
    oup << answer.size() << endl;
    for (auto el : answer) {
        oup << el << " ";
    }
    return 0;
}
