
#include "wet1util.h"

class Group;

class User {
public:
    User(int userId, bool isVip) :
            _id(userId),
            _vip(isVip),
            _group(nullptr) {
        for (int i = 0; i < 4; i++)
        {
            _views[i]=0;
        }
    }

    User(const User& other) = delete;
    User& operator=(const User& other) = delete;
    ~User();

    int getVIP() const;
    int getId() const;
    Group * getGroup() const;


private:
    int _id;
    bool _vip;
    int _views[4];
    Group *_group;
};


int User::getVIP() const {
    return this->_vip;
}

int User::getId() const {
    return this->_id;
}

Group * User::getGroup() const {
    return this->_group;
}