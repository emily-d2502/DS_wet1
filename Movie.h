
#include "wet1util.h"

class Movie {
public:
    Movie();
    Movie(const AVL& other) = delete;
    Movie& operator=(const AVL& other) = delete;
    ~Movie();
private:
    int _id;
    int _tot_points;
    bool _number_of_ratings;
};
