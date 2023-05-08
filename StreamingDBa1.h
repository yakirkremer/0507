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
//#include "Movie.h"
//#include "User.h"
#include "Movies.h"
#include "Group.h"




typedef Movies MoviesTree;//typedef  AvlTree<shared_ptr<Movie>,MovieComperator> MoviesTree;
typedef MoviesByInt MoviesIds;//typedef  AvlTree<shared_ptr<Movie>,int> MoviesIds;
typedef  AvlTreeNew<shared_ptr<User>,UserComperator> UsersTree;
typedef  UsersByInt UsersIds;//AvlTree<shared_ptr<User>,int> UsersIds;


//typedef  Group<UserPtr,int> UsersGroup;

//typedef  AvlTree<shared_ptr<User>,int> Group;
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


    bool validId(int Id){
        if(Id<=0)
            return false;
        return true;
    }



    bool movieExist(int movieId){
        //if(movies->nodeExist(new int(movieId)))
        if(movies->nodeExist(movieId))
            return true;
        return false;
    }

    bool userExist(int userId){
        if(users->nodeExist((userId)))
            return true;
        return false;
    }

    bool groupExist(int groupId){
        if(groups->nodeExist( (groupId)))
            return true;
        return false;
    }

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

    StatusType addMovieToSorted(MoviePtr movie){
        getGenreTree(movie->getGenre())->add(movie, movie->getCmp());
        if(getMostRated(movie->getGenre()) == nullptr){
            getMostRated(movie->getGenre()) = movie;
        }
        sortedByRating->add(movie, movie->getCmp());
        getMostRated(movie->getGenre()) = getGenreTree(movie->getGenre())->updateHighest();

    }
    StatusType removeMovieFromSorted(MoviePtr movie){
        getGenreTree(movie->getGenre())->remove( movie->getCmp());
        sortedByRating->remove(movie->getCmp());
    }


    template<class t, class c>
    t getDataPtr(AvlTreeNew<t,c>* tree, c key){
        t res = tree->getData(key);
        return res;
    }
/*
    MoviePtr getDataPtr(MoviesByInt* tree, int key){
        MoviePtr res = tree->getData(key);
        return res;
    }

    MoviePtr getDataPtr(Movies* tree, MovieComperator key){
        MoviePtr res = tree->getData(key);
        return res;
    }

    UserPtr getDataPtr(UsersByInt* tree, int key){
        UserPtr res = tree->getData(key);
        return res;
    }
    UsersGroup* getDataPtr(AvlTreeNew<UsersGroup*,int>* tree, int key){
        UsersGroup* res = tree->getData(key);
        return res;
    }
*/


    template<class type, class cmp, class avl>
    StatusType addData(avl* tree, cmp key, type val){
        tree->add(val,key);
        return StatusType::SUCCESS;
    }

    template<class type, class cmp>
    StatusType removeData(AvlTreeNew<type, cmp>* tree, cmp key){


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
    void printGroups(){
        groups->postorder(groups->getHead(),2);
    }

    void printMovies(){
        sortedByRating->postorder(sortedByRating->getHead(),2);
    }


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
