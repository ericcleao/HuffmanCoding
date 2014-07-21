#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <QString>
#include <QList>
#include <QBitArray>
#include <math.h>
#include "node.h"
#include "bitvector.h"

using namespace std;

class File
{
    fstream data;
    QString nameIn;
    QString typeIn;
    unsigned char *bytes;
    long long int sizeIn, sizeName;
    long long int frequency[256][2];
    QBitArray *coding;
public:
    File();
    void setFile(QString path);
    void output(QString path, QString Name, unsigned char tree[], int sizeTree);
    QList<Node *> getFrequency();
    void setCode(QBitArray code, unsigned char byte);
    QBitArray getCode(unsigned char byte);
    QString getNameIn();
    QString getTypeIn();
    long long int getSizeIn();
    unsigned char bitToChar(QBitArray bit);
    unsigned char *getBytes();
    long long int getSizeName();
private:
    int findName(QString path);
    void findType(QString path);
    void sort();
    QList<Node *> toList();
};

#endif // FILE_H
