#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
	// TODO: Your code goes here
}

streaming_database::~streaming_database()
{
//    all_users_id_tree.deleteTreeData();
//    all_movies_id_tree.deleteTreeData();
// kill all groups and the trees inside them

}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if((static_cast<int>(genre) == 4) || movieId <= 0 || views < 0)
        return StatusType::INVALID_INPUT;
    try {
        all_movies_id_tree.find(movieId);
        return StatusType::FAILURE;
    } catch (const AVL<int,Movie>::KeyNotFound& e) {}

    try {
        auto *m = new Movie(movieId, genre, views, vipOnly); //////////
        all_movies_id_tree.insert(movieId,m);
        all_movies_rank_tree.insert(*m, m);
        genre_trees_array[static_cast<int>(genre)].insert(*m,m);
    }catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Movie* current = all_movies_id_tree.find(movieId);
        all_movies_id_tree.remove(movieId);
        all_movies_rank_tree.remove(current);
        genre_trees_array[current.getGenre()].remove(current);

    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<int,Movie>::KeyNotFound& e) {
        return StatusType::FAILURE;
    } catch (const AVL<Movie,Movie>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        all_users_id_tree.find(userId);
        return StatusType::FAILURE;
    } catch (const AVL<int,User>::KeyNotFound& e) {}

    try {
        auto *u = new User(userId, isVip); //////////
        all_users_id_tree.insert(userId,u);
    }catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        User* current = all_users_id_tree.find(userId);
        all_users_id_tree.remove(userId);
        if (current->getGroup() != nullptr)
        {
            Group * group = current->getGroup();
            group->removeUser(userId);
        }
    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<int,User>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        all_groups_id_tree.find(groupId);
        return StatusType::FAILURE;
    } catch (const AVL<int,User>::KeyNotFound& e) {}

    try {
        Group *u = new Group(groupId); //////////
        all_groups_id_tree.insert(groupId,u);
    }catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        all_groups_id_tree.find(groupId);
        all_groups_id_tree.remove(groupId);
    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<int,Group>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(groupId <= 0 || userId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Group * g = all_groups_id_tree.find(groupId);
        User * u = all_users_id_tree.find(userId);
        if (u->getGroup() != nullptr)
            return StatusType::FAILURE;
        g->addUser(userId, u);
    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<int,Group>::KeyNotFound& e) {
        return StatusType::FAILURE;
    } catch (const AVL<int,User>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(movieId <= 0 || userId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Movie * m = all_movies_id_tree.find(movieId);
        User * u = all_users_id_tree.find(userId);
        if (!(u->getVIP()) && m->getVIP())
            return StatusType::FAILURE;
    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<int,Group>::KeyNotFound& e) {
        return StatusType::FAILURE;
    } catch (const AVL<int,User>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	//easy just need to remember the manner in which we update the viewing data in group
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    if (static_cast<int>(genre) == 4)
        return all_movies_id_tree.getSize(); //right now we use map
    return genre_trees_array[static_cast<int>(genre)].getSize();
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if (output == NULL)
        return StatusType::INVALID_INPUT;
    int i = 0;
    if (static_cast<int>(genre) == 4){
        all_movies_rank_tree.inOrderSetUp(all_movies_rank_tree.getRoot(), output, &i);
    }
    genre_trees_array->inOrderSetUp(genre_trees_array[static_cast<int>(genre)].getRoot(), output, &i);
    if (output == NULL)
        return StatusType::FAILURE;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    //easy just need to remember the manner in which we update the viewing data in group
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <= 0 || rating < 0 || rating >100)
        return StatusType::INVALID_INPUT;
    try {
        User* u = all_users_id_tree.find(userId);
        Movie* m = all_movies_id_tree.find(userId);
        if (m->getVIP() && !(u->getVIP()))
            return StatusType::FAILURE;

        all_movies_rank_tree.remove(m);
        genre_trees_array[m.getGenre()].remove(m);

        m->addNumberRatings();
        m->addTotalPoints(rating);

        all_movies_rank_tree.insert(m->getID(),m);
        genre_trees_array[m->getGenre()].insert(m);

    } catch (const AVL<int,Movie>::KeyNotFound& e) {
    return StatusType::FAILURE;
    } catch (const AVL<int,User>::KeyNotFound& e) {
    return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId) {

    if (groupId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Group* g = all_groups_id_tree.find(groupId);
        if (g.getSize() == 0)
            return StatusType::FAILURE;


        int genre = 0;
        int *array = g.getTotalViews();

        for (int i = 0; i < 4; i++) {
            if (array[i] > genre)
                genre = array[i];
        }

        if (genre_trees_array[genre].getSize() == 0)
            return StatusType::FAILURE;

        return genre_trees_array[genre]->getMax()->getID();
    } catch (const AVL<int,Group>:: KeyNotFound& e) {  //the exception caught is defined in AVL and currently we use MAP, to solve
    return StatusType::FAILURE;
    }
}



