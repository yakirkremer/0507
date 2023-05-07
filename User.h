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
    Comperator* cmp;
    int * Id;
    int groupID;
    int actionViews;
    int comedyViews;
    int dramaViews;
    int fantasyViews;

public:

    virtual ~User(){
        delete cmp;
    }

    Comperator* getCmp(){
        return cmp;
    }
    int getActionViews() const {
        return actionViews;
    }

    int getComedyViews() const {
        return comedyViews;
    }

    int getDramaViews() const {
        return dramaViews;
    }

    int getFantasyViews() const {
        return fantasyViews;
    }
    virtual void watch(shared_ptr<Movie> movie){
        movie->addViews();
        addViews(movie->getGenre());
    }
    bool operator<(User other){
        return this->cmp->getId() < other.cmp->getId();
    }

    User(int userID, bool isVip):cmp(new Comperator(userID,isVip)),groupID(0),actionViews(0),comedyViews(0),dramaViews(0),fantasyViews(0), Id(new int(userID)){}
    void setGroupID(int ID){groupID = ID;}
    int getGroupID(){ return groupID;}

    int getViews(Genre num){
        switch (num) {
            case Genre::COMEDY:
                return comedyViews;
            case Genre::DRAMA:
                return dramaViews;
            case Genre::ACTION:
                return actionViews;
            case Genre::FANTASY:
                return fantasyViews;
            case Genre::NONE:
                return comedyViews+dramaViews+actionViews+fantasyViews;
        }
    }

    int addViews(Genre num){
        switch (num) {
            case Genre::COMEDY:
                comedyViews++;
                break;
            case Genre::DRAMA:
                dramaViews++;
                break;
            case Genre::ACTION:
                actionViews++;
                break;
            case Genre::FANTASY:
                fantasyViews++;
                break;
        }
    }

    int * getId(){
        return Id;
    }

    virtual bool Vip(){
        return cmp->vip;
    }
};


#endif //__1_USER_H
