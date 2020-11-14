#include <iostream>
#include <vector>
#define mid lt + (rt-lt)/2
#define vx Element *

using namespace std;

struct Element {
    int mini = 0;
    vx right = nullptr;
    vx left = nullptr;
};

void setMin(vx v) {
    if (!v)
        return;
    if (v->left && v->right) {
        v->mini = min(v->left->mini, v->right->mini);
    } else if (v->left) {
        v->mini = v->left->mini;
    } else if (v->right) {
        v->mini = v->right->mini;
    }
}

vx make_vertex(vx left, vx right) {
    vx node = new Element();
    node->right = right;
    node->left = left;
    setMin(node);
    return node;
}
vx make_list(int value) {
    vx node = new Element();
    node->mini = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

class SegTree {
 public:
     SegTree(vector<int> &v, int n) : size(n) {
         root = build(v, 0, size - 1);
     }
     int get(int l, int r) {
         return get(root, l, r, 0, size - 1);
     }
     void set(int value, int x) {
         set(root, value, 0, size - 1, x);
     }

 private:
     int size;
     vx root;
     vx build(vector<int> &v, int lt, int rt) {
         if (lt == rt)
             return make_list(v[lt]);
         return make_vertex(build(v, lt, mid), build(v, mid + 1, rt));
     }
     int get(vx v, int l, int r, int lt, int rt) {
         if (lt > r || rt < l)
             return INT_MAX;
         if (l <= lt && rt <= r)
             return v->mini;
         return min(get(v->left, l, r, lt, mid), get(v->right, l, r, mid + 1, rt));
     }
     void set(vx v, int value, int lt, int rt, int x) {
         if (x > rt || x < lt)
             return;
         if (lt == rt) {
             v->mini = value;
         } else if (mid >= x) {
             set(v->left, value, lt, mid, x);
         } else {
             set(v->right, value, mid + 1, rt, x);
         }
         setMin(v);
     }
};
int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    SegTree tree(v, n);
    string oper;
    while (cin >> oper) {
        if (oper == "min") {
            int l, r;
            cin >> l >> r;
            cout << tree.get(l - 1, r - 1) << endl;
        } else {
            int i, data;
            cin >> i >> data;
            tree.set(data, i - 1);
        }
    }
    return 0;
}
