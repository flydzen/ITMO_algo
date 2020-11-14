#include <iostream>

using namespace std;

template<typename T>
class vector {
private:
    T *_mass;
    int _massSize;

    void resize(T *newMass) {
        for (int i = begin; i < end; i++) {
            newMass[i] = _mass[i];
        }
        delete[] _mass;
        _mass = newMass;
    }

    void _resizeUp() {
        T *newMass = new T[_massSize * 2];
        resize(newMass);
        _massSize *= 2;
    }

    void _resizeDown() {
        T *newMass = new T[_massSize / 2];
        resize(newMass);
        _massSize /= 2;
    }

public:
    int begin, end;

    vector() {
        _massSize = 2;
        _mass = new T[_massSize];
        begin = 0;
        end = 0;
    }

    void push(T value) {
        if (end == _massSize) {
            _resizeUp();
        }
        _mass[end] = value;
        end++;
    }

    void insert(int index, T value) {
        if (end == _massSize) {
            _resizeUp();
        }
        for (int i = end; i > index; i--) {
            _mass[i] = _mass[i - 1];
        }
        _mass[index] = value;
        ++end;
    }

    void pop_back() {
        end--;
        if (end * 2 < size()) {
            _resizeDown();
        }
    }

    T get(int index) {
        return _mass[index];
    }

    T get() {
        return _mass[end - 1];
    }

    int size() {
        return end - begin;
    }

    void clear() {
        _massSize = 2;
        _mass = new T[_mass];
        end = 0;
    }
};



struct Node {
    Node *next = NULL;
    int value = 0;
};

class list {
public:
    Node *head;
    Node *tail;

    list() {
        head = nullptr;
        tail = nullptr;
    }

    void add(int v) {
        Node *el = new Node;
        el->value = v;
        el->next = nullptr;
        if (head) {
            head->next = el;
        }
        head = el;
        if (!tail) {
            tail = el;
        }
    }

    void pop_bot() {
        Node *temp = tail->next;
        delete(tail);
        if (tail == head) {
            tail = nullptr;
            head = nullptr;
        } else {
            tail = temp;
        }
    }

    int bot() {
        return tail->value;
    }
};

int main() {
    list<> s1;
    list<int> s2;

    vector<int> v;
    int n, m, k, a, b, c;
    int ks[2];
    cin >> n >> m >> k >> a >> b >> c;
    int x;
    int summ = 0;

    for (int j = 0; j < k; j++) {
        cin >> x;
        v.push(x);
    }
    // ввели в вектор первые k чисел
    for (int j = k; j < n; j++) {
        int posA = v.get(v.end-2)*a;
        int posB = v.get(v.end-1)*b;
        int y = v.get(v.end-2)*a + v.get(v.end-1)*b + c;
        v.push(y);
    }
    // добавили оставшиеся
    for (int j = 0; j < m-1; j++) {
        s1.add(v.get(j));
    }
    // добавили в стек m первых
    for (int j = m-1; j < n; j++) {
        s1.add(v.get(j));
        summ += get(&s1, &s2);
    }

    cout << endl;
    cout << summ;

    return 0;
}