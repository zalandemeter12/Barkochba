#ifndef BARKOCHBA_BINARYTREE_H
#define BARKOCHBA_BINARYTREE_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

class SplitQueue {
private:
    class QueueElement{
    protected:
        std::string text;
        QueueElement* next;
    public:
        QueueElement(std::string s, QueueElement* n = nullptr) : text(s), next(n){}
        std::string getText() const { return text; }
        QueueElement* getNext() const { return next; }
        QueueElement* setNext(QueueElement* _next) { next = _next; return next; }
    };

    QueueElement* root;
    QueueElement* last;

public:
    SplitQueue(const std::string& s, const char& delim) : root(nullptr), last(nullptr) {
        std::stringstream ss(s);
        std::string token;
        while (std::getline(ss, token, delim)) {
            if (root == nullptr) root = last = new QueueElement(token);
            else last = last->setNext(new QueueElement(token));
        }
    }

    ~SplitQueue() {
        QueueElement* moving = root;
        while (moving != nullptr) {
            QueueElement* temp = moving->getNext();
            delete moving;
            moving = temp;
        }

    }

    QueueElement* getRoot() { return root; }

    std::string pop() {
        if (root != nullptr) {
            std::string tempS = root->getText();
            QueueElement* tempE = root;
            if (root == last) last = nullptr;
            root = root->getNext();
            delete tempE;
            return tempS;
        } else throw std::out_of_range("Empty Queue");
    }
};

///BinaryTreeEleemnt --------------------------------------------------

class BinaryTreeElement{
protected:
    std::string text;
    BinaryTreeElement* parent;
public:
    explicit BinaryTreeElement(const std::string& _text, BinaryTreeElement* _parent = nullptr) : text(_text), parent(_parent) {}
    virtual ~BinaryTreeElement() {};

    std::string getText() const { return text; }
    BinaryTreeElement* getParent() const { return parent; }
    virtual BinaryTreeElement* getLeftTrue() const = 0;
    virtual BinaryTreeElement* getRightFalse() const = 0;
    void setParent(BinaryTreeElement* _parent) { parent = _parent; }
    virtual void setLeftTrue(BinaryTreeElement* _left) = 0;
    virtual void setRightFalse(BinaryTreeElement* _right) = 0;
    virtual void askQuestion() = 0 ;
    void addQuestion();
    std::string serialize() const;
};

///GUESS -----------------------------------------------

class Guess : public BinaryTreeElement{
private:
public:
    explicit Guess(const std::string& _text, BinaryTreeElement* _parent = nullptr) :
            BinaryTreeElement(_text,_parent){}

    virtual BinaryTreeElement* getLeftTrue() const { return nullptr; }
    virtual BinaryTreeElement* getRightFalse() const { return nullptr; }
    virtual void setLeftTrue(BinaryTreeElement* _left) {}; /// !
    virtual void setRightFalse(BinaryTreeElement* _right) {}; /// !
    virtual void askQuestion();
};

///QUESTION -----------------------------------------------

class Question : public BinaryTreeElement {
private:
    BinaryTreeElement* leftTrue;
    BinaryTreeElement* rightFalse;

public:
    Question(const std::string& _text,  BinaryTreeElement* _leftTrue,  BinaryTreeElement* _rightFalse, BinaryTreeElement* _parent = nullptr) :
            BinaryTreeElement(_text, _parent), leftTrue(_leftTrue), rightFalse(_rightFalse) {}

    virtual BinaryTreeElement* getLeftTrue() const { return leftTrue; }
    virtual BinaryTreeElement* getRightFalse() const { return rightFalse; }
    virtual void setLeftTrue(BinaryTreeElement* _left) { leftTrue = _left; }
    virtual void setRightFalse(BinaryTreeElement* _right) { rightFalse = _right; }
    virtual void askQuestion();
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
