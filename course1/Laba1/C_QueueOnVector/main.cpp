#include <iostream>
#include <exception>

using namespace std;

class Product {
 public:
     Product(const char* name, int quantity, double price) : name_(const_cast<char *>(name)), quantity_(quantity), price_(price) {};

     char *getName() const {return name_; }

     int getQuantity() const { return quantity_; }

     double getPrice_() const { return price_; }

 private:
     char *name_;  // Указатель владеет C-style строкой, на которую указывает.
     int quantity_;
     double price_;
};

template<typename T>
class vector {
 private:
     T *_mass;
     int _massSize;

     void resize(T *newMass) {
         for (int j = begin; j < begin + size; j++) {
             newMass[j-begin] = _mass[j%_massSize];
         }
         begin = 0;
         end = size;
         delete[] _mass;
         _mass = newMass;
     }

     void _resizeUp() {
         T *newMass = static_cast<Product *>(malloc(_massSize * 2 * sizeof(T)));
         resize(newMass);
         _massSize *= 2;
     }

     void _resizeDown() {
         T *newMass = static_cast<Product *>(malloc(_massSize / 2 * sizeof(T)));
         resize(newMass);
         _massSize /= 2;
     }

 public:
     int begin, end, size;

     T operator[](int i){
         return get(i);
     }

     explicit vector(size_t n){
         if (n < 1)
             throw exception();
         _massSize = n;
         _mass = static_cast<T *>(malloc(n * sizeof(T)));
         begin = 0;
         end = 0;
         size = 0;
     }

     vector() {
         _massSize = 2;
         _mass = new T[_massSize];
         begin = 0;
         end = 0;
         size = 0;
     }

     void push(const T & value) {
         if (size == _massSize) {
             _resizeUp();
         }
         _mass[end] = value;
         end = (end+1) % _massSize;
         size++;
     }

     T pop() {
         T x = _mass[begin];
         begin = (begin + 1) % _massSize;
         size--;
         if (size * 2 < _massSize) {
             _resizeDown();
         }
         return x;
     }

     T get(int index) {
         if (index < 0)
             throw exception();
         return _mass[index];
     }

     T get() {
         return _mass[end - 1];
     }

     void clear() {
         _massSize = 2;
         _mass = new T[_mass];
         end = 0;
     }
     ~vector(){
         delete[] _mass;
     }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Product> v(5);
    v.push(Product("Vasya", 5, 13.5));
    cout << v.size << endl;
    cout << v[0].getName();
    return 0;
}
