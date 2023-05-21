
#include "Movie.h"

Movie::Movie(int movieId, Genre genre, int views, bool vipOnly):
    _id(movieId),
    _genre(genre),
    _views(views),
    _vip(vipOnly),
    _tot_points(0),
    _number_of_ratings(0) {}

int Movie::id() const {
    return _id;
}

bool Movie::vip() const {
    return _vip;
}

Genre Movie::genre() const {
    return _genre;
}

bool Movie::watch(User& user) {
    if (vip() && !user.vip()) {
        return false;
    }
    user.watch(_genre);
    ++_views;
    return true;
}

bool Movie::watch(Group& group) {
    if (group.size() == 0 || (vip() && !group.vip())) {
        return false;
    }
    _views += group.size();
    return true;
}

void Movie::addNumberRatings() {
    this->_number_of_ratings++;
}

void Movie::addTotalPoints(int points) {
    this->_tot_points = _tot_points + points;
}

bool Movie::operator>(const Movie& other) const {
    return this->_id > other._id;
}

bool Movie::operator==(const Movie& other) const {
    return this->_id == other._id;
}

bool Movie::operator!=(const Movie& other) const {
    return !(*this == other);
}

bool Movie::operator>=(const Movie& other) const {
    return *this > other && *this == other;
}

bool Movie::operator<(const Movie& other) const {
    return other > *this;
}

bool Movie::operator<=(const Movie& other) const {
    return other >= *this;
}



// bool Movie::operator>(const Movie& movie)const{
//    if (playersAbility > key.getPlayersAbility()){
//        return true;
//    } else if(playersAbility < key.getPlayersAbility()){
//        return false;
//    }
//    return teamId > key.getID();
// }