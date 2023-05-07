//
// Created by yakir on 5/5/2023.
//

#ifndef __1_MOVIE_H
#define __1_MOVIE_H
#include "wet1util.h"

#include "Comperator.h"

class Movie {
    int *Id;
    Genre genre;
    int rates;
    MovieComperator * cmp;


    int getRating(){
        return cmp->getRating();
    }


public:

    virtual ~Movie(){
        delete cmp;
    }
    MovieComperator* getCmp(){
        return cmp;
    }

    operator int(){
        return cmp->getId();
    }

    int * getId(){
        return Id;
    }
/*
    bool operator<(Movie other){
        if(other.rating == this->rating)
        {
            if(this->views == other.views)
            {
                return other.ID > this->ID  ;
            }
            return this->views > other.views;

        }
        return this->rating > other.rating;
    }
*/
    int getViews(){
        return cmp->getViews();
    }
    void addViews(int curViews = 1)
    {
        cmp->addViews(curViews);
    }
    Movie(int Id, Genre genre, int views, bool vip):cmp(new MovieComperator(Id,vip,views)),genre(genre),rates(0), Id(new int(Id)){}

    bool isVip(){
        return cmp->vip ;
    }

    void setVip(bool vip){
        cmp->vip = vip;
    }

    Genre getGenre(){
        return genre;
    }

    void watch(){
        addViews();
    }
    void rate(int newRating){
        cmp->setRating( ((cmp->getRating()*(rates))+newRating)/(rates+1));
        rates++;
    };



};

#endif //__1_MOVIE_H
