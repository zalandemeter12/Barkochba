/// \file question.h

#ifndef BARKOCHBA_QUESTION_H
#define BARKOCHBA_QUESTION_H

#include "binarytree.h"

/// Kérdést megvalósító bináris fa elem.
class Question : public BinaryTreeElement {
private:
    BinaryTreeElement* leftTrue;    ///< Baloldali igaz irányban következő elemre mutató pointer.
    BinaryTreeElement* rightFalse;  ///< Jobboldali hamis irányban következő elemre mutató pointer.

public:
    /// Konstruktor, alapértelmezetten a szülőpointert nullptr-el inicializálja.
    /// @param _text - a kérdés szövege
    /// @param _leftTrue - baloldali igaz irányú pointer
    /// @param _rightFalse - jobboldali hamis irányú pointer
    /// @param _parent - szülőpointer
    Question(const std::string& _text,  BinaryTreeElement* _leftTrue,  BinaryTreeElement* _rightFalse, BinaryTreeElement* _parent = nullptr) :
        BinaryTreeElement(_text, _parent), leftTrue(_leftTrue), rightFalse(_rightFalse) {}
    
    /// Destruktor.
    ~Question() {}

    /// A baloldali igaz irány következő elemére mutató pointert adja vissza.
    virtual BinaryTreeElement* getLeftTrue() const { return leftTrue; }

    /// A jobboldali hamis irány következő elemére mutató pointert adja vissza.
    virtual BinaryTreeElement* getRightFalse() const { return rightFalse; }

    /// A baloldali igaz irányú pointert állítja be.
    /// @param _parent - beállítandó pointer  
    void setLeftTrue(BinaryTreeElement* _left) { leftTrue = _left; }
    
    /// A jobboldali hamis irányú pointert állítja be.
    /// @param _parent - beállítandó pointer
    void setRightFalse(BinaryTreeElement* _right) { rightFalse = _right; }
  
    /// Felteszi a kérdést.
    virtual void askQuestion();
};

#endif