
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
private:
    int _id;
    Genre _genre;
    int _views;
    bool _vip;
    int _tot_points;
    int _number_of_ratings;
};
