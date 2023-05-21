#include "AVL/AVL.h"
#include "macros.h"

#define PRINT_NODE(n)                  \
std::cout << (n)._key << std::endl;    \
std::cout << *(n)._data << std::endl;  \
std::cout << (n)._left << std::endl;   \
std::cout << (n)._right << std::endl;  \
std::cout << (n)._height << std::endl; \
std::cout << std::endl;                \
(void)0


bool test_node_swap();
bool test_insert_rotations();

int main()
{
    RUN_TEST(test_node_swap);
    RUN_TEST(test_insert_rotations);
    return 0;
}

bool test_node_swap()
{
    Node<int, int> a(3, new int);
    Node<int, int> b(2, new int);
    a._right = new Node<int,int>(4, new int);
    a._left = new Node<int,int>(0, new int);
    b._right = new Node<int,int>(5, new int);
    b._left = new Node<int,int>(1, new int);
    Node<int, int> c = a;
    Node<int, int> d = b;
    Node<int,int>::swap(&a,&b);

    ASSERT(b._key == c._key);
    ASSERT(a._key == d._key);

    ASSERT(a._data == d._data);
    ASSERT(b._data == c._data);

    ASSERT(a._left == c._left);
    ASSERT(a._right == c._right);

    ASSERT(b._left == d._left);
    ASSERT(b._right == d._right);
    return true;
}

bool test_insert_rotations()
{
    AVL<int, int> e;
    e.insert(135, new int);
    e.insert(235, new int);
    e.insert(35, new int);
    e.insert(335, new int);

    ASSERT(e._root->_height == 2);
    ASSERT(e._root->_left->_height == 0);
    ASSERT(e._root->_right->_height == 1);

    ASSERT(e._root->_key == 135);
    ASSERT(e._root->_left->_key == 35);
    ASSERT(e._root->_right->_key == 235);
    ASSERT(e._root->_right->_right->_key == 335);

    // rr_rotation
    e.insert(435, new int);
    ASSERT(e._root->_key == 135);
    ASSERT(e._root->_left->_key == 35);
    ASSERT(e._root->_right->_key == 335);
    ASSERT(e._root->_right->_right->_key == 435);
    ASSERT(e._root->_right->_left->_key == 235);

    ASSERT(e._root->_height == 2);
    ASSERT(e._root->_left->_height == 0);
    ASSERT(e._root->_right->_height == 1);
    ASSERT(e._root->_right->_right->_height == 0);
    ASSERT(e._root->_right->_left->_height == 0);

    // rl_rotation
    e.insert(200, new int);
    ASSERT(e._root->_key == 235);
    ASSERT(e._root->_left->_key == 135);
    ASSERT(e._root->_left->_left->_key == 35);
    ASSERT(e._root->_left->_right->_key == 200);
    ASSERT(e._root->_right->_key == 335);
    ASSERT(e._root->_right->_right->_key == 435);

    ASSERT(e._root->_height == 2);
    ASSERT(e._root->_left->_height == 1);
    ASSERT(e._root->_left->_left->_height == 0);
    ASSERT(e._root->_left->_right->_height == 0);
    ASSERT(e._root->_right->_height == 1);
    ASSERT(e._root->_right->_right->_height == 0);

    // add leaf
    e.insert(300, new int);
    ASSERT(e._root->_key == 235);
    ASSERT(e._root->_left->_key == 135);
    ASSERT(e._root->_left->_left->_key == 35);
    ASSERT(e._root->_left->_right->_key == 200);
    ASSERT(e._root->_right->_key == 335);
    ASSERT(e._root->_right->_left->_key == 300);
    ASSERT(e._root->_right->_right->_key == 435);

    ASSERT(e._root->_height == 2);
    ASSERT(e._root->_left->_height == 1);
    ASSERT(e._root->_left->_left->_height == 0);
    ASSERT(e._root->_left->_right->_height == 0);
    ASSERT(e._root->_right->_height == 1);
    ASSERT(e._root->_right->_left->_height == 0);
    ASSERT(e._root->_right->_right->_height == 0);

    AVL<int, int> l;
    l.insert(135, new int);
    l.insert(235, new int);
    l.insert(35, new int);
    l.insert(34, new int);

    ASSERT(l._root->_height == 2);
    ASSERT(l._root->_left->_height == 1);
    ASSERT(l._root->_right->_height == 0);

    ASSERT(l._root->_key == 135);
    ASSERT(l._root->_left->_key == 35);
    ASSERT(l._root->_right->_key == 235);
    ASSERT(l._root->_left->_left->_key == 34);

    // ll_rotation
    l.insert(33, new int);
    ASSERT(l._root->_key == 135);
    ASSERT(l._root->_right->_key == 235);
    ASSERT(l._root->_left->_key == 34);
    ASSERT(l._root->_left->_right->_key == 35);
    ASSERT(l._root->_left->_left->_key == 33);

    ASSERT(l._root->_height == 2);
    ASSERT(l._root->_right->_height == 0);
    ASSERT(l._root->_left->_height == 1);
    ASSERT(l._root->_left->_right->_height == 0);
    ASSERT(l._root->_left->_left->_height == 0);

    // rl_rotation
    l.insert(100, new int);
    ASSERT(l._root->_key == 35);
    ASSERT(l._root->_left->_key == 34);
    ASSERT(l._root->_left->_left->_key == 33);
    ASSERT(l._root->_right->_key == 135);
    ASSERT(l._root->_right->_right->_key == 235);
    ASSERT(l._root->_right->_left->_key == 100);

    ASSERT(l._root->_height == 2);
    ASSERT(l._root->_left->_height == 1);
    ASSERT(l._root->_left->_left->_height == 0);
    ASSERT(l._root->_right->_height == 1);
    ASSERT(l._root->_right->_right->_height == 0);
    ASSERT(l._root->_right->_left->_height == 0);

    return true;
}


