#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
	// TODO: Your code goes here
}

streaming_database::~streaming_database()
{
	// TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(genre == 4 || movieId <= 0 || views<0)
        return StatusType::INVALID_INPUT;
    try {
        Movie * m = new Movie(movieId, genre, views, vipOnly);
        all_movies_id_tree.insert(std::pair<int, Movie*>(movieId,m));
        all_movies_rank_tree.insert(std::pair<Movie, Movie*>(*m,m));
        genre_trees_array[genre].insert(std::pair<Movie, Movie*>(*m,m));
        all_movie_counter++;
        per_genre_counter[genre]++;
    }catch (const std::exception& e){
        return StatusType::ALLOCATION_ERROR;
    } catch (const KeyNotFound& e) {  //the exception caught is defined in AVL and currently we use MAP, to solve
        delete m;
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Movie * current = all_movies_id_tree.find(movieId));
//        all_movies_id_tree.remove(movieId);
//        all_movies_rank_tree.remove(m);
//        genre_trees_array[current->getGenre()].remove(m);
//        We should talk about the data parameter in teh AVL tree
        all_movie_counter--;
        per_genre_counter[current->getGenre()]--;

    } catch (const std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const KeyNotFound& e) { //the exception caught is defined in AVL and currently we use MAP, to solve
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    if (genre == 4)
        return all_movies_id_tree.getSize(); //right now we use map
    return genre_trees_array[genre].getSize();
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if (output == NULL)
        return StatusType::INVALID_INPUT;
    int i = 0;
    if (genre == 4){
        inOrderSetUp(all_movies_rank_tree->_root, output, &i);
    }
    inOrderSetUp(genre_trees_array[genre]->_root, output, &i);
    if (output == NULL)
        return StatusType::FAILURE;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <= 0 || rating < 0 || rating >100)
        return StatusType::INVALID_INPUT;
    try {
        User u = all_users_id_tree.find(userId);
        Movie m = all_movies_id_tree.find(userId);
        if (m.getVIP() && !(u.getVIP()))
            return StatusType::FAILURE;

        all_movies_rank_tree.remove(m);
        genre_trees_array[current->getGenre()].remove(m);

        m.addNumberRatings();
        m.addTotalPoints(rating);

        all_movies_rank_tree.insert(std::pair<Movie, Movie*>(*m,m));
        genre_trees_array[m->getGenre()].insert(std::pair<Movie, Movie*>(*m,m));

    } catch (const KeyNotFound& e)   //the exception caught is defined in AVL and currently we use MAP, to solve
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{

    if (groupId <= 0)
        return StatusType::INVALID_INPUT;
    try {
        Group g = all_groups_id_tree.find(groupId);
        if(g.getSize() == 0)
            return StatusType::FAILURE;


        int genre = 0;
        int* array = g.getTotalViews();

        for(int i = 0; i<4; i++){
            if (array[i]> genre)
                genre = array[i];
        }

        if (genre_trees_array[genre].getSize() == 0)
            return StatusType::FAILURE;

        return genre_trees_array[genre].getMax();
    } catch (const KeyNotFound& e)   //the exception caught is defined in AVL and currently we use MAP, to solve
    return StatusType::FAILURE;
    }



}


