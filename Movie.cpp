
#include "Movie.h"

Movie::Movie(int movieId, Genre genre, int views, bool vipOnly):
    _id(movieId),
    _vip(vipOnly),
    _views(views),
    _genre(genre),
    _tot_points(0),
    _number_of_ratings(0),
    _rating(0){}


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
    group.watch(_genre);
    _views += group.size();
    return true;
}

void Movie::addNumberRatings() {
    this->_number_of_ratings++;
}

void Movie::addTotalPoints(int points) {
    this->_tot_points = _tot_points + points;
}

void Movie::updateRating() {
    this->_rating = _tot_points/_number_of_ratings;
}


bool Movie::operator>(const Movie& other) const {
    if ((this->_tot_points * other._number_of_ratings) == (other._tot_points * this->_number_of_ratings) && (this->_number_of_ratings != 0) && (other._number_of_ratings !=0) )
    if (this->_rating > other._rating)
        return true;
    else if (this->_rating < other._rating)
        return false;
    else if (this->_views > other._views)
        return true;
    else if (this->_views < other._views)
        return false;
    return this->_id < other._id;

//
//    if ((this->_number_of_ratings == 0) && (other._number_of_ratings > 0))
//        return (other._tot_points/other._number_of_ratings)>0;
//    if ((this->_number_of_ratings > 0) && (other._number_of_ratings == 0))
//        return (this->_tot_points/this->_number_of_ratings)>0;
//
//    if ((this->_tot_points * other._number_of_ratings) > (other._tot_points * this->_number_of_ratings))
//        return true;
//    if ((this->_views > other._views) && (this->_tot_points * other._number_of_ratings) == (other._tot_points * this->_number_of_ratings))
//        return true;
//    if ((this->_views == other._views) && (this->_tot_points * other._number_of_ratings) == (other._tot_points * this->_number_of_ratings))
//        return this->_id < other._id;
//    return false;

}

bool Movie::operator==(const Movie& other) const {
    if (this->_id == other._id)
        return true;
    return false;
}

bool Movie::operator<(const Movie& other) const {
    if (!(*this > other) && !(*this == other))
        return true;
    return false;
}

bool Movie::operator!=(const Movie& other) const {
    return !(*this == other);
}

bool Movie::operator>=(const Movie& other) const {
    return !(*this < other);
}

bool Movie::operator<=(const Movie& other) const {
    return !(*this > other);
}

