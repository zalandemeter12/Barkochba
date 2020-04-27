#ifndef BARKOCHBA_GUESS_H
#define BARKOCHBA_GUESS_H

#include "binarytree.h"

class Guess : public BinaryTreeElement{
private:
public:
    explicit Guess(const std::string& _text, BinaryTreeElement* _parent = nullptr) :
        BinaryTreeElement(_text,_parent){}
    ~Guess() {}

    virtual BinaryTreeElement* getLeftTrue() const { return nullptr; }
    virtual BinaryTreeElement* getRightFalse() const { return nullptr; }
    virtual void askQuestion();
};

#endif