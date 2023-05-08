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
//typedef AvlTreeNew<MoviePtr,MovieComperator> Movies;
class Movies :public AvlTreeNew<MoviePtr,MovieComperator>{


    MovieComperator getKey(MoviePtr movie)const override{
        return movie->getCmp();
    }

     bool ifSmaller( MovieComperator a , MovieComperator b)const override{
        return a<b;
    }

     bool ifSmaller( MoviePtr a , MovieComperator b)const override{
        return a->getCmp()<b;
    }

    bool ifSmaller( MoviePtr a , MoviePtr b)const override{
        return a->getCmp() < b->getCmp();
    }

    bool ifSmaller( MovieComperator a , MoviePtr b)const override{
        return !(b->getCmp()<a);
    }
     bool ifIs( MovieComperator a , MovieComperator b)const override{
        return a == b;
    }

     bool ifIs( MoviePtr a , MovieComperator b)const override{
        return a->getCmp() == b;
    }
    bool ifIs( MovieComperator a , MoviePtr b)const override{
        return a == b->getCmp();
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


};
//typedef AvlTreeNew<MoviePtr,int> MoviesByInt;
//typedef AvlTreeNew<UserPtr ,int> UsersByInt;


class MoviesByInt: public AvlTreeNew<MoviePtr , int>{
public:
    int getKey(MoviePtr movie)const override{
        return movie->getId();
    }

    bool ifSmaller( int a , int b)const override{
        return a<b;
    }

    bool ifSmaller( MoviePtr a , int b)const override{
        return a->getId()<b;
    }

    bool ifSmaller( MoviePtr a , MoviePtr b)const override{
        return a->getId() < b->getId();
    }

    bool ifSmaller( int a , MoviePtr b)const override{
        return !(b->getId()<a);
    }
    bool ifIs( int a , int b)const override{
        return a == b;
    }

    bool ifIs( MoviePtr a , int b)const override{
        return a->getId() == b;
    }
    bool ifIs( int a , MoviePtr b)const override{
        return a == b->getId();
    }



};

class UsersByInt : public AvlTreeNew<UserPtr , int>{
public:
    int getKey(UserPtr user)const override{
        return user->getId();
    }

    bool ifSmaller( int a , int b)const override{
        return a<b;
    }

    bool ifSmaller( UserPtr a , int b)const override{
        return a->getId()<b;
    }

    bool ifSmaller( UserPtr a , UserPtr b)const override{
        return a->getId() < b->getId();
    }

    bool ifSmaller( int a , UserPtr b)const override{
        return !(b->getId()<a);
    }
    bool ifIs( int a , int b)const override{
        return a == b;
    }

