#include "tree.h"
#include <stdio.h>

Tree::Tree()
{
    root = new Node;
}

Node *Tree::getRoot()
{
    return root;
}

void Tree::TreeSort(QList<Node*> *content){
    int pos = content->size() - 1;//tamanho do array
    int i = pos - 1;
    if(i > 1){
        while((content->at(pos)->getFrequency()  < content->at(i)->getFrequency())  ^ (content->at(pos)->getFrequency() == content->at(i)->getFrequency() && content->at(pos)->getByte() < content->at(i)->getByte())){
            printf("%d %d\n", content->at(pos)->getFrequency(), content->at(i)->getFrequency());
            i--;
            if(i <= 0){
                break;
            }
        }
        content->insert(i, content->at(pos));
        content->removeLast();
    }
    printf("b %d %d\n",content->at(0)->getFrequency(), content->at(1)->getFrequency());

}
//    for (i = 1; i < length; i++) {
//        j = i;
//        while (j > 0 && content->at(j - 1).getFrequency() > content->at(j).getFrequency()) {
//            if(content->at(j).getByte() != 0 && content->at(j-1).getByte() != 0){
//                tmp = content->at(j).getFrequency();
//                tmpchar = content->at(j).getByte();
//                content->at(j).setFrequency(content->at(j - 1).getFrequency());
//                content->at(j).setByte(content->at(j - 1).getByte());
//                content->at(j-1).setFrequency(tmp);
//                content->at(j-1).setByte(tmpchar);
//                j--;
//            } else if (content->at(j).getByte() == content->at(j-1).getByte()) {
//            }
//        }
//    }
//}

void Tree::fill(QList<Node*> content){
    while(content.size() > 1){
        root->setFrequency(content.at(0)->getFrequency());
        root->incFrequency(content.at(1)->getFrequency());

        if(content.at(0)->getFrequency() >= content.at(1)->getFrequency()){
            root->setRight(content.at(0));
            content.at(0)->setPosition(2);
            root->setLeft(content.at(1));
            content.at(1)->setPosition(1);
        } else{
            root->setRight(content.at(1));
            content.at(1)->setPosition(2);
            root->setLeft(content.at(0));
            content.at(0)->setPosition(1);
        }

        content.removeFirst();
        content.removeFirst();
        content.append(root);

        if(content.size() > 1){
            root = new Node;
            TreeSort(&content);
        }
    }
}

void Tree::build(){
    printf("\n");
    Node *aux;
    int cont = 0;
    int close = 0;
    representation.insert(0, root);
    aux = root;
    while(representation.size() != 0){
        aux = representation.first();
        representation.removeFirst();

        if(aux->isLeft() && cont > 1){
            tree[cont] = 40;
            printf("%c", 130);

        } if(aux->isLeft() && cont > 1){
            ++close;
        } if(aux->isLeaf()){
            tree[cont] = aux->getByte();
            printf("%c", aux->getByte());
            if(aux->isRight()){
                for(int  i = 0; i < close; ++i, ++cont){
                    tree[cont] = 41;
                    printf("%c", 41);
                }
                printf("%d",close);
                close = 0;
            }
        }
//        printf("%d", cont);
        if(aux->isLeaf() == false){
//            printf("%d %d\n", aux->getFrequency(), aux->getRight()->getFrequency());
            representation.insert(0, aux->getRight());
            representation.insert(0, aux->getLeft());
        }

//        while(aux->isLeaf() == true){
//            aux = representation.pop();
//            printf("%d ", aux->getFrequency());
//        }
        ++cont;
    }
}

//bool lastMove;
//bool nextMove;
//if(!isSingle){
//    nextMove = false;
//    nextNode = node.left; goLeft --- 0 --- "("
//} else{
//    if(isLeaf){
//        nextNode = lastNode;
//        nextMove = !lastMove; gofolha
//    } else if(left != 0){
//        nextMove = false;
//        nextNode = node.left;
//    } else{
//        nextMove = true;
//        nextNode = node.right;
//    }
//}

//void Tree::print()
//{
//    printf("           %d\n", root->getFrequency());
//    printf("         %d  ", root->getLeft()->getFrequency());
//    printf("      %d\n", root->getRight()->getFrequency());

//}


