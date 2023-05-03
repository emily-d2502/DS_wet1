
#include "wet1util.h"
#include "Group.h"

class User {
public:
    User();
    User(const User& other) = delete;
    User& operator=(const User& other) = delete;
    ~User();
private:
    int _id;
    bool _vip;
    int _views[4];
    Group *_group;
};
