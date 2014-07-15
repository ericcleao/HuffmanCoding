#include "bitvector.h"

BitVector::BitVector(){
}

void BitVector::SetLast(bool option){
    content.resize(content.size() + 1);
    content.setBit(content.size(), option);
}

void BitVector::Clean(){
    content.fill(false, content.size());
}

