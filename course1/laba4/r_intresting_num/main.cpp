#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;
vector<vector<pair<int, int>>> p;

vector<int> answer;

void print(int s, int m) {
    if (s == 0) return;
    print(p[s][m].first, p[s][m].second);
    answer.push_back(s - p[s][m].first);
}

int main() {
    int n;
    ifstream fin("number.in");
    ofstream fout("number.out");
    fin >> n;
    queue<pair<int, int>> q;
    int N = 2001;
    vector<vector<bool> > used(N, vector<bool>(N));
    p = vector(N, vector<pair<int, int> >(N));
    q.push(make_pair(0, 0));
    while (true) {
        pair<int, int> t = q.front();
        q.pop();
        if (t.first == n && t.second == 0) {
            print(t.first, t.second);
            break;
        }
        for (int i = 0; i < 10; i++) {
            int s = t.first + i;
            int m = (t.second * 10 + i) % n;
            if (!used[s][m] && s <= n) {
                used[s][m] = true;
                q.push(make_pair(s, m));
                p[s][m] = make_pair(t.first, t.second);
            }
        }
    }
    for (auto i : answer) {
        fout << i;
    }
    return 0;
}
