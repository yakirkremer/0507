//
// Created by yakir on 5/5/2023.
//

#ifndef __1_USER_H
#define __1_USER_H

#include "Comperator.h"
#include "Movie.h"

#include <memory>;

using namespace std;


class User {
protected:
    int  Id;
    bool Vip;
    int groupID;
    int actionViews;
    int comedyViews;
    int dramaViews;
    int fantasyViews;
    int * groupAction;
    int* groupDrama;
    int* groupFantasy;
    int* groupComedy;
    int* actionTmp;
    int* comedyTmp;
    int * dramaTmp;
    int* fantasyTmp;


public:

    bool operator==(User other){
        return this->getId() == other.getId();
    }

    virtual ~User(){
    }


    int getActionViews() const {
        if(actionTmp== nullptr)
            return actionViews;
        return actionViews + *actionTmp;
    }

    void updateViews(int action,int comedy, int drama, int fantasy){
        actionViews+=action;
        comedyViews+=comedy;
        dramaViews+=drama;
        fantasyViews+=fantasy;
    }

    int getComedyViews() const {
        if(comedyTmp== nullptr)
            return comedyViews;
        return comedyViews+*comedyTmp;
    }

    int getDramaViews() const {
        if(dramaTmp== nullptr)
            return dramaViews;
        return dramaViews+*dramaTmp;
    }

    int getFantasyViews() const {
        if(fantasyTmp== nullptr)
            return fantasyViews;
        return fantasyViews+*fantasyTmp;
    }
    virtual void watch(shared_ptr<Movie> movie){
        if(movie->isVip())
            if(!isVip())
                throw NotVip();
        movie->addViews();
        addViews(movie->getGenre());
    }


    User(int userID, bool isVip):Id(userID),Vip(isVip),groupID(0),actionViews(0),comedyViews(0),dramaViews(0)
    ,fantasyViews(0),groupAction(nullptr),groupComedy(nullptr),groupDrama(nullptr),groupFantasy(nullptr)
            ,actionTmp(nullptr),comedyTmp(nullptr),dramaTmp(nullptr),fantasyTmp(nullptr){
        if(userID <= 0 )
            throw NotValidId();
    }
    void setGroup(int ID,int* a,int* c, int* d, int* f,int* aT,int* cT, int* dT, int* fT){
        groupID = ID;
        groupAction = a;
        groupDrama = d;
        groupComedy = c;
        groupFantasy = f;
        actionTmp = aT;
        comedyTmp = cT;
        fantasyTmp = fT;
        dramaTmp = dT;

    }

    bool isVip()
    {
        return Vip;
    }

    int getGroupID(){ return groupID;}

    int getViews(Genre num){
        int action=0,drama=0,fantasy=0,comedy=0;
        if(comedyTmp)
             comedy = *comedyTmp;
        if(dramaTmp)
             drama = *dramaTmp;
        if(actionTmp)
             action = *actionTmp;
        if(fantasyTmp)
             fantasy = *fantasyTmp;
        switch (num) {
            case Genre::COMEDY:
                return comedyViews+comedy;
            case Genre::DRAMA:
                return dramaViews+drama;
            case Genre::ACTION:
                return actionViews+action;
            case Genre::FANTASY:
                return fantasyViews+fantasy;
            case Genre::NONE:
                return comedyViews+dramaViews+actionViews+fantasyViews;
        }
    }

    int addViews(Genre num){
        switch (num) {
            case Genre::COMEDY:
                if(groupID!=0)
                    *groupComedy++;
                comedyViews++;
                break;
            case Genre::DRAMA:
                if(groupID!=0)
                    *groupDrama++;
                dramaViews++;
                break;
            case Genre::ACTION:
                if(groupID!=0)
                    *groupAction++;
                actionViews++;
                break;
            case Genre::FANTASY:
                if(groupID!=0)
                    *groupFantasy++;
                fantasyViews++;
                break;
        }
    }

    int  getId(){
        return Id;
    }




    void rateMovie(shared_ptr<Movie> movie, int rating){
        movie->rate(rating);
    }
};


#endif //__1_USER_H
