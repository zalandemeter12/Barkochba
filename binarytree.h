#ifndef BARKOCHBA_BINARYTREE_H
#define BARKOCHBA_BINARYTREE_H

#include <string>
#include "splitqueue.h"

class BinaryTreeElement{
protected:
    std::string text;
    BinaryTreeElement* parent;
public:
    explicit BinaryTreeElement(const std::string& _text, BinaryTreeElement* _parent = nullptr) : text(_text), parent(_parent) {}
    virtual ~BinaryTreeElement() {}

    std::string getText() const { return text; }
    BinaryTreeElement* getParent() const { return parent; }
    virtual BinaryTreeElement* getLeftTrue() const = 0;
    virtual BinaryTreeElement* getRightFalse() const = 0;
    void setParent(BinaryTreeElement* _parent) { parent = _parent; }
    virtual void setLeftTrue(BinaryTreeElement* _left) {}
    virtual void setRightFalse(BinaryTreeElement* _right) {}
    virtual void askQuestion() = 0 ;
    void addQuestion();
    std::string serialize() const;
};

class BinaryTree {
private:
    BinaryTreeElement* root;

public:
    BinaryTree() : root(nullptr) {}
    void freeBinaryTree (BinaryTreeElement* _root);
    ~BinaryTree() { freeBinaryTree(root); };

    BinaryTreeElement* getRoot(){ return root; }
    void newGame();
    void save() const;
    void load();
    BinaryTreeElement* deserializeHelper(SplitQueue& queue, BinaryTreeElement* parent  = nullptr);
    void deserialize(const std::string& s);
};



#endif //BARKOCHBA_BINARYTREE_H
