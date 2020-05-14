/// \file binarytree.cpp

#include "binarytree.h"
#include "question.h"
#include "guess.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

void BinaryTreeElement::addQuestion() {
    std::string textQ, textG;
    std::cout << "Adj meg egy kérdést, ami az általad gondolt dologra igaz, de a gép által kitalált dologra hamis." << std::endl;
    std::getline(std::cin, textQ);
    std::cout << "Mire gondoltál?" << std::endl;
    std::getline(std::cin, textG);
    BinaryTreeElement* newG = new Guess(textG, nullptr);
    BinaryTreeElement* newQ = new Question(textQ, newG, (BinaryTreeElement *) this, this->getParent());

    if (this->getParent()->getLeftTrue() == this)
        this->getParent()->setLeftTrue(newQ);
    else this->getParent()->setRightFalse(newQ);

    newG->setParent(newQ);
    this->setParent(newQ);
}

std::string BinaryTreeElement::serialize() const{
    if (getRightFalse() == nullptr || getLeftTrue() == nullptr)
        return "guess~" + text + "|";
    else{
        std::string leftSerialized = getLeftTrue()->serialize();
        std::string rightSerialized = getRightFalse()->serialize();
        return "question~" + text + "|" + leftSerialized + rightSerialized;
    }
}

BinaryTreeElement* BinaryTree::deserialize(std::istream& is, BinaryTreeElement* _parent) {
    std::string data;
    std::getline(is, data, '|');

    if (data.empty()) return nullptr;

    std::istringstream iss(data);
    std::getline(iss, data, '~');

    if (data == "guess") {
        std::getline(iss, data);
        Guess* newNode = new Guess(data, _parent);
        return newNode;
    }
    else{
        std::getline(iss, data);
        Question* newNode = new Question(data, nullptr, nullptr, _parent);
        newNode->setLeftTrue(deserialize(is, newNode));
        newNode->setRightFalse(deserialize(is, newNode));
        return newNode;
    }
}
 
void BinaryTree::freeBinaryTree (BinaryTreeElement* _root) {
    if (_root == nullptr) return;
    freeBinaryTree(_root->getLeftTrue());
    freeBinaryTree(_root->getRightFalse());
    delete _root;
}

void BinaryTree::newGame() {
    if (root == nullptr) {
        std::string textQ, textGL, textGR;
        std::cout << "Adj meg egy kérdést!" << std::endl;
        std::getline(std::cin, textQ);
        std::cout << "Adj meg egy dolgot, amire igaz a kérdés!" << std::endl;
        std::getline(std::cin, textGL);
        std::cout << "Adj meg egy dolgot, amire hamis a kérdés!" << std::endl;
        std::getline(std::cin, textGR);
        BinaryTreeElement* newGL = new Guess(textGL, nullptr);
        BinaryTreeElement* newGR = new Guess(textGR, nullptr);
        BinaryTreeElement* newQ = new Question(textQ, newGL, newGR, nullptr);
        newGL->setParent(newQ);
        newGR->setParent(newQ);
        root = newQ;
    }
    else root->askQuestion();
}

void BinaryTree::save(const std::string& file) const {
    std::ofstream ofs(file); 
    if (ofs.fail()) throw std::runtime_error("Hiba a fájl megnyitása közben.");
    ofs << root->serialize();
    ofs.close();
}

void BinaryTree::load(const std::string& file) {
    std::ifstream ifs(file);
    if (ifs.fail()) throw std::runtime_error("Hiba a fájl megnyitása közben.");

    freeBinaryTree(root);
    root = deserialize(ifs, nullptr);
    
    ifs.close();
}