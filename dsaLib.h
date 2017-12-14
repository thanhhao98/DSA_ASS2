/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>

using namespace std;


class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};


/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
 template <class T>
 struct AVLNode{
     T data;
     AVLNode<T> *_pLeft, *_pRight;
     int status;
     AVLNode<T>(T &a) : data(a), _pLeft(NULL), _pRight(NULL), status(0){}
 };
 
 template <class T>
 class AVLTree{
 private:
     AVLNode<T> *_pRoot;
 public:
     AVLTree<T>(): _pRoot(NULL){};
     AVLTree<T>(T &a);
     ~AVLTree<T>(){release(this->_pRoot);}
     AVLNode<T>* &getRoot(){return _pRoot;};
     bool insert(T a){return insert(this->_pRoot, a); }
     bool remove(T a){return remove(this->_pRoot, a); }
     AVLNode<T>* find(T a){return find(this->_pRoot, a); }
 protected:
     bool insert(AVLNode<T>* &pR, T a);
     bool remove(AVLNode<T>* &pR, T a);
     AVLNode<T>* find(AVLNode<T>* pR, T a);
     void release(AVLNode<T>* &pR);
 
     void roteLeft(AVLNode<T>* &pR);
     void roteRight(AVLNode<T>* &pR);
     void roteLR(AVLNode<T>* &pR);
     void roteRL(AVLNode<T>* &pR);
     
     bool balanceLeft(AVLNode<T>* &pR);
     bool balanceRight(AVLNode<T>* &pR);    
     bool balanceLR(AVLNode<T>* &pR);
     bool balanceRL(AVLNode<T>* &pR);
 
 };
 
 
 template <class T>
 void AVLTree<T>::roteRight(AVLNode<T>* &pR){
     AVLNode<T> *tempNode = pR;
     pR = pR->_pLeft;
     tempNode->_pLeft = pR->_pRight;
     pR->_pRight = tempNode;
 }
 
 template <class T>
 void AVLTree<T>::roteLeft(AVLNode<T>* &pR){
     AVLNode<T> *tempNode = pR;
     pR = pR->_pRight;
     tempNode->_pRight = pR->_pLeft;
     pR->_pLeft = tempNode;
 }
 
 template <class T>
 void AVLTree<T>::roteLR(AVLNode<T>* &pR){
     roteLeft(pR->_pLeft);
     roteRight(pR);
 }
 
 template <class  T>
 void AVLTree<T>::roteRL(AVLNode<T>* &pR){
     roteRight(pR->_pRight);
     roteLeft(pR);
 }
 
 template <class T>
 bool AVLTree<T>::balanceLeft(AVLNode<T>* &pR){
     if(pR->status==-1){
         pR->status=pR->_pRight->status=0;
         return true;
     } else if(pR->status==0){
         pR->status=1;
         pR->_pRight->status = -1;
         return false;
     } else {
         return false;
     }
 }
 
 template <class T>
 bool AVLTree<T>::balanceRight(AVLNode<T>* &pR){
     if(pR->status==1){
         pR->status=pR->_pLeft->status=0;
         return true;
     } else if(pR->status==0){
         pR->status=-1;
         pR->_pLeft->status=1;
         return false;
     } else {
         return false;
     }
 }
 
 template <class T>
 bool AVLTree<T>::balanceLR(AVLNode<T>* &pR){
     if(pR->status==0){
         pR->_pLeft->status=pR->_pRight->status=0;
     } else if(pR->status==-1){
         pR->status=pR->_pLeft->status=0;
         pR->_pRight->status=1;
     } else {
         pR->status=pR->_pRight->status=0;
         pR->_pLeft->status=-1;
     }
     return true;
 
 }
 
 template <class T>
 bool AVLTree<T>::balanceRL(AVLNode<T>* &pR){
     if(pR->status==0){
         pR->_pLeft->status=pR->_pRight->status=0;
     } else if(pR->status==-1){
         pR->status = pR->_pLeft->status=0;
         pR->_pRight->status=1;
     } else {
         pR->status = pR->_pRight->status=0;
         pR->_pLeft->status=-1;
     }
     return true;
 }
 
 template <class T>
 bool AVLTree<T>::insert(AVLNode<T>* &pR, T a){
     if(!pR){
         AVLNode<T> *newNode = new AVLNode<T>(a);
         pR = newNode;
         return true;
     } else if(pR->data > a){
         if(this->insert(pR->_pLeft, a)){
             if(pR->status==0){
                 pR->status = -1;
                 return true;
             } else if(pR->status==1){
                 pR->status = 0;
                 return false;
             } else {
                 if(pR->_pLeft->status == 0){
                     return false;
                 } else if(pR->_pLeft->status == -1){
                     roteRight(pR);
                     return !balanceLeft(pR);
                 } else {
                     roteLR(pR);
                     return !balanceLR(pR);
                 }
             }
         } else {
             return false;
         }
     } else if(pR->data < a){
         if(this->insert(pR->_pRight, a)){
             if(pR->status == 0){
                 pR->status = 1;
                 return true;
             } else if(pR->status==-1){
                 pR->status = 0;
                 return false;
             } else{
                 if(pR->_pRight->status==0){
                     return false;
                 } else if(pR->_pRight->status==1){
                     roteLeft(pR);
                     return !balanceRight(pR);
                 } else {
                     roteRL(pR);
                     return !balanceRL(pR);
                 }
             }
         } else {
             return false;
         }
     } else {
         return false;
     }
 }
 
 template <class T>
 bool AVLTree<T>::remove(AVLNode<T>* &pR, T a){
     if(!pR){
         return false;
     } else if(pR->data>a){
         if(this->remove(pR->_pLeft,a)){
             if(pR->status==0){
                 pR->status=1;
                 return false;
             } else if(pR->status==-1){
                 pR->status=0;
                 return true;
             } else {
                 if(pR->_pRight->status==-1){
                     roteRL(pR);
                     return balanceRL(pR);
                 } else {
                     roteLeft(pR);
                     return balanceRight(pR);
                 }
             }
         } else {
             return false;
         }
     } else if(pR->data<a) {
         if(this->remove(pR->_pRight,a)){
             if(pR->status==0){
                 pR->status=-1;
                 return false;
             } else if(pR->status==1){
                 pR->status=0;
                 return true;
             } else {
                 if(pR->_pLeft->status==1){
                     roteLR(pR);
                     return balanceLR(pR);
                 } else {
                     roteRight(pR);
                     return balanceLeft(pR);
                 }
             }
         } else {
             return false;
         }
     } else {
         if(!pR->_pLeft&&!pR->_pRight){
             pR=NULL;
         } else if(!pR->_pLeft){
             pR=pR->_pRight;
         } else if(!pR->_pRight){
             pR=pR->_pLeft;
         } else {
             AVLNode<T> *temp = pR->_pRight;
             while(temp->_pLeft){
                 temp=temp->_pLeft;
             }
             temp->_pLeft = pR->_pLeft;
             pR->data = temp->data;
             if(this->remove(pR->_pRight,pR->data)){
                 if(pR->status==0){
                     pR->status=-1;
                     return false;
                 } else if(pR->status==1){
                     pR->status=0;
                     return true;
                 } else {
                     if(pR->_pLeft->status==1){
                         roteLR(pR);
                         return balanceLR(pR);
                     } else {
                         roteRight(pR);
                         return balanceLeft(pR);
                     }
                 }
             } else {
                 return false;
             }
         }
     }
 }
 
 template <class T>
 AVLNode<T>* AVLTree<T>::find(AVLNode<T>* pR, T a){
     if(!pR){
         return NULL;
     } else if(pR->data==a){
         return pR;
     } else if(pR->data<a){
         return find(pR->_pRight,a);
     } else return find(pR->_pLeft,a);
 }
 
 template <class T>
 void AVLTree<T>::release(AVLNode<T>* &pR){
     if(pR){
         if(pR->_pLeft){
             release(pR->_pLeft);
         }
         if(pR->_pRight){
             release(pR->_pRight);
         }
         delete(pR);
     }
 }
 


