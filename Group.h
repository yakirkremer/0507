//
// Created by yakir on 5/5/2023.
//

#ifndef __1_GROUP_H
#define __1_GROUP_H
#include "AvlTree.h"


template<class type, class cmp>
class Group:public AvlTree<type,cmp>{
    cmp * groupId;

public:
    Group(int groupId):groupId(new int(groupId)){}
    int * getId(){
        return groupId;
    }
    bool operator<(Group<type, cmp>* other){
        return  this->groupId < other->groupId;
    }
};

#endif //__1_GROUP_H
