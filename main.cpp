#include "tree.h"
#include "file.h"
#include "bitvector.h"
#include"huffman.h"
#include <iostream>

using namespace std;

void printTree(Node* node, Node*comp, int level)
{
    if(node->getLeft()!= NULL)
    {
        printTree(node->getLeft(), comp->getLeft(), level +1);
    }
    cout << qPrintable(QString("\t").repeated(level)) <<"."<< (int)node->getByte() << " " << (int)comp->getByte() <<endl;
    if(node->getRight()!= NULL)
    {
        printTree(node->getRight(), comp->getRight(), level +1);
    }
}

int main()
{

//    Data_File file("..\\HuffmanCoding\\Arquivos\\black.png","../Project/Test/");//Testando com Imagem
//    Data_File file("..\\HuffmanCoding\\Arquivos\\final.wav","../Project/Test/");//Testando com Musica Pequena
//    Data_File file("..\\HuffmanCoding\\Arquivos\\Nothing Else Matters.mp3","../Project/Test/");//Testando com Musica Grande
//    File *file = new File;
//    file->setFile("..\\HuffmanCoding\\Test\\test.txt");
//    file->setFile("..\\HuffmanCoding\\Arquivos\\test.mp3");
//    file->setFile("..\\HuffmanCoding\\Arquivos\\Nothing Else Matters.mp3");
//    file->setFile("..\\HuffmanCoding\\Arquivos\\in.txt");
//    QList<Node*> list = file->getFrequency();

//    for(int cont = 0; cont < list.size(); ++cont){
//        cout << list.at(cont)->getFrequency() << " " << list.at(cont)->getByte() << endl;
//    }
    Huffman test1, test2;
//    test1.Compress("..\\HuffmanCoding\\Arquivos\\pedro.png", "..\\HuffmanCoding\\Test\\", "test");
    test1.Compress("..\\HuffmanCoding\\Arquivos\\in.txt", "..\\HuffmanCoding\\Test\\", "test");
    test2.Decompress("..\\HuffmanCoding\\Test\\test.huff", "..\\HuffmanCoding\\Test\\out.png");
    cout << endl;
    printTree(test1.tree->getRoot(),test2.tree->getRoot(), 0);
    cout << "----------------------------------------------------------------------------" << endl;

////    Descomprimindo eric cerqueira;
//    cout << endl << test1.tree->getRoot()->getLeft()->getLeft()->getByte();
//    cout << endl << test1.tree->getRoot()->getLeft()->getRight()->getByte();
//    cout << endl << test1.tree->getRoot()->getRight()->getLeft()->getLeft()->getLeft()->getByte();
//    cout << endl << test1.tree->getRoot()->getRight()->getLeft()->getLeft()->getRight()->getByte();
//    cout << endl << test1.tree->getRoot()->getRight()->getLeft()->getRight()->getLeft()->getByte();
//    cout << endl << test1.tree->getRoot()->getRight()->getLeft()->getRight()->getRight()->getByte();
//    cout << endl << test1.tree->getRoot()->getRight()->getRight()->getLeft()->getByte();
//    cout << endl << test1.tree->getRoot()->getRight()->getRight()->getRight()->getByte();

//    test.fill(list);
//    cout << test.getRoot()->getFrequency() << " " << test.getRoot()->getLeft()->getFrequency() << " " << test.getRoot()->getRight()->getFrequency();
//    int max = test.build(test.getRoot(), 0);
//    cout << "   " << test.getRoot()->getFrequency() << endl << test.getRoot()->getLeft()->getByte() <<"     "<<  test.getRoot()->getRight()->getFrequency() << endl;
//    cout << "    " << test.getRoot()->getRight()->getLeft()->getByte() << "   " << test.getRoot()->getRight()->getRight()->getByte() << endl;
//    int max = test.build(file, test.getRoot(), 0);
//    file->output("..\\HuffmanCoding\\Test\\", "test2", test.getRep, max);
//    int test1 = 0, test2 = 0;
//    for(int cont = 0; cont < max; ++cont){
//        if(test.tree[cont] == 40 && test.tree[cont - 1] != 45){
//            ++test1;
//        }
//        if(test.tree[cont] == 41 && test.tree[cont - 1] != 45){
//            ++test2;
//        }
//        cout << test.tree[cont];
//    }
//    cout << '\n' << max << endl;
//    cout << test1 << " " << test2 << endl;
    //    test.print();
//    long teste[4][2] = {{1,82},{1,83},{2,67},{3,65}};
//    cout << teste[0][0] << " " << (char)teste[2][1] << endl;

//    Tree test;

//    test.fill(teste);

//    test.print();
    return 0;
}
