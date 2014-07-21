#include "tree.h"
#include <stdio.h>

Tree::Tree()
{
    root = new Node;
    representation = new unsigned char[1200];
    for(int cont = 0; cont < 900; ++cont)
        representation[cont] = '\0';
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
            root->setRight(content.at(0));
            root->setLeft(content.at(1));            
        } else{
            root->setRight(content.at(1));
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

int Tree::make(File *file, Node *aux, int current){
    aux->getLeft()->code.resize(aux->code.size());
    aux->getRight()->code.resize(aux->code.size());
    aux->code.resize(aux->code.size() + 1);
    if(aux != root){
        representation[current] = 40;
        ++current;
    }
    if(aux->getLeft()->isLeaf()){
        aux->getLeft()->encode(false);
        aux->getLeft()->code |= aux->code;
        if(aux->getLeft()->getByte() != 45 && aux->getLeft()->getByte() != 40 && aux->getLeft()->getByte() != 41){
            representation[current] = aux->getLeft()->getByte();
        } else{
            representation[current] = 45;
            ++current;
            representation[current] = aux->getLeft()->getByte();
        }
//        printf("Code/Byte: ");
//        for(int i = 0; i < aux->getLeft()->code.size(); ++i)
//        {
//            printf("%d", aux->getLeft()->code.at(i));
//        }
//        printf(" %c\n", aux->getLeft()->getByte());
        file->setCode(aux->getLeft()->code, aux->getLeft()->getByte());
        ++current;
    } else{
        aux->getLeft()->encode(false);
        aux->getLeft()->code |= aux->code;
        current = make(file, aux->getLeft(), current);
        ++current;
    }
    if(aux->getRight()->isLeaf()){
        aux->getRight()->encode(true);
        aux->getRight()->code |= aux->code;
        if(aux->getRight()->getByte() != 45 && aux->getRight()->getByte() != 40 && aux->getRight()->getByte() != 41){
            representation[current] = aux->getRight()->getByte();
        } else{
            representation[current] = 45;
            ++current;
            representation[current] = aux->getRight()->getByte();
        }
//        printf("Code/Byte: ");
//        for(int i = 0; i < aux->getRight()->code.size(); ++i)
//        {
//            printf("%d", aux->getRight()->code.at(i));
//        }
//        printf(" %c\n", aux->getRight()->getByte());
        file->setCode(aux->getRight()->code, aux->getRight()->getByte());
        ++current;
    } else{
        aux->getRight()->encode(true);
        aux->getRight()->code |= aux->code;
        current = make(file, aux->getRight(), current);
        ++current;
    }
    representation[current] = 41;
    return current;
}

void Tree::unmake(Node *aux, unsigned char *representation, int start, int end){
    if(end <= start){
        return;
    }
    if(aux->getLeft() == 0){
        aux->setLeft(new Node);
    }
    if(aux->getRight() == 0){
        aux->setRight(new Node);
    }
    cout << "s" << start << "|" << "e" << end << endl;

    if(representation[start] == 40){
        int i = findRight(representation, start, end);
        cout << "i = " <<  i << endl;
        if(i < end - 1){
            unmake(aux->getLeft(), representation, start, i);
            if(i  != end - 2){
                unmake(aux->getRight(), representation, i+1, end);
            } else{
                cout << "Exception2 = " << representation[i+1] << endl;
                aux->getRight()->setByte(representation[i+1]);
            }
        } else if(i == end){
            unmake(aux,representation,start + 1, end);
        } else{
            if(representation[end] != 41){
                cout << "Exception = " << representation[end] << endl;
                aux->getRight()->setByte(representation[end]);
                unmake(aux->getLeft(),representation,start, i);
            } else{
                if(start - end > 3){
                    unmake(aux->getRight(),representation,start, i);
                } else{
                    unmake(aux,representation,start, i);
                }
            }
        }
    } else if(representation[start] != 41){
        if(representation[start] == 45){
            ++start;
        }
        if(aux->getLeft()->getByte() == 0){
            cout << "Left = " << representation[start] << endl;
            aux->getLeft()->setByte(representation[start]);
            if(representation[start + 1] != 40){
                unmake(aux,representation,start + 1,end);
            } else{
                unmake(aux->getRight(),representation,start + 1,end);
            }
        } else if(aux->getRight()->getByte() == 0){
            cout << "Right = " << representation[start] << endl;
            aux->getRight()->setByte(representation[start]);
        }
    }
}

int Tree::findRight(unsigned char *representation, int current, int size){
    int open = 0, close = 0;
    for(int cont = current; cont <= size;++cont){
        if(representation[cont] == 40 && (cont == 0 || representation[cont - 1] != 45)){
            ++open;
        } else if(representation[cont] == 41 && (cont == 0 || representation[cont - 1] != 45)){
            ++close;
        }

        if(open - close == 0){
            return cont;
        }
    }

    cout << "error2!!";
    return size + 1;
}

unsigned char *Tree::getRep(){
    return this->representation;
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


