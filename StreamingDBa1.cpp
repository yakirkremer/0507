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
    groups = new Groups();//new AvlTree<Group<UserPtr,int>*,int>();
	// TODO: Your code goes here
}

streaming_database::~streaming_database()
{
    delete movies;
    delete action;
    delete comedy;
    delete fantasy;
    delete drama;
    delete groups;
    delete users;
    delete sortedByRating;
	// TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{

    try{
        //if(views < 0 || genre == Genre::NONE || !validId(movieId))
            //return StatusType::INVALID_INPUT;
        //if(movieExist(movieId))
            //return StatusType::FAILURE;
        //Movie tmp =   Movie(movieId,genre,views,vipOnly);
        MoviePtr movie = make_shared<Movie>(Movie(movieId,genre,views,vipOnly));
        addData(movies,movie->getId(),movie);
        addMovieToSorted(movie);
        return StatusType::SUCCESS;

    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }

    catch (alreadyExists){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
    catch (NotValidGenre){
        return StatusType::INVALID_INPUT;
    }
}

StatusType streaming_database::remove_movie(int movieId)
{
    try{
        //if(!validId(movieId))
            //return StatusType::INVALID_INPUT;
       // if(!movieExist(movieId))
           // return StatusType::FAILURE;
        shared_ptr<Movie> movie = getDataPtr(movies,  (movieId));
        removeMovieFromSorted(movie);
        removeData(movies, (movieId));
        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NoNodeExist){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

}

StatusType streaming_database::add_user(int userId, bool isVip)
{

    try
    {
        //if(!validId(userId))
           // return StatusType::INVALID_INPUT;
        //if(userExist(userId))
          //  return StatusType::FAILURE;
        UserPtr user = make_shared<User>(User(userId,isVip));
        addData(users,  (userId),user);
        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }

    catch (alreadyExists){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }

}

StatusType streaming_database::remove_user(int userId)
{
    try{
       // if(!validId(userId))
          //  return StatusType::INVALID_INPUT;
        //if(!userExist(userId))
           // return StatusType::FAILURE;
        UserPtr user = getDataPtr(users,  (userId));
        if(user->getGroupID() != 0)
        {
            UsersGroup* group = getDataPtr(groups,  (user->getGroupID()));
            group->updateViews(user);
            group->removeUserViews(user->getActionViews(),user->getComedyViews(),user->getDramaViews(),user->getFantasyViews());
            removeData(group,  (userId));
            user->setGroup(0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
            if(user->isVip()) {
                group->removeVip();
                group->updateVip();
            }
            group->removeUserViews(user->getActionViews(),user->getComedyViews(),user->getDramaViews(),user->getFantasyViews());

        }
        removeData(users,  (userId));
        return StatusType::SUCCESS;
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch (NoNodeExist){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
}

StatusType streaming_database::add_group(int groupId)
{
    try
    {
        //if(!validId(groupId))
            //return StatusType::INVALID_INPUT;
       // if(groupExist(groupId))
           // return StatusType::FAILURE;
        UsersGroup* group = new UsersGroup(groupId);
        groups->add(group,group->getId());
    }
    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (alreadyExists){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    try
    {
        //if (!validId(groupId))
          //  return StatusType::INVALID_INPUT;
       // if (!groupExist(groupId))
           // return StatusType::FAILURE;
        UsersGroup *group = getDataPtr(groups,   (groupId));
        group->updateViewsForAll();
        removeData(groups,  (groupId));
        // TODO: Your code goes here
        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NoNodeExist){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    try{
        //if(!validId(userId)|| !validId(groupId))
          //  return StatusType::INVALID_INPUT;
        //if(!userExist(userId) || !groupExist(groupId))
            //return StatusType::FAILURE;
        UserPtr user = getDataPtr(users, (userId));
        UsersGroup* group = getDataPtr(groups, (groupId));
        group->updateViewsForAll();
       // if(user->getGroupID() != 0)
            //return StatusType::FAILURE;
        user->setGroup(groupId,group->getViewsPtr(Genre::ACTION),group->getViewsPtr(Genre::COMEDY)
                       ,group->getViewsPtr(Genre::DRAMA),group->getViewsPtr(Genre::FANTASY)
                ,group->getTmpPtr(Genre::ACTION),group->getTmpPtr(Genre::COMEDY)
                ,group->getTmpPtr(Genre::DRAMA),group->getTmpPtr(Genre::FANTASY));
        addData(group,  (userId), user);
        group->addViewsFromNewUser(user->getActionViews(),user->getComedyViews(),user->getDramaViews(),user->getFantasyViews());
        if(user->isVip())
        {
            group->addVip();
            group->updateVip();
        }
        return StatusType::SUCCESS;

    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NoNodeExist){
        return StatusType::FAILURE;
    }

    catch(alreadyExists)
    {
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    try
    {
        //if(!validId(userId) || !validId(movieId))
           // return StatusType::INVALID_INPUT;
       // if(userExist(userId) && movieExist(movieId ))
        //{

            UserPtr user = getDataPtr(users,  (userId));
            MoviePtr movie = getDataPtr(movies,  (movieId));
            //if(movie->isVip() != true || user->isVip()== movie->isVip()) {
                removeMovieFromSorted(movie);
                user->watch(movie);
                addMovieToSorted(movie);
            //}
            // TODO: Your code goes here
       // }
            //return StatusType::FAILURE;

    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NoNodeExist){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
    catch(NotVip)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;


}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    try
    {
        //if(!validId(groupId) || !validId(movieId))
           // return StatusType::INVALID_INPUT;
        //if(groupExist(groupId) && movieExist(movieId ))
       // {
            UsersGroup * group = getDataPtr(groups,  (groupId));
            MoviePtr movie = getDataPtr(movies,(movieId));
            //if(movie->isVip() != true || group->vip()== movie->isVip()) {
                group->watch(movie);
                return StatusType::SUCCESS;
            //}
        //}
        //return StatusType::FAILURE;
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NoNodeExist){
        return StatusType::FAILURE;
    }

    catch (NotValidId){
        return StatusType::INVALID_INPUT;
    }
    catch(NotVip)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    try
    {
        if(genre== Genre::NONE)
            return movies->getSize();

        return getGenreTree(genre)->getSize();
    }

    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(output == nullptr)
        return StatusType::FAILURE;
    try
    {
        int size = getGenreTree(genre)->getSize();
        MoviePtr *movies = new MoviePtr[size];
        getGenreTree(genre)->putDataInOrder(movies);
        for (int i = 0; i < size; ++i) {
            output[i] = ((movies[i])->getId());
        }
        // TODO: Your code goes here
        //output[0] = 4001;
       // output[1] = 4002;
        //delete [] movies;
        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc){
        return StatusType::ALLOCATION_ERROR;
    }

    catch(EmptyTree){
        return StatusType::FAILURE;
    }

    catch(...){
        return StatusType::FAILURE;
    }
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    try
    {
        //if (!validId(userId))
           // return StatusType::INVALID_INPUT;
      //  if (!userExist(userId))
          //  return StatusType::FAILURE;
        UserPtr user = getDataPtr(users,  (userId));
        return user->getViews(genre);
    }
    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    catch(NoNodeExist){
        return StatusType::FAILURE;
    }
    catch(NotValidId){
        return StatusType::INVALID_INPUT;
    }

	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    //if(!validId(userId)|| !validId(movieId)|| rating<0 || rating >100)
        //return StatusType::INVALID_INPUT;
    try
    {
        //if(userExist(userId)&& movieExist(movieId))
        //{
            MoviePtr movie = getDataPtr(movies,  (movieId));
            UserPtr user = getDataPtr(users,  (userId));
            //if (movie->isVip() == user->isVip() || !movie->isVip()) {
                movies->remove((movie->getId()));
                getGenreTree(movie->getGenre())->remove(movie->getCmp());
                user->rateMovie(movie, rating);
                movies->add(movie, movie->getId());
                getGenreTree(movie->getGenre())->add(movie, movie->getCmp());
                return StatusType::SUCCESS;
           // }
        //}
        //return StatusType::FAILURE;
    }

    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
        catch(NoNodeExist){
                return StatusType::FAILURE;
        }
        catch(NotValidId){
                return StatusType::INVALID_INPUT;
        }
        catch(NotValidRating){
            return StatusType::INVALID_INPUT;
        }

    // TODO: Your code goes here
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    try{
        //if(!validId(groupId))
            //return StatusType::INVALID_INPUT;
        //if(!groupExist(groupId))
           // return StatusType::FAILURE;
        UsersGroup* group = getDataPtr(groups, (groupId));
        //if(getGenreTree(group->getFavGenre())->getSize() == 0 || group->getSize() == 0)
           // return StatusType::FAILURE;
        return (getMostRated(group->getFavGenre()))->getId();
    }
    catch (std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NoNodeExist){
        return StatusType::FAILURE;
    }
    catch(NotValidId){
        return StatusType::INVALID_INPUT;
    }
}


