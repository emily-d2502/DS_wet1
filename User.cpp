
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
    if (_group) {
        ++_group->_total_views[(int)genre];
        ++_group->_total_views[(int)Genre::NONE];
    }
}

void User::add_to_group(Group *group) {
    _group = group;
    for (int i = 0; i <= (int)Genre::NONE; ++i) {
        _views[i] -= group->_group_views_parameter[i];
    }
}

void User::remove_from_group(Group *group) {
    for (int i = 0; i <= (int)Genre::NONE; ++i) {
        _views[i] += group->_group_views_parameter[i];
    }
    _group = nullptr;
}


int User::views(Genre genre) const {
    if (!_group) {
        return _views[(int)genre];
    }
    return _views[(int)genre]
    + _group->_group_views_parameter[(int)genre];
}

int User::id() const {
    return _id;
}

Group *User::getGroup() {
    return this->_group;
}

void User::set_group_null(User& user) {
    user.remove_from_group(user._group);
}