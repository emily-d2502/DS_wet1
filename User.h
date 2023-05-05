
#include "wet1util.h"
#include "Group.h"

class User {
public:
    User();
    User(const User& other) = delete;
    User& operator=(const User& other) = delete;
    ~User();

    int getVIP() const;

private:
    int _id;
    bool _vip;
    int _views[4];
    Group *_group;
};


int User::getVIP() const {
    return this->_vip;
}