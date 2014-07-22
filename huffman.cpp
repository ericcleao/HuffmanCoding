#include "huffman.h"

Huffman::Huffman(){
    file = new File;
    tree = new Tree;
    head = new BitVector;
    sizeTrash = 0;
    sizeTree = 0;
    sizeName = 0;
    nameOut = "";
    representation = new unsigned char[1200];
    coding = "";
}

void Huffman::compress(QString pathIn, QString pathOut, QString nameOut){
    file->setFile(pathIn);
    list = file->getFrequency();
    tree->fill(list);
    sizeTree = tree->make(file, tree->getRoot(), 0);

    ofstream out(qStringtoChar(pathOut, nameOut, "huff"));

    QBitArray temp;
    temp.resize(8);

    for(int cont = 0; cont < 3; ++cont){
        out << 0;
    }

    out << qPrintable(file->getNameIn());

    for(int cont = 0; cont < sizeTree; ++cont){
        out << tree->getRep()[cont];
    }

    for(int i = 0, k = 0; i < file->getSizeIn(); i++){
        for(int j = 0; j < file->getCode(file->getBytes()[i]).size(); ++j, ++k){
            temp.setBit(k%8, file->getCode(file->getBytes()[i]).at(j));
            if(k%8 == 7){
                out << bitToChar(temp);
                k = -1;
                temp.fill(0, 8);
            }

            ++sizeTrash;
        }
        if(sizeTrash%1000 == 0){
            sizeTrash -= (int)(sizeTrash/1000)*1000;
        }

    }
    if(sizeTrash%8 != 0){
        sizeTrash = 8 - sizeTrash%8;
        out << bitToChar(temp);
        temp.fill(0, 8);
    } else{
        sizeTrash = 0;
    }

    out.seekp(0, ios::beg);
    head->fillSizes(QString::number(sizeTrash), QString::number(sizeTree), QString::number(file->getSizeName()));
    for(int cont = 0, k = 0; cont < 24; ++cont, ++k){
        temp.setBit(k%8, head->getSizes().at(cont));
        if(cont%8 == 7){
            out << bitToChar(temp);
            k = -1;
            temp.fill(0, 8);
        }
    }

    out.close();
}

char *Huffman::qStringtoChar(QString pathOut, QString nameOut, QString type){
    QByteArray archive = (pathOut + nameOut + "." + type).toLatin1();//Unindo o nome do arquivo + a extensão do mesmo + o caminho para salva-lo
    return archive.data();
}

unsigned char Huffman::bitToChar(QBitArray bit){
    int character = 0;
    for(int cont = 0; cont < 8; ++cont){
        character += bit.at(cont)*pow(2,7-cont);
    }
    return character;
}

void Huffman::decompress(QString pathIn, QString pathOut){
    file->setFile(pathIn);

    for(int cont = 0; cont < 24; ++cont){
        if(cont < 3){
           this->sizeTrash += (file->getBytes()[cont] - 48)*pow(2,2-cont);
        } else if(cont < 16){
            this->sizeTree += (file->getBytes()[cont] - 48)*pow(2,12 - (cont - 3));
        } else{
            this->sizeName += (file->getBytes()[cont] - 48)*pow(2,7 - (cont - 16));
        }
    }
//    cout << sizeTrash << " " << sizeTree << " " << sizeName << endl;

    head->fillSizes(QString::number(sizeTrash), QString::number(sizeTree), QString::number(sizeName));

    for(int cont = 24; cont < 24 + sizeName; ++cont){
        nameOut += file->getBytes()[cont];
    }

//    cout << qPrintable(nameOut) << endl;

    for(int cont = 24 + sizeName; cont < 24 + sizeName + sizeTree; ++cont){
        representation[cont - (24 + sizeName)] = file->getBytes()[cont];
    }

    int open = 0, close = 0;
    for(int cont = 0; cont < sizeTree;++cont){
        if(representation[cont] == 40 && (cont == 0 || representation[cont - 1] != 45)){
            ++open;
        } else if(representation[cont] == 41 && (cont == 0 || representation[cont - 1] != 45)){
            ++close;
        }
    }

//    cout << open << " " << close << endl;

//    cout << representation << endl;

    for(int cont = 24 + sizeName + sizeTree, k = 0; cont < file->getSizeIn(); ++cont){
        int temp = cont - (23 + sizeName + sizeTree);
        bitCoding.resize(8+k);
        for(int i = 8 + k - 1; i >=  8*(temp - 1); --i, ++k){
            bitCoding.setBit(k, file->getBytes()[cont]&(1<<i%8));
        }
    }

    bitCoding.resize(bitCoding.size() - sizeTrash);

//    for(int cont = 0; cont < bitCoding.size(); ++cont){
//        cout << bitCoding.at(cont);
//    }
//    cout << endl;
//    cout << sizeTree << " " << bitCoding.size() << endl;
    tree->unmake(tree->getRoot(), representation, 0, sizeTree - 1);

    ofstream out(pathOut.toLatin1().data(), ios::out | ios::binary);

    Node *current = tree->getRoot();
//    cout << bitCoding.size();
    for(int cont = 0; cont < bitCoding.size(); ++cont){
        if(!current->isLeaf()){
            if(bitCoding.at(cont) == false){
                if(current->getLeft() != 0){
                    current = current->getLeft();
                }
            } else{
                if(current->getRight() != 0){
                    current = current->getRight();
                }
            }
        }
        if(current->isLeaf()){
            out << current->getByte();
            current = tree->getRoot();
        }
    }

    out.close();
}
