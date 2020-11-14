#include <iostream>
#define ll unsigned long long

using namespace std;

int mod1e10(long long v) {
    return (int) (v % 1000000000);
}

struct vertex {
    int key;
    int height;
    ll sLeft, sRight;
    vertex *left, *right;
};

vertex *make_v(int value) {
    auto *v = new vertex;
    v->key = value;
    v->left = v->right = nullptr;
    v->height = 1;
    v->sLeft = v->sRight = 0;
    return v;
}

class binaryTree {
 public:
     void print() {
         print(head);
     }

     ll lrSum(int l, int r) {
         vertex *mid = findMid(head, l, r);
         if (mid == nullptr) {
             return 0;
         }
         ll s = mid->sLeft + mid->sRight + mid->key;
         return lrSum(s, mid, l, r);
     }

     vertex *find(int x) {
         return find(head, x);
     }

     void insert(int x) {
         if (head == nullptr)
             head = make_v(x);
         else if (find(x) == nullptr)
             head = insert(head, x);
     }

 private:
     vertex *head;

     static vertex *findMid(vertex *mid, int l, int r) {
         if (mid == nullptr)
             return nullptr;
         if (mid->key >= l && mid->key <= r) {
             return mid;
         }
         if (mid->key > r)
             return findMid(mid->left, l, r);
         else
             return findMid(mid->right, l, r);
     }

     static ll lrSum(ll s, vertex *v, int l, int r) {
         vertex *temp = v;
         while (temp != nullptr) {
             if (temp->key == l) {
                 s -= temp->sLeft;
                 break;
             }
             if (temp->key < l) {
                 s -= (temp->sLeft + temp->key);
                 temp = temp->right;
             } else {
                 temp = temp->left;
             }
         }
         temp = v;
         while (temp != nullptr) {
             if (temp->key == r) {
                 s -= temp->sRight;
                 break;
             }
             if (temp->key > r) {
                 s -= (temp->sRight + temp->key);
                 temp = temp->left;
             } else {
                 temp = temp->right;
             }
         }
         return s;
     }

     static vertex *lowLeftRotate(vertex *v) {
         vertex *temp = v->right;
         v->right = temp->left;
         temp->left = v;
         setHeight(v);
         setHeight(temp);
         return temp;
     }

     static vertex *lowRightRotate(vertex *v) {
         vertex *temp = v->left;
         v->left = temp->right;
         temp->right = v;
         setHeight(v);
         setHeight(temp);
         return temp;
     }

     static vertex *bigLeftRotate(vertex *v) {
         v->right = lowRightRotate(v->right);
         return lowLeftRotate(v);
     }

     static vertex *bigRightRotate(vertex *v) {
         v->left = lowLeftRotate(v->left);
         return lowRightRotate(v);
     }

     static vertex *balance(vertex *v) {
         if (v == nullptr)
             return v;
         setHeight(v);
         int b = getBalance(v);
         if (b == -2) {
             if (getBalance(v->right) > 0)
                 return bigLeftRotate(v);
             else
                 return lowLeftRotate(v);
         } else if (b == 2) {
             if (getBalance(v->left) < 0)
                 return bigRightRotate(v);
             else
                 return lowRightRotate(v);
         }
         return v;
     }

     static void setHeight(vertex *v) {
         v->height = max(getHeight(v->left), getHeight(v->right)) + 1;
         v->sLeft = v->left ? v->left->sLeft + v->left->sRight + v->left->key : 0;
         v->sRight = v->right ? v->right->sLeft + v->right->sRight + v->right->key : 0;
     }

     static int getBalance(vertex *v) {
         return getHeight(v->left) - getHeight(v->right);
     }

     static int getHeight(vertex *v) {
         return v != nullptr ? v->height : 0;
     }

     static void print(vertex *v) {
         if (v != nullptr) {
             cout << v->key << endl;
             print(v->left);
             print(v->right);
         }
     }

     static vertex *find(vertex *v, int x) {
         if (v == nullptr || v->key == x)
             return v;
         if (x < v->key)
             return find(v->left, x);
         else
             return find(v->right, x);
     }

     static vertex *mini(vertex *v) {
         if (v->left == nullptr)
             return v;
         return mini(v->left);
     }

     static vertex *maxi(vertex *v) {
         if (v->right == nullptr)
             return v;
         return maxi(v->right);
     }

     static vertex *insert(vertex *v, int x) {
         if (v == nullptr)
             return make_v(x);
         else if (x < v->key)
             v->left = insert(v->left, x);
         else
             v->right = insert(v->right, x);
         return balance(v);
     }
};

int main() {
    binaryTree bt{};
    string inp;
    int n;
    cin >> n;
    long long last = -1;
    for (int i = 0; i < n; i++) {
        cin >> inp;
        if (inp == "+") {
            int value;
            cin >> value;
            if (last != -1) {
                bt.insert(mod1e10(value + last));
            } else {
                bt.insert(value);
            }
            last = -1;
        } else {
            int l, r;
            cin >> l >> r;
            last = (long long) bt.lrSum(l, r);
            cout << last << endl;
        }
    }
    return 0;
}
