
#pragma once
#include "../macros.h"
#include <assert.h>
#define GENERIC_FRIEND_CLASS(x) \
template<typename, typename>    \
friend class x

template<typename T, typename K>
class Node {
public:
    Node(const K& key, T *data);
    Node(const Node&) = default;
    Node& operator=(const Node&) = default;
    ~Node() = default;
    static void swap(Node *v, Node *u);

    void deleteData(Node<T,K>* root);

    void deleteKeys(Node<T,K>* root);


private:
    GENERIC_FRIEND_CLASS(AVL);

    K _key;
    T* _data;
    Node *_right;
    Node *_left;

    int _height;
    bool leaf();
    int children();
    Node *only_child();

    static int BF(Node *v);
    static int height(Node *v);
    static void rr_rotation(Node *v);
    static void ll_rotation(Node *v);
    static void lr_rotation(Node *v);
    static void rl_rotation(Node *v);
};

template<typename T, typename K>
Node<T,K>::Node(const K& key, T *data):
    _key(key),
    _data(data),
    _right(nullptr),
    _left(nullptr),
    _height(0) {}

template<typename T, typename K>
void Node<T,K>::swap(Node *v, Node *u) {
    T *temp_data = u->_data;
    u->_data = v->_data;
    v->_data = temp_data;

    K temp_key = u->_key;
    u->_key = v->_key;
    v->_key = temp_key;
}

template<typename T, typename K>
bool Node<T,K>::leaf() {
    return ((!_right) && (!_left));
}

template<typename T, typename K>
int Node<T,K>::children() {
    if (_left && _right) {
        return 2;
    }
    if (_left || _right) {
        return 1;
    }
    return 0;
}

template<typename T, typename K>
Node<T,K> *Node<T,K>::only_child() {
    assert(children() == 1);
    return (!_right) ? _left : _right;
}


template<typename T, typename K>
int Node<T,K>::BF(Node *v) {
    if (v->_left && v->_right) {
        return v->_left->_height - v->_right->_height;
    }
    if (v->_right) {
        return - v->_right->_height - 1;
    }
    if (v->_left) {
        return v->_left->_height + 1;
    }
    return 0;
}


template<typename T, typename K>
int Node<T,K>::height(Node *v) {
    if (v->_left && v->_right) {
        return MAX(v->_left->_height, v->_right->_height) + 1;
    }
    if (v->_right) {
        return v->_right->_height + 1;
    }
    if (v->_left) {
        return v->_left->_height + 1;
    }
    return 0;
}


template<typename T, typename K>
void Node<T,K>::rr_rotation(Node *v) {
    Node *u = v->_right;
    swap(u,v);

    v->_right = u->_right;
    u->_right = u->_left;
    u->_left = v->_left;
    v->_left = u;

    u->_height = height(u);
    v->_height = height(v);
}


template<typename T, typename K>
void Node<T,K>::ll_rotation(Node *v) {
    Node *u = v->_left;
    swap(u,v);

    v->_left = u->_left;
    u->_left = u->_right;
    u->_right = v->_right;
    v->_right = u;

    u->_height = height(u);
    v->_height = height(v);
}

template<typename T, typename K>
void Node<T,K>::lr_rotation(Node *v) {
    rr_rotation(v->_left);
    ll_rotation(v);
    v->_height = height(v);
}

template<typename T, typename K>
void Node<T,K>::rl_rotation(Node *v) {
    ll_rotation(v->_right);
    rr_rotation(v);
    v->_height = height(v);
}


template<class T,class K>
void Node<T,K>::deleteData(Node* root)
{
    if (root == nullptr){
        return;
    }
    if (root->_left){
        root->_left->deleteData(root->_left);
    }
    if (root->_right){
        root->_right->deleteData(root->_right);
    }
    delete root->_data;
}

template<class T,class K>
void Node<T,K>::deleteKeys(Node* root)
{
    if (root == nullptr){
        return;
    }
    if (root->_left){
        root->_left->deleteData(root->_left);
    }
    if (root->_right){
        root->_right->deleteData(root->_right);
    }
    delete &(root->_key);
}