
#include "User.h"

User::User(int id, bool vip):
    _id(id),
    _vip(vip),
    _group(nullptr) {
    for (int i = 0; i <= (int)Genre::NONE; ++i) {
        _views[i] = 0;
    }
}

bool User::vip() const {
    return this->_vip;
}

void User::watch(Genre genre) {
    ++_views[(int)genre];
    ++_views[(int)Genre::NONE];
}

void User::add_to_group(Group *group) {
    _group = group;
    for (int i = 0; i <= (int)Genre::NONE; ++i) {
        _views[i] -= group->_group_views_parameter[i];
    }
}

int User::views(Genre genre) const {
    if (!_group) {
        return _views[(int)genre];
    }
    return _views[(int)genre]
    + _group->_group_views_parameter[(int)genre];
}