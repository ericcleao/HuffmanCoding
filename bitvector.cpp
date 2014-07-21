#include "bitvector.h"

BitVector::BitVector(){
    sizes.resize(24);
    sizes.fill(false,24);
}

void BitVector::Clean(){
    content.fill(false, content.size());
}

void BitVector::setLast(bool option){
    content.resize(content.size() + 1);
    content.setBit(content.size(), option);
}


void BitVector::fillSizes(QString trash, QString tree, QString name){
    int tra = 0, tre = 0, nam = 0;
    bool ok = false;
    this->trash = QString::number(trash.toLongLong(&ok, 10), 2);
    this->tree = QString::number(tree.toLongLong(&ok, 10), 2);
    this->name = QString::number(name.toLongLong(&ok, 10), 2);

//    printf("%d %d %d\n", this->trash.toInt(&ok, 10), this->tree.toInt(&ok, 10), this->name.toInt(&ok, 10));/* << this->trash << " " << this->tree << " " << this->name << endl;*/

    if(this->trash.size() < 3){
        tra = 3 - this->trash.size();
    }
    if(this->tree.size() < 13){
        tre = 13 - this->tree.size();
    }
    if(this->name.size() < 8){
        nam = 8 - this->name.size();
    }

    for(int pos = 0; pos < 24; ++pos){
        if(pos < 3){
            if(tra <= 0){
                if((int)this->trash.at(pos - (3 - this->trash.size())).toLatin1() == 48){
                    sizes.setBit(pos, false);
                } else if ((int)this->trash.at(pos - (3 - this->trash.size())).toLatin1() == 49){
                    sizes.setBit(pos, true);
                }
            } else{
                sizes.setBit(pos, 0);
            }
            --tra;
        } else if(pos < 16){
            if(tre <= 0){
                if((int)this->tree.at(pos - 3 - (13 - this->tree.size())).toLatin1() == 48){
                    sizes.setBit(pos, false);
                } else if((int)this->tree.at(pos - 3 - (13 - this->tree.size())).toLatin1() == 49){
                    sizes.setBit(pos, true);
                }
            } else{
                sizes.setBit(pos, 0);
            }
            --tre;
        } else{
            if(nam <= 0){
                if((int)this->name.at(pos - 16 - (8 - this->name.size())).toLatin1() == 48){
                    sizes.setBit(pos, false);
                } else if ((int)this->name.at(pos - 16 - (8 - this->name.size())).toLatin1() == 49){
                    sizes.setBit(pos, true);
                }
            } else{
                sizes.setBit(pos, 0);
            }
            --nam;
        }
//        printf("%d", sizes.at(pos));
    }
//    printf("\n");
}

QBitArray BitVector::getSizes(){
    return sizes;
}

