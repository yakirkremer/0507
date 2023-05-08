//
// Created by yakir on 5/5/2023.
//


#include <memory>

#include "StreamingDBa1.h"
using namespace std;






int main1(){
streaming_database* base = new streaming_database();

    for (int i = 1; i < 11; ++i) {
        base->add_movie(i,Genre::COMEDY,0, true);
    }

    base->printMovies();







    return 1;
}