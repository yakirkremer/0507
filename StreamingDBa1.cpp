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
    groups = new Groups();
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

}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{

    try{
        MoviePtr movie = make_shared<Movie>(Movie(movieId,genre,views,vipOnly));
        addData(movies,movie);
        addMovieToSorted(movie.get());
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
        Movie* movie = getMoviePtr(  (movieId));
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
        UserPtr user = make_shared<User>(User(userId,isVip));
        addData(users,user);
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
        User* user = getUserPtr(users,  (userId));
        if(user->getGroupID() != 0)
        {
            UsersGroup* group = getGroupPtr(  (user->getGroupID()));
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
        
        UsersGroupPtr group = make_shared<UsersGroup>(UsersGroup(groupId));
        groups->add(group);
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
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    try
    {
        UsersGroup* group = getGroupPtr(   (groupId));
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

        User* user = getUserPtr(users,(userId));
        UsersGroup* group = getGroupPtr( (groupId));
        group->updateViewsForAll();
        user->setGroup(groupId,group->getViewsPtr(Genre::ACTION),group->getViewsPtr(Genre::COMEDY)
                       ,group->getViewsPtr(Genre::DRAMA),group->getViewsPtr(Genre::FANTASY)
                ,group->getTmpPtr(Genre::ACTION),group->getTmpPtr(Genre::COMEDY)
                ,group->getTmpPtr(Genre::DRAMA),group->getTmpPtr(Genre::FANTASY));
        addData(group, user);
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
            User* user = getUserPtr(users,  (userId));
            Movie* movie = getMoviePtr( (movieId));

                removeMovieFromSorted(movie);
                user->watch(movie);
                addMovieToSorted(movie);
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

            UsersGroup* group = getGroupPtr( (groupId));
            Movie* movie = getMoviePtr((movieId));

            removeMovieFromSorted(movie);
            group->watch(movie);
            addMovieToSorted(movie);
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
        MoviePtr *moviesPtrs = new MoviePtr[size];
        getGenreTree(genre)->putDataInOrder(moviesPtrs);
        for (int i = 0; i < size; ++i) {
            output[i] = ((moviesPtrs[i])->getId());
        }
        delete [] moviesPtrs;
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
        User* user = getUserPtr(users,  (userId));
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
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    try
    {
                Movie* movie = getMoviePtr((movieId));
                User* user = getUserPtr(users,  (userId));
                removeMovieFromSorted(movie);

                //movies->remove((movie->getId()));
                //getGenreTree(movie->getGenre())->remove(movie->getCmp());
                user->rateMovie(movie, rating);
                //movies->add(movie);
                //getGenreTree(movie->getGenre())->add(movie);
                addMovieToSorted(movie);
                return StatusType::SUCCESS;

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

}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    try{
        UsersGroup* group = getGroupPtr( (groupId));
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


