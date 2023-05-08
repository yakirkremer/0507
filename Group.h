//
// Created by yakir on 5/5/2023.
//

#ifndef __1_GROUP_H
#define __1_GROUP_H
//#include "AvlTree.h"
#include "AvlTreeNew.h"
#include "User.h"
template<class type, class cmp>
class Group:public UsersByInt {
    int  groupId;

public:
    Group(int groupId):UsersByInt(),groupId((groupId)){}
    int  getId(){
        return groupId;
    }
    bool operator<(Group<type, cmp>* other){
        return  this->groupId < other->groupId;
    }
};


class UsersGroup: public Group<shared_ptr<User>,int>{
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



    bool operator==(UsersGroup other){
        return this->getId() == other.getId();
    }

    UsersGroup(int groupId): Group(groupId),isVip(false), vipS(0),actionViews(new int(0))
            ,comedyViews(new int(0)),fantasyViews(new int(0)),dramaViews(new int(0)),comedyTmp(new int(0))
            ,dramaTmp(new int(0)),actionTmp(new int(0)),fantasyTmp(new int(0)){
        if(groupId <= 0 )
            throw NotValidId();
    }

    void addVip(){
        vipS++;
    }
    void removeVip(){
        vipS--;
    }
    void updateViewsForAllAux(Node* cur){
        if(cur!= nullptr) {
            updateViews(cur->data);
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

    void updateViews(shared_ptr<User> user){
        user->updateViews(*actionTmp,*comedyTmp,*dramaTmp,*fantasyTmp);

        //actionViews-= actionViews/size;
        //comedyViews-=comedyViews/size;
        //fantasyViews-=fantasyViews/size;
        //dramaViews-=dramaViews/size;
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
    void watch(shared_ptr<Movie> movie){
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


class Groups:public AvlTreeNew<UsersGroup*, int>{
    int getKey(UsersGroup* group)const override{
        return group->getId();
    }

    bool ifSmaller( int a , int b)const override{
        return a<b;
    }

    bool ifSmaller( UsersGroup* a , int b)const override{
        return a->getId()<b;
    }

    bool ifSmaller( UsersGroup* a , UsersGroup* b)const override{
        return a->getId() < b->getId();
    }

    bool ifSmaller( int a , UsersGroup* b)const override{
        return !(b->getId()<a);
    }
    bool ifIs( int a , int b)const override{
        return a == b;
    }

    bool ifIs( UsersGroup* a , int b)const override{
        return a->getId() == b;
    }
    bool ifIs( int a , UsersGroup* b)const override{
        return a == b->getId();
    }
};

#endif //__1_GROUP_H
