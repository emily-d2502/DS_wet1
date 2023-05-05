
#include "wet1util.h"
#include "User.h"
#include <vector>



class Group {
public:
    Group();
    Group(const Group& other) = delete;
    Group& operator=(const Group& other) = delete;
    ~Group();

    int getSize() const;
    int* getTotalViews() const;

private:
    int _id;
    int _vip;
    std::vector<user*> _members;
    int _total_views[4];
    int _group_views_parameter[4];
};


int* Group::getTotalViews() const {
    return this->_total_views;
}

int Group::getSize() const {
    return this->_members.size();
}