    bool ifIs( UserPtr a , int b)const override{
        return a->getId() == b;
    }
    bool ifIs( int a , UserPtr b)const override{
        return a == b->getId();
    }



};

//typedef AvlTreeNew AvlTree;
/*
class Movies:public AvlTreeNew<MoviePtr,MovieComperator>{


public:
    MoviePtr getData(MovieComperator keyToFInd){
        MoviePtr res = find(head,keyToFInd)->data;
        return res; //find(head,keyToFInd)->data;
    }
    bool ifSmaller( MovieComperator a , MovieComperator b){
        return a<b;
    }
    bool ifIs( MovieComperator a , MovieComperator b){
        return a == b;
    }
    Node * find(Node* cur,MovieComperator tmpKey){
        if(cur == nullptr)
            return nullptr;
        if(ifIs(cur->data->getCmp(), tmpKey))//if(tmpKey == (cur->data->getCmp()))
            return cur;
        if(cur->right == nullptr && cur->left == nullptr)
            return nullptr;
        if(ifSmaller(tmpKey, cur->data->getCmp()))//if(tmpKey < (cur->data->getCmp()))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
    bool nodeExist(MovieComperator tmpyKey){
        if(find(head,tmpyKey) != nullptr)
            return true;
        return false;
    }
    Node* addNode(Node* cur,Node* newNode)override{
        if(cur == nullptr) {
            cur = newNode;
            return cur;
        }
        if(ifSmaller(newNode->data->getCmp(), cur->data->getCmp()))
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node* removeNode(Node * cur, MovieComperator requestedKey){
        if(requestedKey == (cur->data->getCmp())){
            if(cur->right == nullptr && cur->left == nullptr)
            {
                //delete cur;
                cur = nullptr;
                return cur;
            }

            else if (cur->right == nullptr && cur->left != nullptr)
            {
                cur = deleteLeftChild(cur);
            }
            else if (cur->left == nullptr && cur->right != nullptr)
            {
                cur =  deleteRightChild(cur);
            }
            else if (cur->left != nullptr && cur->right != nullptr)
            {
                Node* minOfRight = findLeftest(cur->right);
                cur->data = minOfRight->data;
                cur->key = minOfRight->key;
                cur->setRight( removeNode(cur->right,cur->data->getCmp()));
            }
        }

        else
        {
            if(ifSmaller(requestedKey,cur->data->getCmp())) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }
    void add(MoviePtr newData, MovieComperator newKey){
        Node* newNode = new Node(newData);
        head = addNode(head, newNode);
        size++;

    }
    void remove(MovieComperator requestedKey){
        //postorder(head,2);

        head = removeNode(head,requestedKey);
        size--;
    }
};
class MoviesByInt:public AvlTree<MoviePtr,int>{

public:
    MoviePtr getData(int keyToFInd){
        MoviePtr res = find(head,keyToFInd)->data;
        return res; //find(head,keyToFInd)->data;
    }
    bool ifSmaller( int a , int b){
        return a<b;
    }
    bool ifIs( int a , int b){
        return a == b;
    }
    Node * find(Node* cur,int tmpKey){
        if(cur == nullptr)
            return nullptr;
        if(ifIs(cur->data->getId(), tmpKey))//if(tmpKey == (cur->data->getCmp()))
            return cur;
        if(cur->right == nullptr && cur->left == nullptr)
            return nullptr;
        if(ifSmaller(tmpKey, cur->data->getId()))//if(tmpKey < (cur->data->getCmp()))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
    bool nodeExist(int tmpyKey){
        if(find(head,tmpyKey) != nullptr)
            return true;
        return false;
    }
    Node* addNode(Node* cur,Node* newNode)override{
        if(cur == nullptr) {
            cur = newNode;
            return cur;
        }
        if(ifSmaller(newNode->data->getId(), cur->data->getId()))
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node* removeNode(Node * cur, int requestedKey){
        if(requestedKey == (cur->data->getId())){
            if(cur->right == nullptr && cur->left == nullptr)
            {
                //delete cur;
                cur = nullptr;
                return cur;
            }

            else if (cur->right == nullptr && cur->left != nullptr)
            {
                cur = deleteLeftChild(cur);
            }
            else if (cur->left == nullptr && cur->right != nullptr)
            {
                cur =  deleteRightChild(cur);
            }
            else if (cur->left != nullptr && cur->right != nullptr)
            {
                Node* minOfRight = findLeftest(cur->right);
                cur->data = minOfRight->data;
                cur->key = minOfRight->key;
                cur->setRight( removeNode(cur->right,cur->data->getId()));
            }
        }

        else
        {
            if(ifSmaller(requestedKey,cur->data->getId())) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }
    void add(MoviePtr newData, int newKey){
        Node* newNode = new Node(newData);
        head = addNode(head, newNode);
        size++;

    }
    void remove(int requestedKey){
        //postorder(head,2);

        head = removeNode(head,requestedKey);
        size--;
    }
};

class UsersByInt:public AvlTree<UserPtr ,int>{

public:
    UserPtr getData(int keyToFInd){
        UserPtr res = find(head,keyToFInd)->data;
        return res; //find(head,keyToFInd)->data;
    }
    bool ifSmaller( int a , int b){
        return a<b;
    }
    bool ifIs( int a , int b){
        return a == b;
    }
    Node * find(Node* cur,int tmpKey){
        if(cur == nullptr)
            return nullptr;
        if(ifIs(cur->data->getId(), tmpKey))//if(tmpKey == (cur->data->getCmp()))
            return cur;
        if(cur->right == nullptr && cur->left == nullptr)
            return nullptr;
        if(ifSmaller(tmpKey, cur->data->getId()))//if(tmpKey < (cur->data->getCmp()))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
    bool nodeExist(int tmpyKey){
        if(find(head,tmpyKey) != nullptr)
            return true;
        return false;
    }
    Node* addNode(Node* cur,Node* newNode)override{
        if(cur == nullptr) {
            cur = newNode;
            return cur;
        }
        if(ifSmaller(newNode->data->getId(), cur->data->getId()))
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node* removeNode(Node * cur, int requestedKey){
        if(requestedKey == (cur->data->getId())){
            if(cur->right == nullptr && cur->left == nullptr)
            {
                //delete cur;
                cur = nullptr;
                return cur;
            }

            else if (cur->right == nullptr && cur->left != nullptr)
            {
                cur = deleteLeftChild(cur);
            }
            else if (cur->left == nullptr && cur->right != nullptr)
            {
                cur =  deleteRightChild(cur);
            }
            else if (cur->left != nullptr && cur->right != nullptr)
            {
                Node* minOfRight = findLeftest(cur->right);
                cur->data = minOfRight->data;
                cur->key = minOfRight->key;
                cur->setRight( removeNode(cur->right,cur->data->getId()));
            }
        }

        else
        {
            if(ifSmaller(requestedKey,cur->data->getId())) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }
    void add(UserPtr newData, int newKey){
        Node* newNode = new Node(newData);
        head = addNode(head, newNode);
        size++;

    }
    void remove(int requestedKey){
        //postorder(head,2);

        head = removeNode(head,requestedKey);
        size--;
    }
};
*/

#endif //__1_MOVIES_H
