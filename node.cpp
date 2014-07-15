#include "node.h"

Node::Node(){
    frequency = 0;
    byte = 0;
    left = 0;
    right = 0;
    position = 0;
}

bool Node::isSingle(){
    bool answer = true;
    if(this->left != 0 && this->right != 0){
        answer = false;
    }
    return answer;
}

bool Node::isLeaf(){
    bool answer = false;
    if(this->left == 0 && this->right == 0){
        answer = true;
    }
    return answer;
}

void Node::incFrequency(int increase){
    this->frequency += increase;
}

int Node::getFrequency() const{
    return this->frequency;
}

void Node::setFrequency(int frequency){
    this->frequency = frequency;
}

unsigned char Node::getByte() const{
    return byte;
}

void Node::setByte(unsigned char byte){
    this->byte = byte;
}

Node *Node::getLeft()const{
    return left;
}

bool Node::isLeft(){
    if(position == 1){
        return true;
    }
    return false;
}

void Node::setLeft(const Node *left){
    this->left = (Node*)left;
}

Node *Node::getRight()const{
    return right;
}

bool Node::isRight(){
    if(position == 2){
        return true;
    }
    return false;
}

void Node::setRight(const Node *right){
    this->right = (Node*)right;
}

void Node::setPosition(int position){
    this->position = position;
}
