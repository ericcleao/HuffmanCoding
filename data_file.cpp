#include "data_file.h"

Data_File::Data_File(QString path, QString destiny)
{
    Data_Receive(path);//Passando toda a Data do arquivo para o unsigned char *bytes

    Frequency();//calculando a frequencia dos caracteres de bytes

    SaveData(bytes,destiny,"Test");//copiando arquivo para testar se o mesmo está recebendo todos os dados corretamente

    SaveFrequency(destiny,"Frequency");//salvando a frequência em um arquivo
}

void Data_File::Data_Receive(QString path)
{
    ifstream data(path.toLatin1().data(),ios::binary);//Ler bytes do arquivo

    data.seekg(0,ios::end);//procura o fim do arquivo
    sizeData = data.tellg();//define o tamanho do arquivo como sizeData
    data.seekg(0,ios::beg);//volta para o início do arquivo

    bytes = new unsigned char[sizeData];//declarando o array que portará os bytes
    data.read((char *)bytes,sizeData);//lendo os bytes
    data.close();//fechando o arquivo

}

void Data_File::FindExtension(QString path)

{
    for(int i = path.length(); i > 0; i--)//identificando a extensão do arquivo
    {
        if(path[i] == '.')
        {
            int k = i;
            for(int j = 0; j < path.length() - k; j++, i++){

                type[j] = path[i];//armazenando extensão na QString type

            }
            break;
        }
    }
}

void Data_File::SaveData(unsigned char *data, QString path, QString Name)
{
    char *archive = QstringToChar(path + Name + type);//Unindo o nome do arquivo + a extensão do mesmo + o caminho para salva-lo

    ofstream out(archive);//salvando o arquivo

    for( int i=0 ; i < sizeData ; i++ ){//passando os bytes em formato char para o arquivo

        out << (static_cast<unsigned char>(data[i]));

    }
}

void Data_File::SaveFrequency(QString path, QString Name)
{
    char *archive = QstringToChar(path + Name + ".txt");//Unindo o nome do arquivo + a extensão do mesmo + o caminho para salva-lo

    ofstream out(archive);//salvando o arquivo

    for( int i = 0 ; i < 256 ; i++ )//passando os bytes em formato char para o arquivo
    {

        if((static_cast<int>(data_frequency[i][0])) != 0)
        {

            out << (static_cast<int>(data_frequency[i][0])) << /*"||" << data_frequency[i][1]  << */" ";

        }

    }

    int sum = 0;//verificando soma das frequencias para ver se está com o tamnho total do arquivo

    for( int i = 0; i < 256 ; i++)
    {
        sum += (static_cast<int>(data_frequency[i][0]));
    }

    out << sum;//passando soma para o final do arquivo
}

char *Data_File::QstringToChar(QString toConvert)//conversor de Qstring para char*
{
    QByteArray byteArray = toConvert.toLatin1();
    char *Converted = byteArray.data();

    return Converted;
}

void Data_File::FrequencyToZero()//setando todas as posições do array para zero
{
    for(int i = 0; i < 256; i++)
    {
        data_frequency[i][0] = 0;
    }
}

void Data_File::Frequency()//Calculando a frequencia dos bytes
{
    FrequencyToZero();//setando tudo para zero

    for(int i = 0; i < sizeData; i++)
    {
        data_frequency[bytes[i]][0]++;//acrescentando um na frquencia
        data_frequency[bytes[i]][1] = (int)bytes[i];//salvando o char daquela frequencia
    }
        Sort();//ordenando de forma decrescente
}

void Data_File::Sort()//algoritmo modificado do Insertion Sort, ele ordena as frequencias mantendo seus chars
{
    int length = 256;//tamanho do array
    int i, j ,tmp, tmpchar;
    for (i = 1; i < length; i++) {
        j = i;
        while (j > 0 && data_frequency[j - 1][0] > data_frequency[j][0]) {
            tmp = data_frequency[j][0];
            tmpchar = data_frequency[j][1];
            data_frequency[j][0] = data_frequency[j - 1][0];
            data_frequency[j][1] = data_frequency[j - 1][1];
            data_frequency[j - 1][0] = tmp;
            data_frequency[j - 1][1] = tmpchar;
            j--;
        }
    }
}

QList<Node*> Data_File::toList()
{
    QList<Node*> list;

    for(int i = 0; i < 256; i ++)
    {
        if(data_frequency[i][0] != 0 && data_frequency[i][1] != 10 && data_frequency[i][1] != 13)
        {
            Node *node = new Node;
            node->setFrequency(data_frequency[i][0]);
            node->setByte(data_frequency[i][1]);
            list.append(node);
        }
    }

    return list;
}
