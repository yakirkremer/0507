//
// Created by yakir on 5/5/2023.
//

#ifndef תרגיל_רטוב_1_AVLTREE_H
#define תרגיל_רטוב_1_AVLTREE_H
#include <iostream>
#include <iomanip>


template <class type, class cmp>
class AvlTree{
    struct Node{
        type data;
        cmp* key;
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
        Node(type data, cmp* key) : data(data), key(key), right(nullptr), left(nullptr), height(0) {}
        bool operator<(Node* other){
            return *(this->key) < *(other->key);
        }
        bool operator==(Node *other) {
            return this->key == other->key;
        }
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
        cur->key = other->key;
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

    Node* addNode(Node* cur,Node* newNode){
        if(cur == nullptr) {
            cur = newNode;
            return cur;
        }
        if(newNode < cur)
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }
    Node* removeNode(Node * cur, cmp* requestedKey){

        if(*requestedKey == *(cur->key)){
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
                cur->setRight( removeNode(cur->right,cur->key));
            }
        }

        else
        {
            if (*requestedKey < *(cur->key))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node * find(Node* cur,cmp * tmpKey){
        if(cur == nullptr)
            return nullptr;
        if(*tmpKey == *(cur->key))
            return cur;
        if(cur->right == nullptr && cur->left == nullptr)
            return nullptr;
        if(*tmpKey < *(cur->key))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
public:
    Node * getHead(){
        return head;
    }
    AvlTree():head(nullptr),size(0){}
    virtual ~AvlTree() {
        delete head;
    }
    void add(type newData, cmp* newKey){
        Node* newNode = new Node(newData, newKey);
        head = addNode(head, newNode);
        size++;

    }
    void remove(cmp *requestedKey){
        head = removeNode(head,requestedKey);
        size--;
    }
    const int getSize()const{
        return size;
    }
    void putDataInOrderAux(type datas,Node* cur, int* i){
        if(cur == nullptr)
            return;
        putDataInOrderAux(datas,cur->left,i);
        datas[*i] = cur->data;
        (*i)++;
        putDataInOrderAux(datas,cur->right,i);


    }
    void putDataInOrder(type * datas){
        int * i =new int(0);
        putDataInOrderAux(datas,head,i);
        delete i;
    }
    type& getData(cmp* keyToFInd){
        return find(head,keyToFInd)->data;
    }
    bool nodeExist(cmp * tmpKey){
        if(find(head,tmpKey) == nullptr)
            return false;
        return true;
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
            std::cout << *(p->key) << "\n ";
            if (p->left) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                postorder(p->left, indent + 4);
            }
        }
    }


};



#endif //תרגיל_רטוב_1_AVLTREE_H
