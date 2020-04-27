#ifndef BARKOCHBA_QUESTION_H
#define BARKOCHBA_QUESTION_H

#include "binarytree.h"

class Question : public BinaryTreeElement {
private:
    BinaryTreeElement* leftTrue;
    BinaryTreeElement* rightFalse;

public:
    Question(const std::string& _text,  BinaryTreeElement* _leftTrue,  BinaryTreeElement* _rightFalse, BinaryTreeElement* _parent = nullptr) :
        BinaryTreeElement(_text, _parent), leftTrue(_leftTrue), rightFalse(_rightFalse) {}
    ~Question() {}

    virtual BinaryTreeElement* getLeftTrue() const { return leftTrue; }
    virtual BinaryTreeElement* getRightFalse() const { return rightFalse; }
    virtual void setLeftTrue(BinaryTreeElement* _left) { leftTrue = _left; }
    virtual void setRightFalse(BinaryTreeElement* _right) { rightFalse = _right; }
    virtual void askQuestion();
};

#endif