#include "Array/Array.h"
#include <iostream>
using namespace std;

int main() {
    #if !defined(NDEBUG)
    Array<int> l(10);
    for (int i = 0; i < 10; ++i) {
        cout << "Array: " << l << endl;
        l.push(i + 1);
    }
    cout << "Array: " << l << endl;
    #endif
    return 0;
}