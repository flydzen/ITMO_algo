#include <iostream>
#include <random>
#define vx vertex*

using namespace std;

#define SEED 12345
mt19937 getRand(SEED);

struct vertex {
    int key;
    int prior;
    int count;
    int data;
    vertex *left, *right;
};

vx make_v(int value) {
    auto *v = new vertex;
    v->data = value;
    v->key = value;
    v->left = v->right = nullptr;
    v->count = 1;
    v->prior = getRand();
    return v;
}

int count(vx v) {
    return v == nullptr ? 0 : v->count;
}

void newCount(vx v) {
    if (v != nullptr)
        v->count = count(v->left) + count(v->right) + 1;
}

void split(vx v, vx&left, vx&right, int k) {
    if (v == nullptr) {
        left = right = nullptr;
        return;
    }
    int cur = count(v->left) + 1;
    if (cur <= k) {
        split(v->right, v->right, right, k - cur);
        left = v;
    } else {
        split(v->left, left, v->left, k);
        right = v;
    }
    newCount(v);
}

void merge(vx&v, vx left, vx right) {
    if (left == nullptr) {
        v = right;
        return;
    }
    if (right == nullptr) {
        v = left;
        return;
    }
    if (left->prior > right->prior) {
        merge(left->right, left->right, right);
        v = left;
    } else {
        merge(right->left, left, right->left);
        v = right;
    }
    newCount(v);
}

void del(vx& v, int k){
    int cur = count(v->left) + 1;
    if (cur == k){
        merge(v, v->left, v->right);
    }else if (cur < k) {
        del(v->left, k - cur);
    } else {
        del(v->right, k);
    }
}

void insert(vx&v, vx k) {
    if (!v) {
        v = k;
        return;
    }
    if (v->prior > k->prior) {
        (k->key < v->key) ? insert(v->left, k) : insert(v->right, k);
    } else {
        split(v, k->left, k->right, k->key);
        v = k;
    }
    newCount(v);
}

void push(vx&v, vx k, int pos) {
    vx l;
    vx r;
    split(v, l, r, pos);
    merge(l, l, k);
    merge(v, l, r);
}

void print(vx v) {
    if (v->left != nullptr) {
        print(v->left);
    }
    cout << v->data << " ";
    if (v->right != nullptr) {
        print(v->right);
    }
}

void move(vx v, int l, int r) {
    vx left;
    vx right;
    vx mid;
    split(v, left, right, r);
    split(left, left, mid, l);
    merge(v, mid, left);
    merge(v, v, right);
}
// 1 2 3 4 5 6
// 2 3 4 1 5 6
int main() {
    int n, m;
    vx v = make_v(1);
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        insert(v, make_v(i));
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        move(v, l - 1, r);
    }
    print(v);
    cout << endl;
    return 0;
}