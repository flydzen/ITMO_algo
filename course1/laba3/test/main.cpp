#include <iostream>
using namespace std;
int main() {
  long long c = 0;
  for (long long i = 0; i < 100000000000; i++){
    c += 1;
  }
  cout << c;
  return 0;
}