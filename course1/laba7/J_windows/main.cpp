#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#define mid lt + (rt-lt)/2
#define vx Element *

using namespace std;

struct Element {
    int maxi = INT_MIN;
    int add = 0;
    int x;
    vx right = nullptr;
    vx left = nullptr;
};

struct Window {
    Window(int y, int l, int r, char state) : y(y), l(l), r(r), state(state) {}
    int y, l, r;
    char state;
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

class SegTree {
 public:
     explicit SegTree(int n) : size(n) {
         counter = 0;
         ptr = nullptr;
         ptr = (Element *) std::malloc((n * 2) * sizeof(Element));
         assert(ptr);
         root = build(0, size - 1);
     }
     ~SegTree() {
         free(ptr);
     }
     pair<int, int> get() {
         return {root->maxi, root->x};
     }
     void add(int l, int r, int value) {
         add(root, value, 0, size - 1, l, r);
     }

 private:
     int size;
     vx root;
     Element *ptr;
     int counter;

     void toDown(vx v) {
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
     }
     vx make_list(int x) {
         vx node = &ptr[counter++];
         node->right = nullptr;
         node->left = nullptr;
         node->maxi = 0;
         node->add = 0;
         node->x = x;
         return node;
     }
     vx make_vertex(vx left, vx right) {
         vx node = &ptr[counter++];
         node->right = right;
         node->left = left;
         node->add = 0;
         node->maxi = INT_MIN;
         setMax(node);
         return node;
     }

     vx build(int lt, int rt) {
         if (lt == rt)
             return make_list(lt);
         return make_vertex(build(lt, mid), build(mid + 1, rt));
     }

     void add(vx v, int value, int lt, int rt, int l, int r) {
         if (lt > r || rt < l)
             return;
         toDown(v);
         if (l <= lt && rt <= r) {
             v->add += value;
             v->maxi += value;
         } else {
             add(v->left, value, lt, mid, l, r);
             add(v->right, value, mid + 1, rt, l, r);
             setMax(v);
         }
     }
};

bool comp(Window a, Window b) {
    return (a.y == b.y) ? a.state < b.state : a.y < b.y;
}

const int off = 1000000;

int main() {
    int n, x1, y1, x2, y2;
    cin >> n;
    vector<Window> w;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        w.emplace_back(y1, x1, x2, 'b');
        w.emplace_back(y2, x1, x2, 'e');
    }
    sort(w.begin(), w.end(), comp);
    SegTree tree(2000001);
    int ans = INT_MIN;
    pair<int, int> xy;
    for (size_t i = 0; i < w.size(); i++) {
        tree.add(w[i].l + off, w[i].r + off, w[i].state == 'b' ? 1 : -1);
        auto q = tree.get();
        if (q.first > ans) {
            ans = q.first;
            xy = {q.second - off, w[i].y};
        }
    }
    cout << ans << endl << xy.first << " " << xy.second;
    return 0;
}
