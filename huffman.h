#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "file.h"
#include "node.h"
#include "tree.h"
#include "bitvector.h"
#include <QBitArray>

class Huffman
{
    File *file;
    QList<Node*> list;
    BitVector *head;
    int sizeTrash, sizeTree, sizeName;
    QString nameOut;
    unsigned char *representation;
    QBitArray bitCoding;
public:
    Tree *tree;
    Huffman();
    void Compress(QString pathIn, QString pathOut, QString nameOut);
    void Decompress(QString pathIn, QString pathOut);
private:
    QByteArray coding;
    char *QStringtoChar(QString pathOut, QString nameOut, QString type);
    unsigned char bitToChar(QBitArray bit);
};

#endif // HUFFMAN_H
