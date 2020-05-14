/// \file guess.h

#ifndef BARKOCHBA_GUESS_H
#define BARKOCHBA_GUESS_H

#include "binarytree.h"

/// Találgatott dolgot megvalósító bináris fa elem.
class Guess : public BinaryTreeElement{
public:
    /// Konstruktor, alapértelmezetten a szülőpointert nullptr-el inicializálja.
    /// @param _text - a dolog neve
    /// @param _parent - szülőpointer
    explicit Guess(const std::string& _text, BinaryTreeElement* _parent = nullptr) :
        BinaryTreeElement(_text,_parent){}
    
    /// Destruktor.
    ~Guess() {}

    /// A baloldali igaz irány következő elemére mutató pointer helyett nullptr-t ad vissza.
    virtual BinaryTreeElement* getLeftTrue() const { return nullptr; }

    /// A jobboldali hamis irány következő elemére mutató pointer helyett nullptr-t ad vissza.
    virtual BinaryTreeElement* getRightFalse() const { return nullptr; }

    /// Rákérdez a dologra.
    virtual void askQuestion();
};

#endif