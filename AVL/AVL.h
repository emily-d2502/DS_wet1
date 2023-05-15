
#pragma once
#include "class_defines.h"
#include "Node.h"
#define NODE Node<T,K>

template<typename T, typename K>
class AVL {
public:
    AVL();
    AVL(const AVL& other) = delete;
    AVL& operator=(const AVL& other) = delete;
    ~AVL();
    
    T& find(const K& key);
    void insert(const K& key, T *data);
    void remove(const K& key);

    void inOrderSetUp(Node * r, int * output, int * i);
    int getSize() const;
    int getMax() const;

    void deleteTreeData();


    class KeyExists {};
    class KeyNotFound {};
#if defined(DBUG)
public:
#else
private:
#endif
    Node *_root;
    int _size;
    
    void rotations(NODE *v);
    NODE *closest_up(NODE *v);
    NODE *closest_down(NODE *v);
    NODE *insert(NODE *root, NODE *v);
    NODE *remove(NODE *root, const K& key);
};

template<typename T, typename K>
AVL<T,K>::AVL()
{
    _root = nullptr;
    _size = 0;
}

template<typename T, typename K>
AVL<T,K>::~AVL()
{

}

template<typename T, typename K>
T& AVL<T,K>::find(const K& key)
{
    if (_root == nullptr) {
        throw KeyNotFound(); 
    }

    NODE *p = _root;
    while(p != nullptr)
    {
        if (p->_key == key) {
            return *p->_data; 
        }

        if (p->_key < key) {
            p = p->_right;
        } else {
            p = p->_left;
        }
    }
    throw KeyNotFound();
}

template<typename T, typename K>
void AVL<T,K>::insert(const K& key, T *data)
{
    Node *v = new NODE(key, data);
    _root = insert(_root, v);
    ++_size;
}

template<typename T, typename K>
void AVL<T,K>::remove(const K& key)
{
    _root = remove(_root, key);
    --_size;
}

template<typename T, typename K>
NODE *AVL<T,K>::insert(NODE *root, NODE *v)
{
    if (!root) {
        return v;
    }
    if (v->_key > root->_key) {
        root->_right = insert(root->_right, v);
    } else if (v->_key < root->_key) {
        root->_left = insert(root->_left, v);
    } else {
        throw KeyExists();
    }
    root->_height = NODE::height(root); // O(1)
    rotations(root); // O(1)
    return root;
}

template<typename T, typename K>
NODE *AVL<T,K>::remove(NODE *root, const K& key)
{
    if (!root) {
        throw KeyNotFound();
    }
    if (key > root->_key) {
        root->_right = remove(root->_right, key);
    } else if (key < root->_key) {
        root->_left = remove(root->_left, key);
    } else {
        if (root->leaf()) {
            delete root;
            return nullptr;
        }
        if (root->children() == 1) {
            NODE *tmp = root->only_child();
            delete root;
            return tmp;
        }
        NODE *new_root = closest_up(root);
        NODE::swap(new_root, root);
        root->_right = remove(root->_right, key);
    }
    root->_height = NODE::height(root); // O(1)
    rotations(root); // O(1)
    return root;
}


template<typename T, typename K>
void AVL<T,K>::rotations(NODE *v)
{
    #if defined(DBUG)
    assert(-2 <= NODE::BF(v) && NODE::BF(v) <= 2);
    #endif

    if (NODE::BF(v) == 2)
    {
        #if defined(DBUG)
        assert(-1 <= NODE::BF(v->_left) && NODE::BF(v->_left) <= 1);
        #endif

        if (NODE::BF(v->_left) == -1) {
            NODE::lr_rotation(v);
        } else {
            NODE::ll_rotation(v);
        }
    }
    else if (NODE::BF(v) == -2)
    {
        #if defined(DBUG)
        assert(-1 <= NODE::BF(v->_right) && NODE::BF(v->_right) <= 1);
        #endif

        if (NODE::BF(v->_right) == 1) {
            NODE::rl_rotation(v);
        } else {
            NODE::rr_rotation(v);
        }
    }
}

template<typename T, typename K>
NODE *AVL<T,K>::closest_up(NODE *v)
{
    assert(v->_right);
    NODE *res = v->_right;
    while (res->_left) {
        res = res->_left;
    }
    return res;
}

template<typename T, typename K>
int AVL<T,K>::getSize() const {
    return this->size_t;
}

template<typename T, typename K>
int AVL<T,K>::getMax() const {
    Node* current = this->_root;
    while(current->_right)
        current = current->_r;
    return (current->getData())->getID();
}

template<typename T, typename K>
NODE *AVL<T,K>::closest_down(NODE *v)
{
    assert(v->_left);
    NODE *res = v->_left;
    while (res->_right) {
        res = res->_right;
    }
    return res;
}

template<typename T, typename K>
void AVL<T,K>::inOrderSetUp(Node* r, int * output, int * i){
    if (r == NULL)
        return;
    /* first recur on left child */
    inOrderSetUp(r->_left);
    /* then put the data of node */
    output[*i] = r->_data;
    (*i)++;
    /* now recur on right child */
    inOrderSetUp(r->_right);
}

template<typename T, typename K>
void AVL<T,K>::deleteTreeData(){
    _root->deleteData(_root);
}
