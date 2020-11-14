#include <iostream>
#include <vector>
#include <cassert>
#define mid lt + (rt-lt)/2
#define vx Element *
#define ll long long

using namespace std;

struct Element {
    ll mini = LONG_LONG_MAX;
    ll add = 0;
    ll set = LONG_LONG_MIN;
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

class SegTree {
 public:
     SegTree(vector<int> &v, int n) : size(n) {
         counter = 0;
         ptr = nullptr;
         ptr = (Element *) std::malloc((n * 2) * sizeof(Element));
         assert(ptr);
         root = build(v, 0, size - 1);
     }
     ~SegTree() {
         free(ptr);
     }
     ll get(int l, int r) {
         return get(root, l, r, 0, size - 1);
     }
     void add(int l, int r, ll value) {
         add(root, value, 0, size - 1, l, r);
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
                 v->left->add = 0;
                 v->left->set = v->set;
                 v->left->mini = v->set;
             }
             if (v->right) {
                 v->right->add = 0;
                 v->right->set = v->set;
                 v->right->mini = v->set;
             }
             v->set = LONG_LONG_MIN;
         }
         if (v->add) {
             if (v->left) {
                 v->left->add += v->add;
                 v->left->mini += v->add;
             }
             if (v->right) {
                 v->right->add += v->add;
                 v->right->mini += v->add;
             }
             v->add = 0;
         }
     }
     vx make_list(int value) {
         vx node = &ptr[counter++];
         node->right = nullptr;
         node->left = nullptr;
         node->mini = value;
         node->add = 0;
         node->set = LONG_LONG_MIN;
         return node;
     }
     vx make_vertex(vx left, vx right) {
         vx node = &ptr[counter++];
         node->right = right;
         node->left = left;
         node->add = 0;
         node->mini = LONG_LONG_MAX;
         node->set = LONG_LONG_MIN;
         setMin(node);
         return node;
     }

     vx build(vector<int> &v, int lt, int rt) {
         if (lt == rt)
             return make_list(v[lt]);
         return make_vertex(build(v, lt, mid), build(v, mid + 1, rt));
     }

     void add(vx v, ll value, int lt, int rt, int l, int r) {
         if (lt > r || rt < l)
             return;
         toDown(v);
         if (l <= lt && rt <= r) {
             v->add += value;
             v->mini += value;
         } else {
             add(v->left, value, lt, mid, l, r);
             add(v->right, value, mid + 1, rt, l, r);
             setMin(v);
         }
     }

     void set(vx v, ll value, int lt, int rt, int l, int r) {
         if (lt > r || rt < l)
             return;
         toDown(v);
         if (l <= lt && rt <= r) {
             v->set = value;
             v->add = 0;
             v->mini = value;
         } else {
             set(v->left, value, lt, mid, l, r);
             set(v->right, value, mid + 1, rt, l, r);
             setMin(v);
         }
     }

     ll get(vx v, int l, int r, int lt, int rt) {
         toDown(v);
         setMin(v);
         if (lt > r || rt < l)
             return LONG_LONG_MAX;
         if (l <= lt && rt <= r)
             return v->mini;
         return min(get(v->left, l, r, lt, mid), get(v->right, l, r, mid + 1, rt));
     }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    SegTree tree(v, n);
    string oper;
    int l, r, u;
    while (cin >> oper) {
        if (oper == "min") {
            cin >> l >> r;
            cout << tree.get(l - 1, r - 1) << endl;
        } else if (oper == "add") {
            cin >> l >> r >> u;
            tree.add(l - 1, r - 1, u);
        } else if (oper == "set") {
            cin >> l >> r >> u;
            tree.set(l - 1, r - 1, u);
        }
    }
    return 0;
}
