
#include "wet1util.h"

class Movie {
public:
    Movie();
    Movie(const Movie& other) = delete;
    Movie& operator=(const Movie& other) = delete;
    ~Movie();
private:
    int _id;
    int _tot_points;
    bool _number_of_ratings;
};
