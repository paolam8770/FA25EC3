//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

    Node<T>* DFS(Node<T>* curr, const string &id, unordered_set<Node<T>*>& visited) {
        if (curr == nullptr) {
            return nullptr;
        }
        if (visited.count(curr)) {
            return nullptr;
        }
        if (curr->id == id) {
            return curr;
        }

        for (Node<T>* child: curr->children) {
            Node<T>* found = DFS(child, id, visited);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }

    void printDFS(Node<T>* curr, int depth, unordered_set<Node<T>*>& visited) {
        if (curr == nullptr || visited.count(curr)) {
            return;
        }
        visited.insert(curr);

        for (int i=0; i < depth; i++) {
            cout<< " ";
        }
        cout << curr->id << ": " << curr->data << endl;

        for (Node<T>* child: curr->children) {
            printDFS(child, depth + 1, visited);
        }
    }

    void destroyTree(Node<T>* curr, unordered_set<Node<T>*>& visited) {
        if (curr == nullptr || visited.count(curr)) {
            return;
        }

        visited.insert(curr);

        for (Node<T>* child: curr->children) {
            destroyTree(child, visited);
        }
        delete curr;
    }


public:
    // Tree();
    // TODO: Initialize root pointer to nullptr
    Tree(): root(nullptr) {};


    // TODO: Allocate memory, assign id, assign data, set as root
    void createRoot(const string &id, const T &value) {
        if (root != nullptr) {
            // if root already exists return
            return;
        }
        root = new Node<T>(id, value);
    };

    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents
    void addNode(const string &parentID, const string &childID, const T &value) {
        if (root == nullptr) {
            return;
        }

        //find parent in existing tree
        unordered_set<Node<T>*> visitedParent;
        Node<T>* parent = DFS(root, parentID, visitedParent);
        if (parent != nullptr) {
            return;
        }

        // check if child already exists
        unordered_set<Node<T>*> visitedChildren;
        Node<T>* child = DFS(root, childID, visitedChildren);
        if (child == nullptr) {
            child = new Node<T>(childID, value);
        }

        // link parent to child
        parent->children.push_back(child);

    };

    // TODO: Use DFS or BFS to search tree
    Node<T>* findNode(const string &id) {
        Node<T>* curr = root;
        if (curr == nullptr) {
            return nullptr;
        }
        unordered_set<Node<T>*> visited;
        return DFS(root, id, visited);
    }



    // TODO: Print entire structure in readable form
    void printAll() {
        if (root == nullptr) {
            return;
        }
        unordered_set<Node<T>*> visited;
        printDFS(root,0,visited);
    };


    // TODO: Free all allocated memory
    ~Tree() {
        unordered_set<Node<T>*> visited;
        destroyTree(root, visited);
        root = nullptr;
    };

    void playGame() {
        if (root == nullptr) {
            return;
        }
        Node<T>* curr = root;

        while (curr != nullptr) {
            cout << "\n" << curr->data << "\n"; // showing curr text

            if (curr->children.empty()) {
                cout << "\n End \n"; // if no children end
                break;
            }
            cout << "\n Options: \n";
            for (size_t i = 0; i < curr->children.size(); i++) {
                cout << " "<< (i+1) << ") Go to " << curr->children[i]->id << "\n";
            }

            int choice =0;
            while (true) {
                cout << "Enter your choice: (1- " << curr->children.size() << "):";
                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (choice < 1 || static_cast<size_t>(choice) > curr->children.size()) {
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            curr = curr->children[choice-1];

        }
    }

};

#endif //FA25EC3_TREE_H
