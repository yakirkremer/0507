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

        //Node(type data) : data(data), right(NULL), left(NULL), height(0) {}
        Node(type data):data(data), right(NULL), left(NULL), height(0) {}
       // bool operator<(Node* other){
         //   return *(this->data) < *(other->key);
        //}
       // bool operator==(Node *other) {
           // return this->key == other->key;
       // }
        void updateHeight(){
            int rHeight = -1, lHeight = -1;
            if(right != NULL)
                rHeight = right->height;
            if(left != NULL)
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

        if (cur->right != NULL)
            RH = cur->right->height;
        if (cur->left != NULL)
            LH = cur->left->height;
        return LH - RH;
    }
    void copy(Node* cur,Node* other){
        cur->right = other->right;
        cur->left  = other->left;
        cur->data = other->data;
        //
        // cur->key = other->key;
        cur->height = other->height;
        other->left = NULL;
        other->right = NULL;
    }
    Node* findLeftest(Node * cur){
        if(cur->left == NULL)
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
        leftChild = NULL;
        return cur;
    }

    Node *deleteRightChild(Node* cur){
        Node* rightChild = cur->right;
        copy(cur, rightChild);
        delete rightChild;
        rightChild = NULL;
        return cur;
    }


public:
    virtual cmp getKey(type dat)const=0;


    Node * getHead(){
        return head;
    }
    AvlTreeNew():head(NULL),size(0){}
    virtual ~AvlTreeNew() {
        delete head;
    }

    const int getSize()const{
        return size;
    }
    void putDataInOrderAux(type* datas,Node* cur, int* i){
        if(cur == NULL)
            return;
        putDataInOrderAux(datas,cur->left,i);
        datas[*i] = cur->data;
        (*i)++;
        putDataInOrderAux(datas,cur->right,i);


    }
    void putDataInOrder(type * datas){
        if(head == NULL || size == 0)
            throw EmptyTree();
        int * i =new int(0);
        putDataInOrderAux(datas,head,i);
        delete i;
    }




    void postorder(Node *p, int indent) {
        if (p != NULL) {
            if (p->right) {
                postorder(p->right, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
            //std::cout << *(p->data) << "\n ";
            if (p->left) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                postorder(p->left, indent + 4);
            }
        }
    }



private:

    virtual bool ifSmaller( cmp a , cmp b)const = 0;



    virtual bool ifSmaller( type a , cmp b)const=0;

    virtual bool ifSmaller( type a , type b)const=0;

    virtual bool ifSmaller( cmp a , type b)const=0;
    virtual bool ifIs( cmp a , cmp b)const=0;

    virtual bool ifIs( type a , cmp b)const=0;

    virtual bool ifIs( cmp a ,type b)const=0;
    virtual Node * find(Node* cur,cmp tmpKey){
        if(cur == NULL)
            throw NoNodeExist();
        if(ifIs(cur->data,tmpKey))//if(tmpKey == (cur->data->getCmp()))
            return cur;
        if(cur->right == NULL && cur->left == NULL)
            throw NoNodeExist();
        if(!ifSmaller( cur->data,tmpKey))//if(tmpKey < (cur->data->getCmp()))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
public:
    type getData(cmp keyToFInd){
        try
        {
            type res = find(head, keyToFInd)->data;
            return res; //find(head,keyToFInd)->data;
        }
        catch (...)
        {
            throw NoNodeExist();
        }
    }
    virtual bool nodeExist(cmp tmpyKey){
        try{
            find(head,tmpyKey);
        }
        catch (...){
            return false;
        }
    }
    virtual Node* addNode(Node* cur,Node* newNode){

        if(cur == NULL) {
            cur = newNode;
            return cur;
        }

        if(cur->data == newNode->data)
            throw alreadyExists();

        if(ifSmaller(newNode->data, cur->data))
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }

    virtual Node* removeNode(Node * cur, cmp requestedKey){
        if(cur == NULL)
            throw NoNodeExist();
        if(ifIs(requestedKey,cur->data)){
            if(cur->right == NULL && cur->left == NULL)
            {
                //delete cur;
                cur = NULL;
                return cur;
            }

            else if (cur->right == NULL && cur->left != NULL)
            {
                cur = deleteLeftChild(cur);
            }
            else if (cur->left == NULL && cur->right != NULL)
            {
                cur =  deleteRightChild(cur);
            }
            else if (cur->left != NULL && cur->right != NULL)
            {
                Node* minOfRight = findLeftest(cur->right);
                cur->data = minOfRight->data;
                //cur->key = minOfRight->key;
                cur->setRight( removeNode(cur->right,getKey(cur->data)));
            }
        }

        else
        {
            if(ifSmaller(requestedKey,cur->data)) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }


public:


    virtual void add(type newData, cmp newKey){
        Node* newNode = new Node(newData);
        head = addNode(head, newNode);
        size++;

    }
    virtual void remove(cmp requestedKey){
        //postorder(head,2);

        head = removeNode(head,requestedKey);
        size--;
    }
    ////////////////////////**********



};





#endif //__1_AVLTREENEW_H
