
#include "Group.h"
class Movie;


Group::Group(int groupId) {
    _id = groupId;
}

Group::~Group() {
    _members.apply(User::set_group_null);
}

int Group::getMaxViews() const {
    int genre = 0;
    for(int i = 0; i < (int)Genre::NONE; ++i) {
        if (_total_views[i] > genre) {
            genre = i;
        }
    }
    return genre;
}

int Group::size() const {
    return this->_members.size();
}

void Group::add_member(int userId, User *user) {
    _members.insert(userId, user);
    if (user->vip()) {
        _vip++;
    }
    for (int i = 0; i <= (int)Genre::NONE; ++i) {
        _total_views[i] += user->views((Genre)i);
    }
    user->add_to_group(this);
}

bool Group::vip() const {
    return _vip > 0;
}

AVL<User,int>* Group::getMembers() {
    return &this->_members;
}

void Group::watch(Genre genre) {
    ++_group_views_parameter[(int)genre];
    ++_group_views_parameter[(int)Genre::NONE];
    _total_views[(int)genre] += size();
    _total_views[(int)Genre::NONE] += size();
}

void Group::removeUser(const User& user) {
    if (user.vip())
        _vip--;
    _members.remove(user.id());
    for (int i = 0; i <= (int)Genre::NONE; ++i) {
        _total_views[i] -= user.views((Genre)i);
    }
}

