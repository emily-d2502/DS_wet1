
#include "wet1util.h"

class Group {
public:
    Group();
    Group(const AVL& other) = delete;
    Group& operator=(const AVL& other) = delete;
    ~Group();
private:
    int _id;
    *User _members[];
    int _total_views[5];
    int _views_parameter[5];
};
