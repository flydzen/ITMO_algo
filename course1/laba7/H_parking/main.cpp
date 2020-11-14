#include <iostream>
#include <vector>
#include <cassert>
#define mid lt + (rt-lt)/2
#define vx Element *
#define ll long long

using namespace std;

struct Element {
    ll mini = LONG_LONG_MAX;
    vx minEl = nullptr;
    ll set = LONG_LONG_MIN;
    int pos;
    vx right = nullptr;
    vx left = nullptr;
};

void setMin(vx v) {
    if (!v)
        return;
    if (v->left && v->right) {
        if (v->left->mini <= v->right->mini) {
            v->mini = v->left->mini;
            v->minEl = v->left->minEl;
        } else {
            v->mini = v->right->mini;
            v->minEl = v->right->minEl;
        }
    } else if (v->left) {
        v->mini = v->left->mini;
        v->minEl = v->left->minEl;
    } else if (v->right) {
        v->mini = v->right->mini;
        v->minEl = v->right->minEl;
    }
}

class SegTree {
 public:
     SegTree(int n) : size(n) {
         counter = 0;
         ptr = nullptr;
         ptr = (Element *) std::malloc((n * 2) * sizeof(Element));
         assert(ptr);
         root = build(0, size - 1);
     }
     ~SegTree() {
         free(ptr);
     }
     pair<ll, vx> get(int l, int r) {
         return get(root, l, r, 0, size - 1);
     }
     void set(int l, int r, ll value) {
         set(root, value, 0, size - 1, l, r);
     }

 private:
     int size;
     vx root;
     Element *ptr;
     int counter;

     void toDown(vx v) {
         if (v->set != LONG_LONG_MIN) {
             if (v->left) {
                 v->left->set = v->set;
                 v->left->mini = v->set;
             }
             if (v->right) {
                 v->right->set = v->set;
                 v->right->mini = v->set;
             }
             v->set = LONG_LONG_MIN;
         }
     }
     vx make_list(int pos) {
         vx node = &ptr[counter++];
         node->right = nullptr;
         node->left = nullptr;
         node->mini = 0;
         node->pos = pos;
         node->set = LONG_LONG_MIN;
         node->minEl = node;
         return node;
     }
     vx make_vertex(vx left, vx right) {
         vx node = &ptr[counter++];
         node->right = right;
         node->left = left;
         node->mini = LONG_LONG_MAX;
         node->set = LONG_LONG_MIN;
         setMin(node);
         return node;
     }

     vx build(int lt, int rt) {
         if (lt == rt)
             return make_list(lt);
         return make_vertex(build(lt, mid), build(mid + 1, rt));
     }

     void set(vx v, ll value, int lt, int rt, int l, int r) {
         if (lt > r || rt < l)
             return;
         toDown(v);
         if (l <= lt && rt <= r) {
             v->set = value;
             v->mini = value;
         } else {
             set(v->left, value, lt, mid, l, r);
             set(v->right, value, mid + 1, rt, l, r);
             setMin(v);
         }
     }

     pair<ll, vx> get(vx v, int l, int r, int lt, int rt) {
         toDown(v);
         setMin(v);
         if (lt > r || rt < l)
             return {LONG_LONG_MAX, v};
         if (l <= lt && rt <= r)
             return {v->mini, v->minEl};
         auto g1 = get(v->left, l, r, lt, mid);
         auto g2 = get(v->right, l, r, mid + 1, rt);
         if (g1.first <= g2.first)
             return g1;
         else
             return g2;
     }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    SegTree tree(n);
    string oper;
    int l;
    for (int i = 0; i < m; i++) {
        cin >> oper >> l;
        if (oper == "enter") {
            auto v = tree.get(l - 1, n - 1);
            if (v.first == 1)
                v = tree.get(0, l - 1);
            int pos = v.second->pos;
            cout << pos + 1 << endl;
            tree.set(pos, pos, 1);
        } else {
            tree.set(l - 1, l - 1, 0);
        }
    }
    return 0;
}
