
#ifndef GROUP_H_
#define GROUP_H_

#include "../wet1util.h"
#include "User.h"
#include "../AVL/AVL.h"


class User;
class Group {
public:
    Group()                            = default;
    Group(const Group& other)            = delete;
    Group& operator=(const Group& other) = delete;
    ~Group()                             = default;

    int size() const;
    bool vip() const;
    void watch(Genre genre);
    int getMaxViews() const;
    void add_member(int userId, User *user);
    void removeUser(const User& user);


private:
    int _id;
    int _vip;
    AVL<User, int> _members;
    int _total_views[(int)Genre::NONE + 1];
    int _group_views_parameter[(int)Genre::NONE + 1];

    friend class User;
};



#endif