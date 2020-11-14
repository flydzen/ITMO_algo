#include <iostream>
#include <vector>

#define ui unsigned int
#define ll long long
using namespace std;

ui a, b;
ui cur = 0;
ui nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

ui nextRand32() {
    ui a = nextRand24(), b = nextRand24();
    return (a << 8) ^ b;
}

int next(){
    return (int)nextRand32();
}

void merge(vector<int> &v, unsigned int left, unsigned int right, unsigned int mid) {
    unsigned int u1 = left;
    unsigned int u2 = mid;
    vector<int> res((int)right - left);
    while (u1 < mid && u2 < right) {
        if (v[u1] > v[u2]) {
            res[u1 + u2 - left - mid] = v[u1];
            u1++;
        } else {
            res[u1 + u2 - left - mid] = v[u2];
            u2++;
        }
    }
    while (u1 < mid) {
        res[u1 + u2 - left - mid] = v[u1];
        u1++;
    }
    while (u2 < right) {
        res[u1 + u2 - left - mid] = v[u2];
        u2++;
    }
    for (unsigned int i = 0; i < right - left; i++) {
        v[left + i] = res[i];
    }
}

void sort(vector<int> &v, unsigned int l, unsigned int r) {
    if (r - l <= 1) {
        return;
    }
    unsigned int mid = (l + r) / 2;
    sort(v, l, mid);
    sort(v, mid, r);
    merge(v, l, r, mid);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, l1 = 0, l2 = 0;
    ll k, l1sum = 0, l2sum = 0, answer = 0;
    cin >> n >> k >> a >> b;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = next();
    }
    sort(v, 0, n);
    for(int i = 0; i < n; i++) {
        l1sum += v[i];
        l2sum += v[i];
        while (l2 < i && l2sum-v[l2] >= k){
            l2sum -= v[l2++];
        }
        while (l1 < l2 && l1sum < k) {
            l1sum -= v[l1++];
        }
        answer += l2-l1 + 1;
        if (l2==l1 && v[i]<k){
            answer-=1;
            break;
        }
    }
    cout << answer;
    return 0;
}