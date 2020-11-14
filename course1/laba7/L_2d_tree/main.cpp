#include <algorithm>
#include <iostream>
#include <vector>
#define mid lt + (rt-lt)/2
#define vx Element *
#define ui unsigned int

using namespace std;


struct Element {
    vector<ui> v;
    vx right = nullptr;
    vx left = nullptr;
};

ui a, b;
ui cur = 0;
ui nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

ui nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void merge(vector<ui> &v, vector<ui> &v1, vector<ui> &v2) {
    size_t p1 = 0, p2 = 0;
    while (p1 != v1.size() && p2 != v2.size()) {
        if (v1[p1] < v2[p2]) {
            v[p1 + p2] = v1[p1];
            p1++;
        } else {
            v[p1+p2] = v2[p2];
            p2++;
        }
    }
    while (p1 != v1.size()) {
        v[p1 + p2] = v1[p1];
        p1++;
    }
    while (p2 != v2.size()) {
        v[p1 + p2] = v2[p2];
        p2++;
    }
}

vx make_vertex(vx left, vx right) {
    vx node = new Element();
    node->v.resize(left->v.size() + right->v.size());
    merge(node->v, left->v, right->v);
    node->right = right;
    node->left = left;
    return node;
}
vx make_list(int value) {
    vx node = new Element();
    node->v.push_back(value);
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

class SegTree {
 public:
     SegTree(vector<ui> &v, int n) : size(n) {
         root = build(v, 0, size - 1);
     }
     ui get(ui l, ui r, ui x, ui y) {
         return get(root, l, r, 0, size - 1, x, y);
     }

 private:
     int size;
     vx root;

     vx build(vector<ui> &v, ui lt, ui rt) {
         if (lt == rt)
             return make_list(v[lt]);
         return make_vertex(build(v, lt, mid), build(v, mid + 1, rt));
     }
     ui get(vx v, ui l, ui r, ui lt, ui rt, ui x, ui y) {
         if (lt > r || rt < l)
             return 0;
         if (l <= lt && rt <= r) {
             ui ans = upper_bound(v->v.begin(), v->v.end(), y) -
                 lower_bound(v->v.begin(), v->v.end(), x);
             return ans;
         }
         return get(v->left, l, r, lt, mid, x, y) + get(v->right, l, r, mid + 1, rt, x, y);
     }
};

int main() {
    int q;
    cin >> q >> a >> b;
    vector<ui> f(131072);
    for (int i = 0; i < 131072; i++) {
        f[i] = nextRand24();
    }
    unsigned long long answer = 0;
    SegTree tree(f, 131072);
    for (int i = 0; i < q; i++) {
        ui l = nextRand17();
        ui r = nextRand17();
        if (l > r) swap(l, r);
        ui x = nextRand24();
        ui y = nextRand24();
        if (x > y) swap(x, y);
        ui res = tree.get(l, r, x, y);
        b += res;
        answer = (answer + res) % 4294967296;
    }
    cout << answer;
    return 0;
}
