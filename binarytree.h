#ifndef BARKOCHBA_BINARYTREE_H
#define BARKOCHBA_BINARYTREE_H

/// \file binarytree.h

#include <string>

/// Bináris fa elemet megvalósító osztály.
/// Dinamikus példányai keletkeznek, amik a
/// BinárisFa osztály destruktorában szabadulnak fel.
class BinaryTreeElement{
protected:
    std::string text;           ///< A kérdés vagy dolog szövegét tárolja el
    BinaryTreeElement* parent;  ///< Szülőre mutató pointer
public:
    /// Konstruktor, alapértelmezetten a szülőpointert nullptr-el inicializálja.
    /// @param _text - a kérdés szövege, vagy a dolog neve
    /// @param _parent - szülőpointer
    explicit BinaryTreeElement(const std::string& _text, BinaryTreeElement* _parent = nullptr) : text(_text), parent(_parent) {}
    
    /// Virtuális destruktor.
    virtual ~BinaryTreeElement() {}

    /// A kérdés, vagy dolog szövegét adja vissza.
    std::string getText() const { return text; }

    /// A szülőpointert adja vissza.
    BinaryTreeElement* getParent() const { return parent; }
    
    /// A baloldali igaz irány következő elemére mutató pointert adja vissza.
    virtual BinaryTreeElement* getLeftTrue() const = 0;
    
    /// A jobboldali hamis irány következő elemére mutató pointert adja vissza.
    virtual BinaryTreeElement* getRightFalse() const = 0;

    /// A kérdés, vagy dolog szövegét állítja be.
    /// @param _text - beállítandó szöveg
    void setText(const std::string& _text) { text = _text; }
    
    /// A szülő pointert állítja be.
    /// @param _parent - beállítandó pointer
    void setParent(BinaryTreeElement* _parent) { parent = _parent; }
    
    /// A baloldali igaz irányú pointert állítja be.
    /// @param _parent - beállítandó pointer
    virtual void setLeftTrue(BinaryTreeElement* _left) {}
    
    /// A jobboldali hamis irányú pointert állítja be.
    /// @param _parent - beállítandó pointer
    virtual void setRightFalse(BinaryTreeElement* _right) {}

    /// Felteszi a kérdést, vagy rákérdez a dologra.
    virtual void askQuestion() = 0 ;
    
    /// Hozzáad egy új kérdést az adatbázishoz.
    void addQuestion();
    
    /// Sztringgé alakítja az adatbázist.
    std::string serialize() const;
};

/// Bináris fát megvalósító osztály.
class BinaryTree {
private:
    BinaryTreeElement* root;    ///< a fa gyökerére mutató pointer
public:
    /// Konstruktor, alapértelmezetten a gyökérpointert nullptr-el inicializálja.
    BinaryTree() : root(nullptr) {}
    
    /// A bináris fa felszabadítását végző rekurzív függvény.
    /// @param _root - a felszabadítandó fa gyökerére mutató pointer
    void freeBinaryTree (BinaryTreeElement* _root);
    
    /// Destruktor
    ~BinaryTree() { freeBinaryTree(root); };

    /// A gyökérpointert adja vissza.
    BinaryTreeElement* getRoot(){ return root; }

    //// A gyökérpointert állítja be.
    /// @param _root - beállítandó pointer
    void setRoot(BinaryTreeElement* _root) { root = _root; };
    
    /// Elindít egy új játékot.
    void newGame();

    /// Elmenti az adatbázist.
    void save(const std::string& file) const;

    /// Betölti az adatbázist.
    void load(const std::string& file);
    
    /// Az adatbázis sztringből való visszatöltését segítő rekurzív függvény.
    /// @param is - beolvasni kívánt adatfolyam
    /// @param parent - létrehozott példány szülöpointere
    BinaryTreeElement* deserialize(std::istream& is, BinaryTreeElement* parent  = nullptr);
};



#endif //BARKOCHBA_BINARYTREE_H
