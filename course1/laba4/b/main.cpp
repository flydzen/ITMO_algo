#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    ifstream r("lis.in");
    ofstream w("lis.out");
    int n;
    r >> n;
    vector<int> v(n + 3);
    vector<int> l(n + 3, INT_MAX);
    vector<int> pre(n + 3, -1);
    vector<int> ind(n + 3, -1);
    for (int i = 0; i < n; i++)
        r >> v[i];
    int len = 0;
    l[0] = INT_MIN;
    for (int i = 0; i < n; i++) {
        int x = lower_bound(l.begin(), l.end(), v[i]) - l.begin();
        if (l[x - 1] < v[i] && v[i] < l[x]) {
            l[x] = v[i];
            ind[x] = i;
            pre[i] = ind[x - 1];
            len = max(len, x);
        }
    }
    pre[0] = -1;
    vector<int> answer;
    int step = ind[len];
    while (step != -1) {
        answer.push_back(v[step]);
        step = pre[step];
    }
    w << answer.size() << endl;
    for (auto it = --answer.end(); it != --answer.begin(); it--) {
        w << *it << " ";
    }
    return 0;
}
