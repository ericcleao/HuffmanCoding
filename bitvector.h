#ifndef BITVECTOR_H
#define BITVECTOR_H
#include <QBitArray>

class BitVector
{
   QBitArray content;
public:
    BitVector();
    void Clean();
    void SetLast(bool option);
};

#endif // BITVECTOR_H
