#include "file.h"

File::File(){
    for(int i = 0; i < 256; i++){
        frequency[i][0] = 0;
    }

}

void File::setFile(QString path){
    fstream data(path.toLatin1().data(), ios::in | ios::binary | ios::ate);//Ler bytes do arquivo
    size = data.tellg();//define o tamanho do arquivo como sizeData
    data.seekg(0,ios::beg);//volta para o início do arquivo
    cout << "Size: " << size << endl;
    try
    {
        bytes = new unsigned char [size];//declarando o array que portará os bytes
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }

    data.read((char *)bytes,size);//lendo os bytes
    data.close();//fechando o arquivo

    findExtension(path);
}

void File::findExtension(QString path){
    for(int i = path.length(); i > 0; i--)//identificando a extensão do arquivo
    {
        if(path[i] == '.'){
            int k = i;
            for(int j = 0; j < path.length() - k; j++, i++){
                type[j] = path[i];//armazenando extensão na QString type

            }
            break;
        }
    }
}

QList<Node*> File::getFrequency(){
    for(int i = 0; i < size; i++){
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
