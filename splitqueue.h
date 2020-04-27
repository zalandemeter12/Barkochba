#ifndef BARKOCHBA_SPLITQUEUE_H
#define BARKOCHBA_SPLITQUEUE_H

#include <string>

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
    SplitQueue(const std::string&, const char&);
    ~SplitQueue();
    QueueElement* getRoot() { return root; }
    std::string pop();
};

#endif