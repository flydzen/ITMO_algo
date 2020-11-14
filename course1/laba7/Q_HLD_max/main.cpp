#include <iostream>
#include <vector>
#define mid (lt + (rt-lt)/2)
#define vx Element *

using namespace std;


struct Element {
    int maxi = 0;
    vx right = nullptr;
    vx left = nullptr;
};

void setMax(vx v) {
    if (!v)
        return;
    if (v->left && v->right) {
        v->maxi = max(v->left->maxi, v->right->maxi);
    } else if (v->left) {
        v->maxi = v->left->maxi;
    } else if (v->right) {
        v->maxi = v->right->maxi;
    }
}

vx make_vertex(vx left, vx right) {
    vx node = new Element();
    node->right = right;
    node->left = left;
    setMax(node);
    return node;
}
vx make_list(int value) {
    vx node = new Element();
    node->maxi = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

class SegTree {
 public:
     void create(vector<int> &v) {
         size = v.size();
         root = build(v, 0, size - 1);
     }
     SegTree() {
         root = nullptr;
         size = 0;
     }
     explicit SegTree(vector<int> &v) : size(v.size()) {
         root = build(v, 0, size - 1);
     }
     int get(int l, int r) {
         return get(root, l, r, 0, size - 1);
     }
     void add(int value, int x) {
         add(root, value, 0, size - 1, x);
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
             return INT_MIN;
         if (l <= lt && rt <= r)
             return v->maxi;
         return max(get(v->left, l, r, lt, mid), get(v->right, l, r, mid + 1, rt));
     }
     void add(vx v, int value, int lt, int rt, int x) {
         if (x > rt || x < lt)
             return;
         if (lt == rt) {
             v->maxi += value;
         } else if (mid >= x) {
             add(v->left, value, lt, mid, x);
         } else {
             add(v->right, value, mid + 1, rt, x);
         }
         setMax(v);
     }
};

class HLD {
 public:
     explicit HLD(vector<vector<int>> &ss) : size_(ss.size()) {
         depth.resize(size_);
         head.resize(size_);
         heavy.resize(size_, -1);
         time.resize(size_);
         parent.resize(size_);
         timer = 0;
         dfs(0, ss);
         build(0, 0, ss);
         vector<int> fold(size_);
         st.create(fold);
     }
     int maxi(int a, int b) {
         int ans = 0;
         while (head[a] != head[b]) {
             if (depth[head[a]] > depth[head[b]])
                 swap(a, b);
             int wayMax = st.get(time[head[b]], time[b]);
             if (wayMax > ans) ans = wayMax;
             b = parent[head[b]];
         }
         if (depth[a] > depth[b])
             swap(a, b);
         int wayMax = st.get(time[a], time[b]);
         if (wayMax > ans) ans = wayMax;
         return ans;
     }

     void add(int v, int value) {
         st.add(value, time[v]);
     }

 private:
     size_t size_;
     vector<int> depth;
     vector<int> head;
     vector<int> heavy;
     vector<int> time;
     vector<int> parent;
     SegTree st;
     int timer;

     int dfs(int v, vector<vector<int>> &ss) {
         int size = 1;
         int maxSize = 0;
         for (int i : ss[v]) {
             if (i != parent[v]) {
                 parent[i] = v;
                 depth[i] = depth[v] + 1;
                 int subSize = dfs(i, ss);
                 size += subSize;
                 if (subSize > maxSize) {
                     maxSize = subSize;
                     heavy[v] = i;
                 }
             }
         }
         return size;
     }

     void build(int v, int h, vector<vector<int>> &ss) {
         head[v] = h;
         time[v] = timer++;
         if (heavy[v] != -1)
             build(heavy[v], h, ss);
         for (int i : ss[v]) {
             if (i != parent[v] && i != heavy[v]) {
                 build(i, i, ss);
             }
         }
     }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ss(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        ss[a - 1].push_back(b - 1);
        ss[b - 1].push_back(a - 1);
    }
    HLD hld(ss);
    int m;
    cin >> m;
    char command;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> command >> a >> b;
        if (command == 'I') {
            hld.add(a - 1, b);
        } else {
            cout << hld.maxi(a - 1, b - 1) << endl;
        }
    }
    return 0;
}
