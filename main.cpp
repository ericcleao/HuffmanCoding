#include "data_file.h"
#include "tree.h"
#include <iostream>

using namespace std;
int main()
{
//    Data_File file("../Project/Arquivos/black.png","../Project/Test/");//Testando com Imagem
//    Data_File file("../Project/Arquivos/final.wav","../Project/Test/");//Testando com Musica Pequena
//    Data_File file("../Project/Arquivos/Nothing Else Matters.mp3","../Project/Test/");//Testando com Musica Grande
    Data_File file("../Project/Arquivos/in.txt","../Project/Test/");//Testando com Texto

    QList<Node*> list = file.toList();

    for(int cont = 0; cont < list.size(); ++cont){
        cout << list.at(cont)->getFrequency() << " " << list.at(cont)->getByte() << endl;
    }

    Tree test;

    test.fill(list);
    test.build();
//    cout << "   " << test.getRoot()->getFrequency() << endl << test.getRoot()->getLeft()->getByte() <<"     "<<  test.getRoot()->getRight()->getFrequency() << endl;
//    cout << "    " << test.getRoot()->getRight()->getLeft()->getByte() << "   " << test.getRoot()->getRight()->getRight()->getByte() << endl;
    cout << test.tree;
    //    test.print();
//    long teste[4][2] = {{1,82},{1,83},{2,67},{3,65}};
//    cout << teste[0][0] << " " << (char)teste[2][1] << endl;

//    Tree test;

//    test.fill(teste);

//    test.print();
    return 0;
}
