#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> ss;
vector<bool> used;
vector<int> Size;

int n;

int findC(int v) {
    if ((Size[v] - 1) == n / 2)
        return v;
    used[v] = true;
    int maxi = n;
    for (int u : ss[v]) {
        if (!used[u]) {
            if (Size[u] > Size[maxi]) {
                maxi = u;
            }
        }
    }
    if (Size[maxi] - 1 < n / 2) {
        return v;
    } else {
        return findC(maxi);
    }
}

void getSize(int v, vector<int> &size) {
    used[v] = true;
    size[v] = 0;
    for (int u : ss[v]) {
        if (!used[u]) {
            getSize(u, size);
            size[v] += size[u];
        }
    }
    size[v] += 1;
}

bool compare(int a, int b) {
    return Size[a] > Size[b];
}

void psp(int v, vector<bool> &answer) {
    used[v] = true;
    for (auto u : ss[v]) {
        if (!used[u]) {
            answer.push_back(true);
            psp(u, answer);
        }
    }
    answer.push_back(false);
}

int main() {
    cin >> n;
    ss = vector<vector<int>>(n);
    Size = vector<int>(n + 1);
    used = vector<bool>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        ss[a - 1].push_back(b - 1);
        ss[b - 1].push_back(a - 1);
    }
    if (n % 2 == 0 || n == 1) {
        cout << "NO";
        exit(0);
    }
    getSize(0, Size);
    used = vector<bool>(n);
    int centroid = findC(0); // нашли центроид
    if (centroid == -1 || ss[centroid].size() % 2 == 1) { // тривиальные условия если не подходит
        cout << "NO";
        exit(0);
    }
    used = vector<bool>(n);
    getSize(centroid, Size); //  обновили веса от центра
    for (int i = 0; i < n; i++) {
        sort(ss[i].begin(), ss[i].end(), compare);
    } // отсортировали списки смежности по весу в поддеревьях
    vector<int> left; // левые бункеры
    vector<int> right; // правые бункеры
    vector<bool> pspl;  // псп для левых
    vector<bool> pspr; // псп для правых
    bool turn = true;
    used = vector<bool>(n);
    for (int u : ss[centroid]) {
        if (turn) {
            left.push_back(u);
        } else {
            right.push_back(u);
        }
        turn = !turn;
    } // по очереди раскидывем в левые и правые
    used[centroid] = true;
    for (auto i : left) { // делаем дфс от левых
        psp(i, pspl);
    }
    for (auto i : right) {
        psp(i, pspr);
    }
    cout << (pspl == pspr ? "YES" : "NO");
    return 0;
}
