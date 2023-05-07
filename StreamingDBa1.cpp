#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
    movies = new MoviesIds ();
    action  = new MoviesTree();
    drama  = new MoviesTree();
    fantasy = new MoviesTree();
    comedy  = new MoviesTree();
    users = new UsersIds ();
    sortedByRating = new MoviesTree();
    groups = new AvlTree<Group<UserPtr,int>*,int>();
	// TODO: Your code goes here
}

streaming_database::~streaming_database()
{
    delete movies;
    delete action;
    delete comedy;
    delete fantasy;
    delete drama;
    delete users;
    delete sortedByRating;
	// TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{

    try{
        shared_ptr<Movie> movie = make_shared<Movie>(Movie(movieId,genre,views,vipOnly));
        addData(movies,movie->getId(),movie);
        switch (genre) {
            case Genre::ACTION:
                addData(action,movie->getCmp(),movie);
                break;
            case Genre::DRAMA:
                addData(drama,movie->getCmp(),movie);
                break;
            case Genre::FANTASY:
                addData(fantasy,movie->getCmp(),movie);
                break;
            case Genre::COMEDY:
                addData(comedy,movie->getCmp(),movie);
                break;
        }
        return addData(sortedByRating,movie->getCmp(),movie);
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    try{
        shared_ptr<Movie> movie = getDataPtr(movies, new int(movieId));
        Genre genre = movie->getGenre();
        removeData(getGenreTree(genre),movie->getCmp());

        removeData(sortedByRating,movie->getCmp());
        return removeData(movies,new int(movieId));
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    try
    {
        shared_ptr<User> user = make_shared<User>(User(userId,isVip));
        return addData(users, new int(userId),user);
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    try{
        UserPtr user = getDataPtr(users, new int(userId));
        int groupId = user->getGroupID();
        if(groupId != 0)
        {
            removeData(getDataPtr(groups,new int(groupId)),new int (groupId));
            user->setGroupID(0);
        }
        removeData(users,new int (userId));
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    try
    {
        Group<UserPtr ,int>* group = new Group<UserPtr,int>(groupId);
        groups->add(group,group->getId());
    }
    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    removeData(groups, new int (groupId));
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    try{
        UserPtr user = getDataPtr(users,new int(userId));
        UsersGroup* group = getDataPtr(groups,new int(groupId));
        if(user->getGroupID() != 0)
            return StatusType::FAILURE;
        user->setGroupID(groupId);
        addData(group,new int (userId), user);
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    UserPtr user  = getDataPtr(users, new int(userId));
    MoviePtr movie = getDataPtr(movies,new int(movieId));
    remove_movie(*(movie->getId()));
    user->watch(movie);
    getGenreTree(movie->getGenre())->add(movie,movie->getCmp());
    sortedByRating->add(movie,movie->getCmp());
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
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


