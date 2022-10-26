#ifndef BST_H
#define BST_H

#include <iostream>
#include "Node.h"
using namespace std;

class BST{      //Binary Search Tree
    private:
        Node *Root;

        void insert(double &, string, Node *&);
        void inOrder(Node *);
        void preOrder(Node *);
        void postOrder(Node *);
        void deleteNode(int&, Node *&);
        void substituteToMin(Node *&, Node *&);

        int height(Node*);
        bool ancestors(Node*, int);
        int level(Node*, int);
        int whatLevelAmI(Node*, int, int);

    public:
        BST(): Root(NULL){}
        /*~BST(){
            DeleteBST(this->Root);
            cout << "\nDestructor: BST deleted. \n";
        }*/

        //Funciones
        void insert(double &value, string data) {insert(value, data, this->Root);}
        void inOrder() {(inOrder(this->Root));}
        void preOrder() {(preOrder(this->Root));}
        void postOrder() {(postOrder(this->Root));}
        void BFT(); //level order

        void deleteNode(int &value) {deleteNode(value, this->Root);}

        int height(){return height(this->Root);}
        bool ancestors(int data) {return ancestors(this->Root, data);}
        int level(int data) {return level(this->Root, data);}
        int whatLevelAmI(int data, int level) {return whatLevelAmI(this->Root, data, level);}

        //void DeleteBST(Node*&);
        
};


#endif // BST_H