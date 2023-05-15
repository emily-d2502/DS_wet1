
#include "wet1util.h"

class Movie {
public:
    Movie(int movieId, Genre genre, int views, bool vipOnly) :
        _id(movieId),
        _genre(genre),
        _views(views),
        _vip(vipOnly),
        _tot_points(0),
        _number_of_ratings(0) {}

    Movie(const Movie& other) = delete;
    Movie& operator=(const Movie& other) = delete;
    ~Movie() = default;

    bool operator>(const Movie& movie) const;

    int getGenre() const;
    int getVIP() const;
    int getID() const;


    void Movie::addTotalPoints(int points);
    void Movie::addNumberRatings();

private:
    int _id;
    Genre _genre;
    int _views;
    bool _vip;
    int _tot_points;
    int _number_of_ratings;
};

int Movie::getGenre() const {
    return this->_genre;
}

int Movie::getVIP() const {
    return this->_vip;
}

int Movie::getID() const {
    return this->_id;
}

void Movie::addTotalPoints(int points) {
    this->_tot_points = _tot_points + points;
}

void Movie::addNumberRatings() {
    this->_number_of_ratings++;
}

bool Movie::operator>(const Movie& movie)const{
//    if (playersAbility > key.getPlayersAbility()){
//        return true;
//    } else if(playersAbility < key.getPlayersAbility()){
//        return false;
//    }
//    return teamId > key.getID();
}