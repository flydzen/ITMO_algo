#include <iostream>

using namespace std;

template<typename T>
struct Node {
    Node *next = nullptr;
    T value;
};

template<typename T>
class list {
 public:
     Node<T> *head;
     int size;

     list() {
         head = nullptr;
         size = 0;
     }

     ~list() {
         clear();
     }

     void add(T v) {
         auto *el = new Node<T>;
         el->value = v;
         el->next = head;
         head = el;
         size++;
     }

     bool empty() {
         return size == 0;
     }

     void pop() {
         Node<T> *temp = head->next;
         delete (head);
         head = temp;
         size--;
     }

     T top() {
         if (head != nullptr) {
             return head->value;
         } else {
             return false;
         }
     }

     T get() {
         T x = top();
         pop();
         return x;
     }

     void clear() {
         for (int j = 0; j < size; j++) {
             pop();
         }
     }
};

int main() {
    list<int> nums;
    char ch;
    while (cin >> ch) {
        if (isdigit(ch)) {
            nums.add(ch - '0');
        } else {
            int a = nums.get();
            int b = nums.get();
            if (ch == '+') {
                nums.add(a + b);
            } else if (ch == '-') {
                nums.add(b - a);
            } else {
                nums.add(a * b);
            }
        }
    }
    cout << nums.top();
    return 0;
}
