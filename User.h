
#include "wet1util.h"

class User {
public:
    User();
    User(const AVL& other) = delete;
    User& operator=(const AVL& other) = delete;
    ~User();
private:
    NODE _id;
    bool _vip;
    int _views[5];
    Group *_group;
};
