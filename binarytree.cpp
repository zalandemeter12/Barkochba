#include "binarytree.h"
#include <iostream>

void BinaryTreeElement::addQuestion() {
    std::cin.clear();
    fflush(stdin);
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

BinaryTreeElement* BinaryTree::deserializeHelper(SplitQueue& queue, BinaryTreeElement* _parent) {
    std::string text = queue.pop();
    if (text == "nullptr") return nullptr;
    SplitQueue secondary(text, '~');
    BinaryTreeElement* newNode;
    if (secondary.pop() == "guess")
        newNode = new Guess(secondary.pop(), _parent);
    else{
        newNode = new Question(secondary.pop(), nullptr, nullptr, _parent);
        newNode->setLeftTrue(deserializeHelper(queue, newNode));
        newNode->setRightFalse(deserializeHelper(queue, newNode));
    }
    return newNode;
}

void BinaryTree::deserialize(const std::string& s){
    freeBinaryTree(root);
    SplitQueue queue(s, '|');
    root = deserializeHelper(queue, nullptr);
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

#include <fstream>

void BinaryTree::save() const {
    std::ofstream ofs("barkochba.dat");
    if (ofs.fail()) throw std::runtime_error("Hiba a fájl megnyitása közben.");
    ofs << root->serialize();
    ofs.close();
}

void BinaryTree::load() {
    std::ifstream ifs("barkochba.dat");
    if (ifs.fail()) throw std::runtime_error("Hiba a fájl megnyitása közben.");
    std::string data;
    std::getline(ifs, data);
    if (data.empty()) root = nullptr;
    else deserialize(data);
    ifs.close();
}

///GUESS --------------------------------------------------

void Guess::askQuestion() {
    std::string answer;
    std::cout << text << ", erre gondoltál?" << std::endl;
    std::cout << "Igen = 1 / Nem = 0" << std::endl;
    std::getline(std::cin, answer);
    if (answer == "1") std::cout << "Köszönöm, hogy játszottál!" << std::endl;
    else if (answer == "0") addQuestion();
}

///QUESTION ------------------------------------------------

void Question::askQuestion() {
    std::string answer;
    std::cout << text << std::endl;
    std::cout << "Igaz = 1 / Hamis = 0" << std::endl;
    std::getline(std::cin, answer);
    if (answer == "1") leftTrue->askQuestion();
    else if (answer == "0") rightFalse->askQuestion();
}
