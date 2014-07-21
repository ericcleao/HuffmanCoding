#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <QBitArray>
#include <QString>

class BitVector
{
   QBitArray content;
   QBitArray sizes;
   QString trash, tree, name;
public:
    BitVector();
    void Clean();
    void setLast(bool option);
    void fillSizes(QString trash, QString tree, QString name);
    QBitArray getSizes();
};

#endif // BITVECTOR_H
