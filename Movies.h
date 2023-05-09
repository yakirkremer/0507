//
// Created by yakir on 5/8/2023.
//

#ifndef __1_MOVIES_H
#define __1_MOVIES_H
//#include "AvlTree.h"
#include "AvlTreeNew.h"
#include "Movie.h"
#include "User.h"

typedef shared_ptr<User> UserPtr;
typedef shared_ptr<Movie> MoviePtr;

/*
template<class type>
class IntKeyAVlTree:public AvlTreeNew<type, int>{

    friend class AvlTreeNew<type, int>;
    int getKey(type data)const override{
        return data->getId();
    }

    bool ifSmaller( type& data , int& b)const override{
        return data->getId()<b;

    }

    bool ifSmaller( type& a , type& b)const override{
        return a->getId() < b->getId();
    }


    bool ifIs( type& a , int& b)const override{
        return a->getId() == b;
    }
    bool ifIs(AvlTreeNew<type,int>::Node* cur,  int& b)const override{
        return cur->data->getId() == b;
    }
};*/



class MoviesByInt:public AvlTreeNew<MoviePtr , int>{

    int getKey(MoviePtr data)const override{
        return data->getId();
    }

    bool ifSmaller( MoviePtr & data , int& b)const override{
        return data->getId()<b;

    }

    bool ifSmaller( MoviePtr & a , MoviePtr & b)const override{
        return a->getId() < b->getId();
    }


    bool ifIs( MoviePtr & a , int& b)const override{
        return a->getId() == b;
    }
    bool ifIs( Node*  a , int& b)const override{
        return a->data->getId() == b;
    }
public:
    Movie* getData(int key){
        return (find(head,key))->data.get();
    }

};


class UsersByInt:public AvlTreeNew<UserPtr , int>{



    bool ifIs( Node*  a , int& b)const override{
        return a->data->getId() == b;
    }
    int getKey(UserPtr data)const override{
        return data->getId();
    }

    bool ifSmaller( UserPtr & data , int& b)const override{
        return data->getId()<b;

    }

    bool ifSmaller( UserPtr & a , UserPtr & b)const override{
        return a->getId() < b->getId();
    }


    bool ifIs( UserPtr & a , int& b)const override{
        return a->getId() == b;
    }
public:
    User* getData(int key){
        return (find(head,key))->data.get();
    }

};

class Movies :public AvlTreeNew<MoviePtr,MovieComperator>{



    bool ifIs( Node*  a , MovieComperator& b)const override{
        return a->data->getCmp() == b;
    }

    MovieComperator getKey(MoviePtr movie)const override{
        return movie->getCmp();
    }



     bool ifSmaller( MoviePtr& a , MovieComperator& b)const override{
        return a->getCmp()<b;
    }

    bool ifSmaller( MoviePtr& a , MoviePtr& b)const override{
        return a->getCmp() < b->getCmp();
    }



     bool ifIs( MoviePtr& a , MovieComperator& b)const override{
        return a->getCmp() == b;
    }

    MoviePtr highestRated(Node* cur){
        if(cur->left == nullptr)
            return cur->data;
        return highestRated(cur->left);
    }

public:
    MoviePtr updateHighest(){
        if(head != nullptr)
            return highestRated(head);

    }
    Movie* getData(MovieComperator key){
        return (find(head,key))->data.get();
    }


};

//typedef IntKeyAVlTree<MoviePtr> MoviesByInt;
//typedef IntKeyAVlTree<UserPtr> UsersByInt;





#endif //__1_MOVIES_H
