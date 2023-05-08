//
// Created by yakir on 5/5/2023.
//

#ifndef __1_COMPERATOR_H
#define __1_COMPERATOR_H
#include "wet1util.h"
#include <iostream>

class Comperator{
protected:
    int Id;
    bool vip;

public:
    Comperator():Id(0),vip(false){}
    virtual ~Comperator()=default;

    Comperator(int Id,bool vip = false){
        this->Id = Id;
        this->vip = vip;
    }
    bool isVip(){
        return vip;
    }

    bool operator!(){
        if(Id <= 0)
            return false;
        return true;
    }
    bool operator<(const Comperator& other)
    {
        return this->Id < other.Id;
    }

    bool operator==(const Comperator& other)
    {
        return this->Id == other.Id;
    }
    bool validVip(Comperator* other){
        return this->vip == other->vip;
    }
    int getId(){
        return Id;
    }
    virtual void print(std::ostream& os){
       os<< Id <<"\n";
    }
    friend std::ostream & operator<<(std::ostream & os,Comperator& cmp){
        cmp.print(os);
    }
    Comperator(const Comperator& other):Id(other.Id),vip(other.vip){}
};



typedef Comperator UserComperator;

class MovieComperator:public Comperator{
    int rating;
    int views;
public:
    MovieComperator(int Id,bool vip, int views): Comperator(Id,vip){
        this->views = views;
        this->rating = 0;

    }
    virtual ~MovieComperator()= default;
    int getRating(){
        return rating;
    }
    bool operator<(MovieComperator& other){
        if(this->rating == other.rating)
        {
            if(this->views == other.views)
            {
                return this->Id < other.Id;
            }
            return this->views > other.views;
        }
        return this->rating > other.rating;
    }
    bool operator==(MovieComperator other){
        return ((this->rating == other.rating) && (this->views == other.views) && (this->Id == other.Id));
    }
    void addViews(int newViews){
        views += newViews;
    }
    void setRating(int newRating){
        rating = newRating;
    }
    int getViews(){
        return views;
    }
    void print(std::ostream& os)override{
        os<<rating<< "   "<< views << "    " << Id <<"\n";
    }

    MovieComperator (const MovieComperator& other)= default;// Comperator(other),rating(other.rating),views(other.views){}
    MovieComperator& operator=(const MovieComperator& other) = default;
    MovieComperator():Comperator(),rating(0),views(0){}


};

#endif //__1_COMPERATOR_H
