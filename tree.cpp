#include "tree.h"
#include <stdio.h>

Tree::Tree()
{
    root = new Node;
    for(int cont = 0; cont < 900; ++cont)
        tree[cont] = '\0';
}

Node *Tree::getRoot()
{
    return root;
}

void Tree::TreeSort(QList<Node*> *content){
    int pos = content->size() - 1;//tamanho do array
    int i = pos - 1;
    if(i >= 0){
        while((content->at(pos)->getFrequency()  < content->at(i)->getFrequency())  ^ (content->at(pos)->getFrequency() == content->at(i)->getFrequency() && content->at(pos)->getByte() < content->at(i)->getByte())){
            i--;
            if(i < 0){
                break;
            }
        }
        content->insert(i+1, content->at(pos));
        content->removeLast();
    }

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

        if(content.at(0)->getFrequency() > content.at(1)->getFrequency()){
//            content.at(0)->encode(true);
            root->setRight(content.at(0));
//            content.at(1)->encode(false);
            root->setLeft(content.at(1));            
        } else{
//            content.at(1)->encode(true);
            root->setRight(content.at(1));
//            content.at(0)->encode(false);
            root->setLeft(content.at(0));
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

int Tree::build(Node *aux, int cont){
    aux->getLeft()->code.resize(aux->code.size());
    aux->getRight()->code.resize(aux->code.size());
    aux->code.resize(aux->code.size() + 1);
    tree[cont] = 40;
    ++cont;
    if(aux->getLeft()->isLeaf()){
        aux->getLeft()->encode(false);
        aux->getLeft()->code |= aux->code;
        if(aux->getLeft()->getByte() != 45 && aux->getLeft()->getByte() != 40 && aux->getLeft()->getByte() != 41){
            tree[cont] = aux->getLeft()->getByte();
        } else{
            tree[cont] = 45;
            ++cont;
            tree[cont] = aux->getLeft()->getByte();
        }
        printf("Code/Byte: ");
        for(int i = 0; i < aux->getLeft()->code.size(); ++i)
        {
            printf("%d", aux->getLeft()->code.at(i));
        }
        printf(" %c\n", aux->getLeft()->getByte());
        ++cont;
    } else{
        aux->getLeft()->encode(false);
        aux->getLeft()->code |= aux->code;
        cont = build(aux->getLeft(), cont);
        ++cont;
    }
    if(aux->getRight()->isLeaf()){
        aux->getRight()->encode(true);
        aux->getRight()->code |= aux->code;
        if(aux->getRight()->getByte() != 45 && aux->getRight()->getByte() != 40 && aux->getRight()->getByte() != 41){
            tree[cont] = aux->getRight()->getByte();
        } else{
            tree[cont] = 45;
            ++cont;
            tree[cont] = aux->getRight()->getByte();
        }
        printf("Code/Byte: ");
        for(int i = 0; i < aux->getRight()->code.size(); ++i)
        {
            printf("%d", aux->getRight()->code.at(i));
        }
        printf(" %c\n", aux->getRight()->getByte());
        ++cont;
    } else{
        aux->getRight()->encode(true);
        aux->getRight()->code |= aux->code;
        cont = build(aux->getRight(), cont);
        ++cont;
    }
    tree[cont] = 41;
    ++cont;
    return cont;
}

//void Tree::build(){
//    printf("\n");
//    Node *aux;
//    int cont = 0;
//    int close = 0;
//    representation.insert(0, root);
//    aux = root;
//    while(representation.size() != 0){
//        aux = representation.first();
//        representation.removeFirst();

//        if(aux->isLeft() && cont > 1){
//            tree[cont] = 40;
//            printf("%c", 130);

//        } if(aux->isLeft() && cont > 1){
//            ++close;
//        } if(aux->isLeaf()){
//            tree[cont] = aux->getByte();
//            printf("%c", aux->getByte());
//            if(aux->isRight()){
//                for(int  i = 0; i < close; ++i, ++cont){
//                    tree[cont] = 41;
//                    printf("%c", 41);
//                }
//                printf("%d",close);
//                close = 0;
//            }
//        }
////        printf("%d", cont);
//        if(aux->isLeaf() == false){
////            printf("%d %d\n", aux->getFrequency(), aux->getRight()->getFrequency());
//            representation.insert(0, aux->getRight());
//            representation.insert(0, aux->getLeft());
//        }

////        while(aux->isLeaf() == true){
////            aux = representation.pop();
////            printf("%d ", aux->getFrequency());
////        }
//        ++cont;
//    }
//}

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


