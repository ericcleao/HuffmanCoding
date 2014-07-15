#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <QByteArray>
#include <QList>
#include <QString>
#include <iostream>
#include <fstream>

#include "node.h"

using namespace std;

class Data_File
{
public:

    Data_File(QString path, QString destiny);

    void Data_Receive(QString path);
    void FindExtension(QString path);
    void SaveData(unsigned char *data, QString path, QString Name);
    void SaveFrequency(QString path, QString Name);
    char *QstringToChar(QString toConvert);
    void FrequencyToZero();
    void Frequency();
    void Sort();
    QList<Node*> toList();

private:

    long sizeData;
    unsigned char *bytes;
    long int data_frequency[256][2];
    QString type;

};

#endif // DATA_FILE_H
