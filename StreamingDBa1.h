// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "Movies.h"
#include "Group.h"




typedef Movies MoviesTree;
typedef MoviesByInt MoviesIds;
typedef  UsersByInt UsersIds;
//typedef IntKeyAVlTree<UsersGroupPtr> Groups;
class streaming_database {
private:
	//
	// Here you may add anything you want
	//

    MoviesIds * movies;
    UsersIds * users;
    MoviesTree * action;
    MoviesTree * drama;
    MoviesTree * fantasy;
    MoviesTree * comedy;
    MoviesTree * sortedByRating;
    Groups* groups;
    MoviePtr mostRatedAction;
    MoviePtr mostRatedComedy;
    MoviePtr mostRatedDrama;
    MoviePtr mostRatedFantasy;

    MoviePtr& getMostRated(Genre genre){
        if(getGenreTree(genre)->getSize() <= 0)
            throw NoNodeExist();
        switch (genre) {
            case Genre::ACTION:
                return mostRatedAction;
            case Genre::DRAMA:
                return mostRatedDrama;
            case Genre::FANTASY:
                return mostRatedFantasy;
            case Genre::COMEDY:
                return mostRatedComedy;
        }
    }

    void addMovieToSorted(Movie* movie){
        getGenreTree(movie->getGenre())->add(make_shared<Movie>(*movie));
        if(getMostRated(movie->getGenre()) == nullptr){
            getMostRated(movie->getGenre()) = make_shared<Movie>(*movie);
        }
        sortedByRating->add(make_shared<Movie>(*movie));
        getMostRated(movie->getGenre()) = getGenreTree(movie->getGenre())->updateHighest();
    }
    void removeMovieFromSorted(Movie* movie){
        getGenreTree(movie->getGenre())->remove( movie->getCmp());
        sortedByRating->remove(movie->getCmp());
    }

    //template<class type, class cmp>
    /*type& getDataPtr(AvlTreeNew<type,cmp>* tree, cmp key){
        try
        {
            type res = tree->getData(key);
            return res;
        }
        catch (NoNodeExist){
            throw NoNodeExist();
        }
    }
*/
    Movie* getMoviePtr(int key){
        return movies->getData(key);
    }


    Movie* getMoviePtr(MoviesTree* moviesTree ,MovieComperator key){
        return moviesTree->getData(key);
    }
    User* getUserPtr(UsersByInt* usersByInt ,int key){
        return usersByInt->getData(key);
    }
    User* getUserPtr(UsersGroup* usersByInt ,int key){
        return usersByInt->getData(key);
    }
    UsersGroup* getGroupPtr(int key){
        return groups->getData(key);
    }

    template<class type, class treePtr>
    StatusType addData(treePtr tree, type* val){
        tree->add(make_shared<type>(*val));
        return StatusType::SUCCESS;
    }

    template<class type, class treePtr>
    StatusType addData(treePtr tree, shared_ptr<type> val){
        tree->add(val);
        return StatusType::SUCCESS;
    }

    template<class treePtr, class cmp>
    StatusType removeData(treePtr tree, cmp key){
        tree->remove(key);
        return StatusType::SUCCESS;
    }

    MoviesTree* getGenreTree(Genre genre){
        switch (genre) {
            case Genre::ACTION:
                return action;
            case Genre::DRAMA:
                return drama;
            case Genre::FANTASY:
                return fantasy;
            case Genre::COMEDY:
                return comedy;
            case Genre::NONE:
                return sortedByRating;
        }
    }

public:

	// <DO-NOT-MODIFY> {

	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);
	
	// } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
