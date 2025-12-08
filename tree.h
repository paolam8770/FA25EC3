//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and TODO comments.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // TODO: Write constructor
    Node(const string &nodeID, const U &value) {
        id = nodeID;
        data = value;
    };
};

template <typename T>
class Tree {
private:
    Node<T>* root;

public:
    // Tree();
    // TODO: Initialize root pointer to nullptr
    Tree(): root(nullptr) {};


    // TODO: Allocate memory, assign id, assign data, set as root
    void createRoot(const string &id, const T &value) {
        if (root != nullptr) {
            return;
        }
        if (root == nullptr) {
            root->children.push_back(new Node<T>(id, value));
            root->id = id;
            root->data = value;
            root = new Node<T>(id, value);
        }
    };

    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents
    void addNode(const string &parentID, const string &childID, const T &value) {
        if (root == nullptr) {
            return;
        }

        Node<T> *parent = new Node<T>(parentID);
        if (parent == nullptr) {
            return;
        }

        Node<T> *child = findNode(childID);
        if (child == nullptr) {
            child = new Node<T>(childID, value);
        }
        parent->children.push_back(child);


    };

    // TODO: Use DFS or BFS to search tree
    Node<T>* findNode(const string &id) {
        Node<T>* curr = root;
            if (curr == nullptr) {
                return nullptr;
            }
            if (curr->id == id) { //reached goal so returns true
                return curr;
            }


            for (int i = 0; i < curr->children.size(); i++) { // loop to compute next row and col
                        //resetting the currs
                        Node<T>* currChild = curr->children[i];

                        // if true getting assigned and calling dfs
                        Node<T>*found  = findNode(currChild, id); // recursive call
                        if (found != nullptr) {
                            return found;
                        }
            }

            return nullptr;
        }




    // TODO: Print entire structure in readable form
    void printAll() {

    };

    ~Tree();
    // TODO: Free all allocated memory
};

#endif //FA25EC3_TREE_H
