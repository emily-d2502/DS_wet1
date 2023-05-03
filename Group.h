
#include "wet1util.h"
#include "User.h"


class Group {
public:
    Group();
    Group(const Group& other) = delete;
    Group& operator=(const Group& other) = delete;
    ~Group();
private:
    int _id;
    User* _members[];
    int _total_views[5];
    int _views_parameter[5];
};
