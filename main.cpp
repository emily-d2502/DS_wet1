#include "AVL/AVL.h"
#include <iostream>
using namespace std;

int main() {
    AVL<int, int> l, e;

    for (int i = 0; i < 100000; ++i) {
        l.insert(i, new int);
    }

    for (int i = 0; i < 100000; ++i) {
        e.insert(i, new int);
    }
    for (int i = 0; i < 50000; ++i) {
        e.remove(i);
    }
    return 0;
}