/************************************************************************
 * This section is for Linklist
 ************************************************************************/

 template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    AVLTree<T> treeAVL;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    L1Item<T>   *_pTail;// The tail pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pTail(NULL), _pHead(NULL), _size(0) {}
    ~L1List(){}

    L1Item<T> *getHead(){return _pHead;}
    L1Item<T> *getTail(){return _pTail;}

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);
    T&      operator[](int i){
        L1Item<T> *temp = _pHead;
        for(int j=0;j<i;j++) temp=temp->pNext;
        return temp->data;
    }

    bool    find(T& a, int& idx);
    T*      find(T& a);
    T*      findLast(T& a);
    int     insert(int i, T& a);
    int     remove(int i);
    int     removeAll(T& a);

    int     push_back(T& a);
    int     insertHead(T& a);

    int     removeHead();
    int     removeLast();


    void    traverse(void (*op)(T&)) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    L1Item<T> *newNode = new L1Item<T>(a);
    if (_pHead) {
        _pTail->pNext = newNode;
        _pTail = newNode;
    } else {
        _pTail=_pHead = newNode;
    }
    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *newNode = new L1Item<T>(a);
    if(_pTail){
        newNode->pNext = _pHead;
        _pHead = newNode;
    } else {
        _pHead = _pTail = newNode;
    }
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead!=_pTail) {
        L1Item<T> *temp = _pHead;
        _pHead = _pHead->pNext;
        delete temp;
        _size--;
        return 0;
    }
    _pHead = _pTail = NULL;
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead!=_pTail) {
        L1Item<T> *temp = _pHead;
        while(temp->pNext!=_pTail){
            temp=temp->pNext;
        }
        delete temp->pNext;
        _pTail = temp;
        return 0;
    }
    _pHead=_pTail=NULL;
    return -1;
}



#endif //A02_DSALIB_H
