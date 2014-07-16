#include "file.h"
#include "tree.h"
#include <iostream>

using namespace std;
int main()
{
//    Data_File file("..\\HuffmanCoding\\Arquivos\\black.png","../Project/Test/");//Testando com Imagem
//    Data_File file("..\\HuffmanCoding\\Arquivos\\final.wav","../Project/Test/");//Testando com Musica Pequena
//    Data_File file("..\\HuffmanCoding\\Arquivos\\Nothing Else Matters.mp3","../Project/Test/");//Testando com Musica Grande
    File *file = new File;
//    file->setFile("..\\HuffmanCoding\\Arquivos\\black.png");
//    file->setFile("..\\HuffmanCoding\\Arquivos\\codeblocks-13.12mingw-setup.exe");
    file->setFile("..\\HuffmanCoding\\Arquivos\\in.txt");
    QList<Node*> list = file->getFrequency();

    for(int cont = 0; cont < list.size(); ++cont){
        cout << list.at(cont)->getFrequency() << " " << list.at(cont)->getByte() << endl;
    }

    Tree test;
    test.fill(list);
//    cout << test.getRoot()->getFrequency() << " " << test.getRoot()->getLeft()->getFrequency() << " " << test.getRoot()->getRight()->getFrequency();
    int max = test.build(test.getRoot(), 0);
//    cout << "   " << test.getRoot()->getFrequency() << endl << test.getRoot()->getLeft()->getByte() <<"     "<<  test.getRoot()->getRight()->getFrequency() << endl;
//    cout << "    " << test.getRoot()->getRight()->getLeft()->getByte() << "   " << test.getRoot()->getRight()->getRight()->getByte() << endl;
    int test1 = 0, test2 = 0;
    for(int cont = 0; cont < max; ++cont){
        if(test.tree[cont] == 40 && test.tree[cont - 1] != 45){
            ++test1;
        }
        if(test.tree[cont] == 41 && test.tree[cont - 1] != 45){
            ++test2;
        }
        cout << test.tree[cont];
    }
    cout << '\n' << max << endl;
    cout << test1 << " " << test2 << endl;
    //    test.print();
//    long teste[4][2] = {{1,82},{1,83},{2,67},{3,65}};
//    cout << teste[0][0] << " " << (char)teste[2][1] << endl;

//    Tree test;

//    test.fill(teste);

//    test.print();
    return 0;
}
