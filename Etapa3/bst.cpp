//Fernando Gomez Martinez
//Act 3.1 Advanced operations in BST

#include <iostream>
#include <queue>
#include <vector>
#include "bst.h"

using namespace std;

void BST::insert(double &value, string tx, Node *& root){
    if (root == NULL){
        root = new Node(value, tx);
    }
    else{
        if(value < root->ip){
            insert(value, tx, root->left);
        }
        else if (value > root->ip){
            insert (value, tx, root->right);
        }
        else{
            cout << "Repeated element. \n";
        }
    }
}//complexity o(1)

void BST::preOrder(Node *root){
    if(root == NULL){
        return;
    }
    cout << root->ip << " " << root->text << " -->\n";
    preOrder(root->left);
    preOrder(root->right);
}//complexity o(n^2)

void BST::inOrder(Node *root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    cout << root->ip << " " << root->text << " -->";
    inOrder(root->right);

}//complexity o(n^2)

void BST::postOrder(Node *root){
    if(root == NULL){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->ip << " " << root->text << " -->";

}//complexity o(n^2)

void BST::BFT(){
    if(this->Root == NULL){
        cout << "The BFT is empty.\n";
        return;
    }

    queue<Node*> Q;
    Q.push(Root);

    Node *Aux;
    while (!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while(Aux != NULL){
            cout << Aux->ip << " ";

            if(Aux->left != NULL){
                Q.push(Aux->left);
            }
            if(Aux->right != NULL){
                Q.push(Aux->right);
            }

            Q.pop();

            cout << endl;
            return;
        }
    }
} //complexity o(log n)

void BST::substituteToMin(Node *&root, Node *&apAux){
    if(root->left != NULL){
        substituteToMin(root->left, apAux);
    }
    else{
        //transfer data from substitute node
        apAux->ip = root->ip;
        //save the minValue node (to delete)
        apAux = root;
        //swap place minValue-right (Node or NULL)
        root = root->right;
    }
}//complexity o(log n)

void BST::deleteNode(int &value, Node *&root){
     if (root == NULL){
        cout << "The BST is empty.\n\n";
    }
    else{
        if(value < root->ip){
            deleteNode(value, root->left);
        }
        else if(value > root->ip){
            deleteNode(value, root->right);
        }
        else{
            Node *apAux = root;
            if(apAux->right == NULL){   // only left child node
                root = apAux->left;
            }
            if(apAux->left == NULL){   // only right child node
                root = apAux->right;
            }
            if(apAux->left != NULL && apAux->right != NULL) {//two child nodes
                substituteToMin(root->right, apAux);
            }

            cout << "\nThe key to delete: " << value << endl;
            cout << "The element was deleted with the key: " << apAux->ip << endl;
        }
    }
}//complexity o(n^2)

int BST::height(Node* root){
    if(root == NULL){
        return 0;
    }else{
        int heightLeft = height(root->left);
        int heightRight = height(root->right);

        return max(heightLeft, heightRight) +1;
    }
}//complexity o(n^2)

bool BST::ancestors(Node *root, int data){
    if(root == NULL)
        return false;
    else{
        if(root->ip == data)
            return true;
        else{
            if(ancestors(root->left, data) || ancestors(root->right, data)){
                cout << root->ip << " ";
                return true;
            }
            else
                return false;
        }
    }
}//complexity o(n^2)

int BST::whatLevelAmI(Node* root, int data, int level){
    if(root == NULL){
        return 0;
    }
    else{
        if(root->ip == data){
            return level;
        }else{
            int leftLevel = whatLevelAmI(root->left, data, level + 1);
            int rightLevel = whatLevelAmI(root->right, data, level + 1);
            return max(leftLevel, rightLevel);
        }
    }
}//complexity o(n^2)

int BST::level(Node *root, int data){
    return whatLevelAmI(root, data, 1);
}//complexity o(1)



