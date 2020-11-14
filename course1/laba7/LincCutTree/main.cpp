#include <iostream>
#define vx vertex*
#include <random>

using namespace std;

#define SEED 12345
mt19937 getRand(SEED);

struct vertex {
    int key;
    vx parent;
    vx left;
    vx right;
};

vx make_v(int value, vx parent) {
    auto *v = new vertex;
    v->key = value;
    v->parent = parent;
    v->left = v->right = nullptr;
    return v;
}

class SplayTree{
 public:
     SplayTree(vector<vector<int>> &ss){

     }

     explicit SplayTree(vx v) : root(v){

     }

     vx splay(vx v){
         while (v->parent != nullptr){
             if (v == v->parent->left){
                 if (gParent(v) == nullptr){
                     rzig(v);
                 }else if (v->parent == gParent(v)->left){
                     rzig(v->parent);
                     rzig(v);
                 } else {
                     rzig(v);
                     lzig(v);
                 }
             } else {
                 if (gParent(v) == nullptr){
                     lzig(v);
                 } else if (v->parent == gParent(v)->right){
                     lzig(v->parent);
                     lzig(v);
                 } else {
                     lzig(v);
                     rzig(v);
                 }
             }
         }
     }


     SplayTree split(vx v){
         splay(v);
         vx r = v->right;
         v->right = nullptr;
         if (r) r->parent = nullptr;
         return SplayTree(r);
     }

     vx merge(SplayTree s){
         vx maxi = root;
         while (maxi->right)
             maxi = maxi->right;
         splay(maxi);
         maxi->right = s.root;
     }

 private:
     vx root;

     void dfs(){

     }

     vx parent(vx v){
         return v ? v->parent : nullptr;
     }

     vx gParent(vx v) {
         return v ? parent(v->parent) : nullptr;
     }

     vx rzig(vx v){
         v->parent->left = v->right;
         v->right->parent = v->parent;
         v->right = v->parent;
         v->parent->parent = v; // x отец p
         v->parent = nullptr;
     }

     vx lzig(vx v){
         v->parent->right = v->left;
         v->left->parent = v->parent;
         v->left = v->parent;
         v->parent->parent = v;
         v->parent = nullptr;
     }

};

int main() {


    return 0;

}