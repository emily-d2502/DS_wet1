

#ifndef MOVIE_H_
#define MOVIE_H_

#include "wet1util.h"
#include "User.h"
#include "Group.h"

class Movie {
public:
    Movie(int movieId, Genre genre, int views, bool vipOnly);
    Movie()                              = default;
    Movie(const Movie& other)            = default;
    Movie& operator=(const Movie& other) = default;
    ~Movie()                             = default;

    bool watch(User& user);
    bool watch(Group& group);
    int id() const;
    bool vip() const;
    Genre genre() const;
    void addNumberRatings();
    void addTotalPoints(int points);
    void updateRating();

    bool operator>(const Movie& other) const;
    bool operator>=(const Movie& other) const;
    bool operator==(const Movie& other) const;
    bool operator!=(const Movie& other) const;
    bool operator<=(const Movie& other) const;
    bool operator<(const Movie& other) const;

private:
    int _id;
    bool _vip;
    int _views;
    Genre _genre;
    int _tot_points;
    int _number_of_ratings;
    double _rating;
};

#endif