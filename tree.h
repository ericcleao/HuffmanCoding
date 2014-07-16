#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <QList>

class Tree
{
    Node *root;
public:
    unsigned char tree[1200];
    Tree();
    Node* getRoot();
    void TreeSort(QList<Node*> *content);
    void fill(QList<Node*> content);
    void print();
    int build(Node *aux, int cont);
};

#endif // TREE_H
