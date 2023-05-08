//
// Created by yakir on 5/5/2023.
//

#ifndef __1_MOVIE_H
#define __1_MOVIE_H
#include "wet1util.h"

#include "Comperator.h"

class NotValidId:public std::exception{};
class NotVip:public std::exception{};
class NotValidGenre:public std::exception{};
class NotValidRating: public std::exception{};
class Movie {
    int Id;
    Genre genre;
    int rates;
    MovieComperator  cmp;


    int getRating(){
        return cmp.getRating();
    }


public:

  /*  Movie (const Movie& other): {
        this->cmp = MovieComperator(other.cmp);
        this->rates = other.rates;
        this->Id = other.Id;
        this->genre = other.genre;

    }*/
    virtual ~Movie(){
        //delete cmp;
    }
    MovieComperator& getCmp(){
        return cmp;
    }

    operator int(){
        return cmp.getId();
    }

    bool operator==(Movie other){
        return this->getId() == other.getId();
    }

    int  getId(){
        return Id;
    }

    int getViews(){
        return cmp.getViews();
    }
    void addViews(int curViews = 1)
    {
        cmp.addViews(curViews);
    }
    Movie(int ID, Genre genre, int views, bool vip){
        if(ID <= 0)
            throw NotValidId();
        if(genre == Genre::NONE)
            throw NotValidGenre();
        this->cmp =  MovieComperator(ID,vip,views);
        this->Id = (ID);
        this->genre = genre;
        this->rates = 0;
    }

    bool isVip(){
        return cmp.isVip();
    }



    Genre getGenre(){
        return genre;
    }

    void watch(){
        addViews();
    }
    void rate(int newRating){
        if(newRating<0 || newRating>100)
            throw NotValidRating();
        cmp.setRating( ((cmp.getRating()*(rates))+newRating)/(rates+1));
        rates++;
    };



};



#endif //__1_MOVIE_H
