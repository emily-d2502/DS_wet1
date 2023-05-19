
#include "wet1util.h"
#include <vector>

#include <User.h>
#include <AVL.h>



class Group {
public:
    explicit Group(int GroupId) :
            _id(GroupId),
            _vip(0),
            _members(),
            _group_views_parameter(),
            _total_views() {
        for (int i = 0; i < 4; i++) {
            _group_views_parameter[i] = 0;
            _total_views[i] = 0;
        }
    }
    Group(const Group& other) = delete;
    Group& operator=(const Group& other) = delete;
    ~Group();

    int getSize() const;
    int* getTotalViews() const;
    void removeUser(int userId);
    void addUser(int userId, User* user);


private:
    int _id;
    int _vip;
    AVL<User, int> _members;
    int _total_views[4];
    int _group_views_parameter[4];
};


int* Group::getTotalViews() const {
    return this->_total_views;
}

int Group::getSize() const {
    return this->_members.getSize();
}

void Group::removeUser(int userId) {
    _members.remove(userId);
    /////do we need to change paremeters to group???
}

void Group::addUser(int userId, User* user) {
    _members.insert(userId, user);
    /////do we need to change paremeters to group??? dont remember but i think yes not info in dry
}
