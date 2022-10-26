#ifndef NODE_H
#define NODE_H
#include <cstddef>
#include <iostream>

using namespace std;

class Node
{
    public:
        Node(double data, string tx): ip(data), left(NULL), right(NULL), text(tx){}
        Node() : ip(0), left(NULL), right(NULL), text(""){}
        Node(double data) : ip(data), left(NULL), right(NULL), text(""){}
        double ip;
        string text;
        Node *left;
        Node *right;
};

#endif