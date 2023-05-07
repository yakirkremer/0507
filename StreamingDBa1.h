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
#include "Movie.h"
#include "User.h"
#include "Group.h"

typedef  AvlTree<shared_ptr<Movie>,MovieComperator> MoviesTree;
typedef  AvlTree<shared_ptr<Movie>,int> MoviesIds;
typedef  AvlTree<shared_ptr<User>,UserComperator> UsersTree;
typedef  AvlTree<shared_ptr<User>,int> UsersIds;
typedef shared_ptr<User> UserPtr;
typedef shared_ptr<Movie> MoviePtr;

typedef  Group<UserPtr,int> UsersGroup;

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
    AvlTree<Group<UserPtr,int>*,int>* groups;



    template<class type, class cmp>
    type getDataPtr(AvlTree<type, cmp>* tree, cmp* key){
        return tree->getData(key);
    }

    template<class type, class cmp>
    StatusType addData(AvlTree<type, cmp>* tree, cmp* key, type val){
        if(!(*key))
            return StatusType::INVALID_INPUT;
        if(tree->nodeExist(key))
            return StatusType::FAILURE;
        tree->add(val,key);
        return StatusType::SUCCESS;
    }

    template<class type, class cmp>
    StatusType removeData(AvlTree<type, cmp>* tree, cmp* key){
        if(!(*key))
            return StatusType::INVALID_INPUT;
        if(!tree->nodeExist(key))
            return StatusType::FAILURE;
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
