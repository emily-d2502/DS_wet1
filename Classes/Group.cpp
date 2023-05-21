
#include "Group.h"

int Group::getTotalViews() const {
    return this->_total_views[3];
}

int Group::size() const {
    return this->_members.size();
}

void Group::add_member(int userId, User *user) {
    _members.insert(userId, user);
    if (user->vip()) {
        ++_vip;
    }
    user->add_to_group(this);
}

bool Group::vip() const {
    return _vip > 0;
}

void Group::watch(Genre genre) {
    ++_group_views_parameter[(int)genre];
    ++_group_views_parameter[(int)Genre::NONE];
}