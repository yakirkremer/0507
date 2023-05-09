//
// Created by yakir on 5/8/2023.
//

#ifndef __1_AVLTREENEW_H
#define __1_AVLTREENEW_H

#include <iostream>
#include <iomanip>


class NoNodeExist:public std::exception{};
class alreadyExists:public std::exception{};
class EmptyTree:public std::exception{};

template <class type, class cmp>
class AvlTreeNew{
protected:
    struct Node{
        type data;
        //cmp* key;
        Node* right;
        Node* left;
        int height;

        virtual ~Node(){
            delete right;
            delete left;
            //delete data;
        }
        int max(int a, int b){
            if(a>b)
                return a;
            return b;
        }


        Node(type data):data(data), right(nullptr), left(nullptr), height(0) {}

        void updateHeight(){
            int rHeight = -1, lHeight = -1;
            if(right != nullptr)
                rHeight = right->height;
            if(left != nullptr)
                lHeight = left->height;
            height = max(rHeight, lHeight) +1;
        }
        void setLeft(Node* newNode){left = newNode;}
        void setRight(Node* newNode){right = newNode;}


    };

    int getHeight(Node * cur){
        return cur->height;
    }
    Node * head;
    int size;
    int getBf(Node* cur){
        int RH = -1, LH = -1;

        if (cur->right != nullptr)
            RH = cur->right->height;
        if (cur->left != nullptr)
            LH = cur->left->height;
        return LH - RH;
    }
    void copy(Node* cur,Node* other){
        cur->right = other->right;
        cur->left  = other->left;
        cur->data = other->data;
        cur->height = other->height;
        other->left = nullptr;
        other->right = nullptr;
    }
    Node* findLeftest(Node * cur){
        if(cur->left == nullptr)
            return cur;
        return findLeftest(cur->left);
    }
    Node* rotateLL(Node *cur){
        Node* A = cur;
        Node* B = cur->left;
        Node* C = cur->left->left;
        A->setLeft(B->right);
        B->setRight(A);
        A->updateHeight();
        B->updateHeight();
        return B;
    }
    Node* rotateRR(Node *cur){
        Node* A = cur;
        Node* B = cur->right;
        Node* C = cur->right->right;
        A->setRight(B->left);
        B->setLeft(A);
        A->updateHeight();
        B->updateHeight();
        return B;
    }
    Node* rotateLR(Node *cur) {
        cur->setLeft(rotateRR(cur->left))  ;
        return rotateLL(cur);
    }
    Node* rotateRL(Node *cur) {
        cur->setRight(rotateLL(cur->right));
        return rotateRR(cur);
    }
    Node* fixBalance(Node *cur) {
        if (getBf(cur) == 2) {
            if (getBf(cur->left) == -1)
                return rotateLR(cur);
            else
                return rotateLL(cur);
        } else if (getBf(cur) == -2) {
            if (getBf(cur->right) == 1)
                return rotateRL(cur);
            else
                return rotateRR(cur);
        }
        return cur;
    }
    Node *deleteLeftChild(Node* cur){
        Node* leftChild = cur->left;
        copy(cur, leftChild);
        delete leftChild;
        leftChild = nullptr;
        return cur;
    }
    Node *deleteRightChild(Node* cur){
        Node* rightChild = cur->right;
        copy(cur, rightChild);
        delete rightChild;
        rightChild = nullptr;
        return cur;
    }
    void putDataInOrderAux(type* datas,Node* cur, int* i){
        if(cur == nullptr)
            return;
        putDataInOrderAux(datas,cur->left,i);
        datas[*i] = cur->data;
        (*i)++;
        putDataInOrderAux(datas,cur->right,i);


    }
    //virtual bool ifSmaller( cmp a , cmp b)const = 0;
    virtual bool ifSmaller( type& a , cmp& b)const=0;
    virtual bool ifSmaller( type& a , type& b)const=0;
    //virtual bool ifSmaller( cmp a , type b)const=0;
    //virtual bool ifIs( cmp a , cmp b)const=0;
    virtual bool ifIs( type& a , cmp& b)const=0;
    virtual bool ifIs( Node* a , cmp& b)const=0;
    //virtual bool ifIs( cmp a ,type b)const=0;
    type& return_data(Node* cur){
        return cur->data;
    }
    virtual Node * find(Node* cur,cmp tmpKey){
        if(cur == nullptr)
            throw NoNodeExist();
        if(ifIs(cur, tmpKey))//type,cmo
            return cur;
        if(cur->right == nullptr && cur->left == nullptr)
            throw NoNodeExist();
        if(!ifSmaller( cur->data,tmpKey))//type,cmp
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
    virtual Node* addNode(Node* cur,Node* newNode){

        if(cur == nullptr) {
            cur = newNode;
            return cur;
        }

        if(cur->data == newNode->data)
            throw alreadyExists();

        if(ifSmaller(newNode->data, cur->data))//type,cmp
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }
    Node* removeNode(Node * cur, cmp requestedKey){
        if(cur == nullptr)
            throw NoNodeExist();
        if(ifIs(cur,requestedKey)){//cmp,type
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
                //cur->key = minOfRight->key;
                cur->setRight( removeNode(cur->right,getKey(cur->data)));
            }
        }

        else
        {
            if(!ifSmaller(cur->data,requestedKey)) //cmp,type
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }
    virtual cmp getKey(type dat)const=0;

public:
    AvlTreeNew():head(nullptr),size(0){}
    virtual ~AvlTreeNew() {
        delete head;
    }
    Node * getHead(){
        return head;
    }

    const int getSize()const{
        return size;
    }
    void putDataInOrder(type * datas){
        if(head == nullptr || size == 0)
            throw EmptyTree();
        int * i =new int(0);
        putDataInOrderAux(datas,head,i);
        delete i;
    }
    /* type getData(cmp keyToFInd){
        try
        {
            Node* res = find(head, keyToFInd);
            //type res = ();
            return res->data; //find(head,keyToFInd)->data;
        }
        catch (...)
        {
            throw NoNodeExist();
        }
    }*/

    virtual void add(type newData){
        Node* newNode = new Node(newData);
        head = addNode(head, newNode);
        size++;

    }
    virtual void remove(cmp requestedKey){
        //postorder(head,2);

        head = removeNode(head,requestedKey);
        size--;
    }




};





#endif //__1_AVLTREENEW_H
