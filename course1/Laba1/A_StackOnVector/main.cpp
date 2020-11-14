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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> s;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char command;
        cin >> command;
        if (command == '-') {
            cout << s.get() << endl;
            s.pop_back();
        } else {
            int value;
            cin >> value;
            s.push(value);
        }
    }
    return 0;
}
