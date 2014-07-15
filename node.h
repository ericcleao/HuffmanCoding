#ifndef NODE_H
#define NODE_H

class Node
{
    int frequency;
    unsigned char byte;
    Node *right;
    Node *left;
    char position;
public:
    Node();
    bool isSingle();
    bool isLeaf();
    void incFrequency(int increase);
    int getFrequency() const;
    void setFrequency(int frequency);
    unsigned char getByte()const ;
    void setByte(unsigned char byte);
    Node *getLeft() const;
    bool isLeft();
    void setLeft(const Node *left);
    Node *getRight() const;
    bool isRight();
    void setRight(const Node *right);
    void setPosition(int position);
};

#endif // NODE_H
