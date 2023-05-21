
#ifndef USER_H_
#define USER_H_


#include "../wet1util.h"
#include "Group.h"

class Group;
class User {
public:
    User(int userId, bool isVip);
    User(const User& other)            = default;
    User& operator=(const User& other) = default;
    ~User()                            = default;

    bool vip() const;
    void watch(Genre genre);
    int views(Genre genre) const;
    void add_to_group(Group *group);

private:
    int _id;
    bool _vip;
    int _views[(int)Genre::NONE + 1];
    Group *_group;
};


#endif