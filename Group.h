//
// Created by yakir on 5/5/2023.
//

#ifndef __1_GROUP_H
#define __1_GROUP_H
//#include "AvlTree.h"
#include "Movies.h"


class UsersGroup: public UsersByInt {
    int  groupId;
    bool isVip;
    int* actionViews;
    int* dramaViews;
    int* fantasyViews;
    int* comedyViews;
    int* actionTmp;
    int* dramaTmp;
    int* fantasyTmp;
    int* comedyTmp;
    int vipS;
public:

    int  getId(){
        return groupId;
    }


    bool operator==(shared_ptr<UsersGroup> other){
        return this->getId() == other->getId();
    }



    UsersGroup(int groupId): groupId(groupId),isVip(false), vipS(0),actionViews(new int(0))
            ,comedyViews(new int(0)),fantasyViews(new int(0)),dramaViews(new int(0)),comedyTmp(new int(0))
            ,dramaTmp(new int(0)),actionTmp(new int(0)),fantasyTmp(new int(0)){
        if(groupId <= 0 )
            throw NotValidId();
    }
    virtual ~UsersGroup(){
        delete actionViews;
        delete dramaViews;
        delete comedyViews;
        delete fantasyViews;
        delete actionTmp;
        delete comedyTmp;
        delete dramaTmp;
        delete fantasyTmp;
    }

    void addVip(){
        vipS++;
    }
    void removeVip(){
        vipS--;
    }
    void updateViewsForAllAux(Node* cur){
        if(cur!= nullptr) {
            updateViews(cur->data.get());
            updateViewsForAllAux(cur->right);
            updateViewsForAllAux(cur->left);
        }
    }

    void updateViewsForAll(){
        updateViewsForAllAux(head);

        *actionTmp = 0;
        *comedyTmp = 0;
        *dramaTmp = 0;
        *fantasyTmp = 0;
    }


    void addViewsFromNewUser(int action, int comedy, int drama, int fantasy){
        (*actionViews)+=action;
        (*comedyViews)+=comedy;
        (*dramaViews)+=drama;
        (*fantasyViews)+=fantasy;
    }

    void removeUserViews(int action, int comedy, int drama, int fantasy){
        (*actionViews)-=action;
        (*comedyViews)-=comedy;
        (*dramaViews)-=drama;
        (*fantasyViews)-=fantasy;
    }

    void updateViews(User* user){
        user->updateViews(*actionTmp,*comedyTmp,*dramaTmp,*fantasyTmp);
    }
    void updateVipAux(Node * cur){

        if(isVip)
            return;
        if(cur->data->isVip())
        {
            isVip = true;
            return;
        }
        else {
            updateVipAux(cur->right);
            updateVipAux(cur->right);
        }
    }
    void updateVip(){
        if(vipS > 0)
            isVip = true;
        if(vipS <= 0)
            isVip = false;
        //isVip = false;
        //updateVipAux(this->getHead());

    }
    int getViews(Genre genre){
        switch (genre) {
            case Genre::COMEDY:
                return *comedyViews;
            case Genre::DRAMA:
                return *dramaViews;
            case Genre::ACTION:
                return *actionViews;
            case Genre::FANTASY:
                return *fantasyViews;
            case Genre::NONE:
                return *comedyViews+*dramaViews+*actionViews+*fantasyViews;
        }
    }

    int* getViewsPtr(Genre genre){
        switch (genre) {
            case Genre::COMEDY:
                return comedyViews;
            case Genre::DRAMA:
                return dramaViews;
            case Genre::ACTION:
                return actionViews;
            case Genre::FANTASY:
                return fantasyViews;
        }
    }

    bool vip(){
        return isVip;
    }

    Genre getFavGenre(){
        Genre res = Genre::COMEDY;
        int maxViews = *comedyViews;
        if(*dramaViews > maxViews) {
            res = Genre::DRAMA;
        maxViews = *dramaViews;
        }
        if(*actionViews > maxViews){
            res = Genre::ACTION;
        maxViews = *actionViews;
    }
        if(*fantasyViews > maxViews){
            res = Genre::FANTASY;
        maxViews = *fantasyViews;
    }
        return res;
    }

    int* getTmpPtr(Genre genre){
        switch (genre) {
            case Genre::COMEDY:
                return comedyTmp;
            case Genre::DRAMA:
                return dramaTmp;
            case Genre::ACTION:
                return actionTmp;
            case Genre::FANTASY:
                return fantasyTmp;
        }
    }
    void watch(Movie* movie){
        if(movie->isVip())
            if(!vip())
                throw NotVip();

        movie->addViews(size);
        switch(movie->getGenre()) {
            case Genre::COMEDY:
                (*comedyTmp)++;
                (*comedyViews)+=size;
                break;
            case Genre::DRAMA:
                (*dramaTmp)++;
                (*dramaViews)+=size;
                break;
            case Genre::ACTION:
                (*actionTmp)++;
                (*actionViews)+=size;
                break;
            case Genre::FANTASY:
                (*fantasyTmp)++;
                (*fantasyViews)+=size;
                break;
        }
    }
};



typedef shared_ptr<UsersGroup> UsersGroupPtr;


class Groups:public AvlTreeNew<UsersGroupPtr , int>{



    int getKey(UsersGroupPtr data)const override{
        return data->getId();
    }

    bool ifSmaller( UsersGroupPtr & data , int& b)const override{
        return data->getId()<b;

    }

    bool ifSmaller( UsersGroupPtr & a , UsersGroupPtr & b)const override{
        return a->getId() < b->getId();
    }


    bool ifIs( UsersGroupPtr & a , int& b)const override{
        return a->getId() == b;
    }

    bool ifIs( Node*  a , int& b)const override{
        return a->data->getId() == b;
    }

public:
    UsersGroup* getData(int key){
        return (find(head,key))->data.get();
    }

};
#endif //__1_GROUP_H
