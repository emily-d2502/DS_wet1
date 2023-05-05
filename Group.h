
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
    int _vip;
    User* _members[];
    int _total_views[4];
    int _group_views_parameter[4];
};
