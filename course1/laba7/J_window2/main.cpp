#include <iostream>
#include <vector>
#include <algorithm>
#define mid lt + (rt-lt)/2
#define vx Element *

using namespace std;

struct Window {
    int y, r, l;
    char ble;
};

Window make_window(int y, int l, int r, char ble) {
    Window *node = new Window;
    node->y = y;
    node->r = r;
    node->l = l;
    node->ble = ble;
    return *node;
}

struct Element {
    int maxi = INT_MIN;
    long long add = 0;
    vx right = nullptr;
    vx left = nullptr;
    int x = 0;
};

void setMax(vx v) {
    if (!v)
        return;
    if (v->left && v->right) {
        if (v->left->maxi > v->right->maxi) {
            v->maxi = v->left->maxi;
            v->x = v->left->x;
        } else {
            v->maxi = v->right->maxi;
            v->x = v->right->x;
        }
    } else if (v->left) {
        v->maxi = v->left->maxi;
        v->x = v->left->x;
    } else if (v->right) {
        v->maxi = v->right->maxi;
        v->x = v->right->x;
    }
}

vx make_vertex(vx left, vx right) {
    vx node = new Element();
    node->right = right;
    node->left = left;
    setMax(node);
    return node;
}
vx make_list(int value, int x) {
    vx node = new Element();
    node->maxi = value;
    node->left = nullptr;
    node->right = nullptr;
    node->x = x;
    return node;
}

class SegTree {
 public:
     SegTree(int n) : size(n) {
         root = build(0, size - 1);
     }
     pair<int, int> get(int l, int r) {
         return get(root, l, r, 0, size - 1);
     }
     void Add(int l, int r, int value) {
         Add(root, value, 0, size - 1, l, r);
     }

 private:
     int size;
     vx root;
     void Add(vx v, int value, int lt, int rt, int l, int r) {
         if (lt > r || rt < l)
             return;
         if (v->add) {
             if (v->left) {
                 v->left->add += v->add;
                 v->left->maxi += v->add;
             }
             if (v->right) {
                 v->right->add += v->add;
                 v->right->maxi += v->add;
             }
             v->add = 0;
         }
         if (l <= lt && rt <= r) {
             v->add += value;
             v->maxi += value;
         } else {
             Add(v->left, value, lt, mid, l, r);
             Add(v->right, value, mid + 1, rt, l, r);
             setMax(v);
         }
     }

     vx build(int lt, int rt) {
         if (lt == rt)
             return make_list(0, lt);
         return make_vertex(build(lt, mid), build(mid + 1, rt));
     }
     pair<int, int> get(vx v, int l, int r, int lt, int rt) {
         return {v->maxi, v->x};
     }
};

bool comp(Window a, Window b) {
    return (a.y == b.y) ? a.ble < b.ble : a.y < b.y;
}

const int off = 1000000;

int main() {
    int n, x1, y1, x2, y2;
    cin >> n;
    vector<Window> W;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        W.push_back(make_window(y1, x1, x2, 'b'));
        W.push_back(make_window(y2, x1, x2, 'e'));
    }
    sort(W.begin(), W.end(), comp);
    SegTree tree(2 * off);
    int bla;
    int ans = INT_MIN;
    int x, y;
    pair<int, int> q;
    for (int i = 0; i < 2 * n; i++) {
        if (W[i].ble == 'b') bla = 1;
        else bla = -1;
        tree.Add(W[i].l + off, W[i].r + off, bla);
        q = tree.get(0, 2 * n - 1);
        if (q.first > ans) {
            ans = q.first;
            x = q.second - off;
            y = W[i].y;
        }
    }
    cout << ans << endl << x << ' ' << y << endl;
    return 0;
}