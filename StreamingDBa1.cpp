#include "StreamingDBa1.h"
#include <new>

using namespace std;

#if defined(DBUG)
#define FUNC_ENTRY()  \
  func_entry_c __func(__PRETTY_FUNCTION__);
#else
#define FUNC_ENTRY()
#endif

class func_entry_c {
    const char* _func;
public:
    func_entry_c(const char* func): _func(func) {
        cerr << _func << " --> " << endl;
    }
    ~func_entry_c() {
        cerr << _func << " <-- " << endl;
    }
};

streaming_database::streaming_database() :
_users_id_tree(),
_groups_id_tree(),
_movies_id_tree(),
_movies_genre_trees() {}

streaming_database::~streaming_database()
{
    _users_id_tree.deleteTreeData();
    _movies_id_tree.deleteTreeData();
    _groups_id_tree.deleteTreeData();
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
	if ((int)genre == 4 || movieId <= 0 || views < 0) {
        return StatusType::INVALID_INPUT;
	}

    try {
        Movie *movie = new Movie(movieId, genre, views, vipOnly);
    	_movies_id_tree.insert(movieId, movie);
		_movies_genre_trees[(int)genre].insert(*movie, movie);
		_movies_genre_trees[(int)Genre::NONE].insert(*movie, movie);
    } catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<Movie, Movie>::KeyExists& e) {
        return StatusType::FAILURE;
    } catch (const AVL<Movie, int>::KeyExists& e) {
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
	if (movieId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
		Movie& movie = _movies_id_tree.find(movieId);
		_movies_genre_trees[(int)movie.genre()].remove(movie);
		_movies_genre_trees[(int)Genre::NONE].remove(movie);
		_movies_id_tree.remove(movieId);

	} catch (const AVL<Movie>::KeyNotFound& e) {
        return StatusType::FAILURE;
    } catch (const AVL<Movie, int>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if (userId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
		User *user = new User(userId, isVip);
		_users_id_tree.insert(userId, user);
	} catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<User, int>::KeyExists& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	if (userId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
        User& user = _users_id_tree.find(userId);
        if (user.getGroup()) {
            user.getGroup()->removeUser(user);
        }
        _users_id_tree.remove(userId);
	} catch (const AVL<User, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
	if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
		Group *group = new Group();
		_groups_id_tree.insert(groupId, group);
	} catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    } catch (const AVL<Movie, int>::KeyExists& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
	}
	try {
		_groups_id_tree.remove(groupId);
        //
        Group& group = _groups_id_tree.find(groupId);
        AVL<User,int>* Tree = group.getMembers();
        User **tmp = new User*[Tree->size()];
        Tree->inorder(tmp);
        for (int i = 0; i < Tree->size(); ++i) {
            tmp[i]->remove_from_group(&group);
        }
        //

	} catch (const AVL<Movie, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	if (userId <= 0 || groupId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
		Group& group = _groups_id_tree.find(groupId);
		User& user = _users_id_tree.find(userId);
        if (user.getGroup() != nullptr) {
            return StatusType::FAILURE;
        }
		group.add_member(userId, &user);
	} catch (const AVL<Group, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	} catch (const AVL<User, int>::KeyNotFound& e) {
    		return StatusType::FAILURE;
	}
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	if (userId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
		Movie& movie = _movies_id_tree.find(movieId);
		User& user = _users_id_tree.find(userId);

		if (!movie.watch(user)) {
			return StatusType::FAILURE;
		}
	} catch (const AVL<User, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	} catch (const AVL<Movie, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	}
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	if (groupId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
	}

	try {
		Movie& movie = _movies_id_tree.find(movieId);
		Group& group = _groups_id_tree.find(groupId);

		if (!movie.watch(group)) {
			return StatusType::FAILURE;
		}
	} catch (const AVL<Movie, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	} catch (const AVL<Group, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    return _movies_genre_trees[(int)genre].size();
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if (output == nullptr) {
        return StatusType::INVALID_INPUT;
	}

	try {
		int size = _movies_genre_trees[(int)genre].size();
		if (size == 0) {
			return StatusType::FAILURE;
		}
		Movie **tmp = new Movie*[size];
		_movies_genre_trees[(int)genre].inorder(tmp);
		for (int i = 0; i < size; ++i) {
			output[i] = tmp[i]->id();
		}
		delete[] tmp;

	} catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	if (userId <= 0) {
        return StatusType::INVALID_INPUT;
	}
	try {
		User& user = _users_id_tree.find(userId);
		return user.views(genre);
	} catch (const AVL<User, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	}
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <= 0 || 0 > rating || rating > 100) {
        return StatusType::INVALID_INPUT;
	}
    try {
        Movie& movie = _movies_id_tree.find(movieId);
        User& user = _users_id_tree.find(userId);

		if (movie.vip() && !user.vip()) {
			return StatusType::FAILURE;
		}
		_movies_genre_trees[(int)movie.genre()].remove(movie);
		_movies_genre_trees[(int)Genre::NONE].remove(movie);

		movie.addNumberRatings();
        movie.addTotalPoints(rating);

		_movies_genre_trees[(int)Genre::NONE].insert(movie, &movie);
		_movies_genre_trees[(int)movie.genre()].insert(movie, &movie);

    } catch (const AVL<User, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
	} catch (const AVL<Movie, int>::KeyNotFound& e) {
		return StatusType::FAILURE;
    } catch (const AVL<Movie, Movie>::KeyNotFound& e) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
	}
     try {
	 	Group& group = _groups_id_tree.find(groupId);
	 	if (group.size() == 0) {
	 		return StatusType::FAILURE;
	 	}
         int maxGenre = group.getMaxViews();
         if (_movies_genre_trees[maxGenre].size() == 0) {
             return StatusType::FAILURE;
	 	}
         return _movies_genre_trees[maxGenre].max().id();
     } catch (const AVL<Group, int>::KeyNotFound& e) {
     	return StatusType::FAILURE;
     }
}


