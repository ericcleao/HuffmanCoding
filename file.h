#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <QString>
#include <QList>
#include "node.h"

using namespace std;

class File
{
    fstream data;
    QString type;
    unsigned char *bytes;
    long long int size;
    long long int frequency[256][2];
public:
    File();
    void setFile(QString path);
    QList<Node *> getFrequency();
private:
    void findExtension(QString path);
    void sort();
    QList<Node *> toList();
};

#endif // FILE_H
