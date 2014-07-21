#include "file.h"

File::File(){
    coding = new QBitArray[256];
    for(int i = 0; i < 256; i++){
        frequency[i][0] = 0;
    }

}

void File::setFile(QString path){
    fstream data(path.toLatin1().data(), ios::in | ios::binary | ios::ate);//Ler bytes do arquivo
    sizeIn = data.tellg();//define o tamanho do arquivo como sizeData
    data.seekg(0,ios::beg);//volta para o início do arquivo
//    cout << "Size: " << sizeIn << endl;
    try
    {
        bytes = new unsigned char [sizeIn];//declarando o array que portará os bytes
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }

    data.read((char *)bytes,sizeIn);//lendo os bytes
    data.close();//fechando o arquivo

    sizeName = findName(path);
    findType(path);
}

//void File::output(QString path, QString Name, unsigned char tree[], int sizeTree){
//    QByteArray aux = (path + Name + ".txt").toLatin1();//Unindo o nome do arquivo + a extensão do mesmo + o caminho para salva-lo
//    QBitArray temp;
//    temp.resize(8);
//    char *archive = aux.data();
////    puts(archive);
//    ofstream out(archive);//salvando o arquivo
//    int sizeTrash = 0, k = 0;
//    BitVector head;
//    for(int cont = 0; cont < 24; ++cont){
//        out << 0;
//    }
//    out << qPrintable(this->nameIn);
//    for(int cont = 0; cont < sizeTree; ++cont){
//        out << tree[cont];
//    }
//    for(int i = 0; i < sizeIn; i++){
//        for(int j = 0; j < getCode(bytes[i]).size(); ++j, ++k){
//            temp.setBit(k%8, getCode(bytes[i]).at(j));

//            if(k%8 == 7){
//                out << bitToChar(temp);
//                k = -1;
//                temp.fill(0, 8);
//            }

//            ++sizeTrash;
//        }
//        if(sizeTrash%1000 > 0){
//            sizeTrash -= (int)(sizeTrash/100)*100;
//        }

//    }
//    if(sizeTrash%8 != 0){
//        sizeTrash = 8 - sizeTrash%8;
//        out << bitToChar(temp);
//    } else{
//        sizeTrash = 0;
//    }

//    out.seekp(0, ios::beg);
//    head.fillSizes(QString::number(sizeTrash), QString::number(sizeTree), QString::number(sizeName));
//    for(int cont = 0; cont < 24; ++cont){
//        out << head.getSizes().at(cont);
//    }
//    out.close();
//}

int File::findName(QString path){
    int size = 0;
    for(int i = path.length(); i > 0; i--)//identificando a extensão do arquivo
    {
        if(path[i] == '\\'){
            ++i;
            int k = i;
            for(int j = 0; j < path.length() - k; j++, i++){
                nameIn[j] = path[i];//armazenando extensão na QString type
                ++size;
            }
            return size;
        }
    }
}

void File::findType(QString path){
    for(int i = path.length(); i > 0; i--)//identificando a extensão do arquivo
    {
        if(path[i] == '.'){
            ++i;
            int k = i;
            for(int j = 0; j < path.length() - k; j++, i++){
                typeIn[j] = path[i];//armazenando extensão na QString type
            }
            break;
        }
    }
}

void File::setCode(QBitArray code, unsigned char byte){
    coding[byte].resize(code.size());
    coding[byte] |= code;
}

QBitArray File::getCode(unsigned char byte){
    return coding[byte];
}

QString File::getNameIn(){
    return this->nameIn;
}

long long File::getSizeIn(){
    return this->sizeIn;
}

unsigned char *File::getBytes(){
    return this->bytes;
}

long long File::getSizeName(){
    return this->sizeName;
}

QList<Node*> File::getFrequency(){
    for(int i = 0; i < sizeIn; i++){
        frequency[bytes[i]][0]++;//acrescentando um na frquencia
        frequency[bytes[i]][1] = (int)bytes[i];//salvando o char daquela frequencia
    }

    sort();//ordenando de forma decrescente
    return toList();
}

void File::sort()//algoritmo modificado do Insertion Sort, ele ordena as frequencias mantendo seus chars
{
    int length = 256;//tamanho do array
    int i, j ,tmp, tmpchar;
    for (i = 1; i < length; i++) {
        j = i;
        while (j > 0 && frequency[j - 1][0] > frequency[j][0]) {
            tmp = frequency[j][0];
            tmpchar = frequency[j][1];
            frequency[j][0] = frequency[j - 1][0];
            frequency[j][1] = frequency[j - 1][1];
            frequency[j - 1][0] = tmp;
            frequency[j - 1][1] = tmpchar;
            j--;
        }
    }
}

QList<Node*> File::toList()
{
    QList<Node*> list;

    for(int i = 0; i < 256; i ++)
    {
        if(frequency[i][0] != 0 && frequency[i][1] != 10 && frequency[i][1] != 13)
        {
            Node *node = new Node;
            node->setFrequency(frequency[i][0]);
            node->setByte(frequency[i][1]);
            list.append(node);
        }
    }

    return list;
}
