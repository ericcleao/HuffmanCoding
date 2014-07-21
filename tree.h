#ifndef TREE_H
#define TREE_H

#include <QList>
#include "node.h"
#include "file.h"

class Tree
{
    Node *root;
    unsigned char *representation;
public:
    Tree();
    Node* getRoot();
    void TreeSort(QList<Node*> *content);
    void fill(QList<Node*> content);
    int make(File *file, Node *aux, int current);
    void unmake(Node *aux, unsigned char *representation, int start, int end);
    unsigned char *getRep();
private:
    int findRight(unsigned char *representation, int current, int size);
};

#endif // TREE_H
