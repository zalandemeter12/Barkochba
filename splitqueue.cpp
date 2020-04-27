#include "splitqueue.h"

#include <sstream>
#include <stdexcept>

SplitQueue::SplitQueue(const std::string& s, const char& delim) : root(nullptr), last(nullptr) {
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (root == nullptr) root = last = new QueueElement(token);
        else last = last->setNext(new QueueElement(token));
    }
}

SplitQueue::~SplitQueue() {
    QueueElement* moving = root;
    while (moving != nullptr) {
        QueueElement* temp = moving->getNext();
        delete moving;
        moving = temp;
    }
}

std::string SplitQueue::pop() {
        if (root != nullptr) {
            std::string tempS = root->getText();
            QueueElement* tempE = root;
            if (root == last) last = nullptr;
            root = root->getNext();
            delete tempE;
            return tempS;
        } else throw std::out_of_range("Empty Queue");
    }