#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <QList>

class Tree
{
    Node *root;
    QList<Node*> representation;
public:
    unsigned char tree[123];
    Tree();
    Node* getRoot();
    void TreeSort(QList<Node*> *content);
    void fill(QList<Node*> content);
    void print();
    void build();
};

#endif // TREE_H
