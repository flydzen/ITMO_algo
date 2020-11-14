#include <iostream>
#include <vector>
#define mid lt + (rt-lt)/2
#define vx Element *

using namespace std;

int r;

struct Matrix {
    int m[2][2]{};
    Matrix(int data[4]) {
        m[0][0] = data[0];
        m[0][1] = data[1];
        m[1][0] = data[2];
        m[1][1] = data[3];
    }
    Matrix() {
        m[0][0] = 1;
        m[0][1] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
    }

    Matrix operator*(Matrix const &x) {
        Matrix res{};
        res.m[0][0] = (m[0][0] * x.m[0][0] + m[0][1] * x.m[1][0]) % r;
        res.m[0][1] = (m[0][0] * x.m[0][1] + m[0][1] * x.m[1][1]) % r;
        res.m[1][0] = (m[1][0] * x.m[0][0] + m[1][1] * x.m[1][0]) % r;
        res.m[1][1] = (m[1][0] * x.m[0][1] + m[1][1] * x.m[1][1]) % r;
        return res;
    }
    void print() {
        cout << m[0][0] << " " << m[0][1] << endl
             << m[1][0] << " " << m[1][1] << endl;
    }
};

struct Element {
    Matrix data{};
    vx right = nullptr;
    vx left = nullptr;
};

void setData(vx v) {
    if (!v)
        return;
    if (v->left && v->right) {
        v->data = v->left->data * v->right->data;
    } else if (v->left) {
        v->data = v->left->data;
    } else if (v->right) {
        v->data = v->right->data;
    }
}

vx make_vertex(vx left, vx right) {
    vx node = new Element();
    node->right = right;
    node->left = left;
    setData(node);
    return node;
}
vx make_list(Matrix &value) {
    vx node = new Element();
    node->data = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

class SegTree {
 public:
     SegTree(vector<Matrix> &v, int n) : size(n) {
         root = build(v, 0, size - 1);
     }
     Matrix get(int l, int r) {
         return get(root, l, r, 0, size - 1);
     }
     void set(Matrix value, int x) {
         set(root, value, 0, size - 1, x);
     }

 private:
     int size;
     vx root;
     vx build(vector<Matrix> &v, int lt, int rt) {
         if (lt == rt)
             return make_list(v[lt]);
         return make_vertex(build(v, lt, mid), build(v, mid + 1, rt));
     }
     Matrix get(vx v, int l, int r, int lt, int rt) {
         if (lt > r || rt < l) {
             Matrix h{};
             return h;
         }
         if (l <= lt && rt <= r)
             return v->data;
         return get(v->left, l, r, lt, mid) * get(v->right, l, r, mid + 1, rt);
     }

     void set(vx v, Matrix &value, int lt, int rt, int x) {
         if (x > rt || x < lt)
             return;
         if (lt == rt) {
             v->data = value;
         } else if (mid >= x) {
             set(v->left, value, lt, mid, x);
         } else {
             set(v->right, value, mid + 1, rt, x);
         }
         setData(v);
     }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> r >> n >> m;
    vector<Matrix> v(n);
    for (int i = 0; i < n; i++) {
        int data[4];
        for (int &j : data)
            cin >> j;
        v[i] = {data};
    }
    SegTree tree(v, n);
    for (int i = 0; i < m; i++) {
        int l_, r_;
        cin >> l_ >> r_;
        tree.get(l_ - 1, r_ - 1).print();
        cout << endl;
    }
    return 0;
}
