/// \file main.cpp

#include "binarytree.h"
#include "gtest.h"
#include "question.h"
#include "guess.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    TEST(TEST1, emptyRoot) {
        BinaryTree barkochba;
        if (barkochba.getRoot() != nullptr) 
            FAIL() << "Nem üres bináris fa jött létre." << std::endl;
    } ENDM

    TEST(TEST2, correctQuestion) {
        Question q1("Szülő", nullptr, nullptr, nullptr);
        Question q2("Helyesen jöttem létre?", new Guess("Igen", nullptr), new Guess("Nem", nullptr), &q1);

        if (q2.getText() != "Helyesen jöttem létre?") 
            FAIL() << "Helytelen szöveggel jött létre a kérdés." << std::endl;

        if (q2.getLeftTrue()->getText() != "Igen")
            FAIL() << "Helytelen szöveggel jött létre a tipp." << std::endl;
        
        if (q2.getRightFalse()->getText() != "Nem")
            FAIL() << "Helytelen szöveggel jött létre a tipp." << std::endl;
        
        if (q2.getParent()->getText() != "Szülő")
            FAIL() << "Helytelen szülővel jött létre a kérdés." << std::endl;
        
        q2.setParent(nullptr);
        if (q2.getParent() != nullptr)
            FAIL() << "Szülő beállítása sikertelen." << std::endl;
        
        delete q2.getLeftTrue();
        delete q2.getRightFalse();
        q2.setLeftTrue(nullptr);
        if (q2.getLeftTrue() != nullptr)
            FAIL() << "Bal pointer beállítása sikertelen." << std::endl;
        
        q2.setRightFalse(nullptr);
        if (q2.getRightFalse() != nullptr)
            FAIL() << "Jobb pointer beállítása sikertelen." << std::endl;
    } ENDM

    TEST(TEST3, correctGuess) {
        Question q("Szülő", nullptr, nullptr, nullptr);
        Guess g("Tipp", &q);
        
        if (g.getText() != "Tipp") 
            FAIL() << "Helytelen szöveggel jött létre a kérdés." << std::endl;
        
        if (g.getParent()->getText() != "Szülő")
            FAIL() << "Helytelen szülővel jött létre a kérdés." << std::endl;
        
        g.setParent(nullptr);
        if (g.getParent() != nullptr)
            FAIL() << "Szülő beállítása sikertelen." << std::endl;
    } ENDM

    TEST(TEST4, serialize) {
        Guess g1("Igen", nullptr);
        Guess g2("Nem", nullptr);
        Question q("Kérdés?", &g1, &g2, nullptr);
        
        if (q.serialize() != "question~Kérdés?|guess~Igen|guess~Nem|") 
            FAIL() << "Hibás sztringgé alakítás" << std::endl;
    } ENDM

    TEST(TEST5, deserialize) {
        BinaryTree barkochba;
        std::istringstream temp("question~Kérdés?|guess~Igen|guess~Nem|");
        barkochba.setRoot(barkochba.deserialize(temp));
        
        if (barkochba.getRoot()->getText() != "Kérdés?")
            FAIL() << "Hibás beolvasás sztringből." << std::endl;
        
        if (barkochba.getRoot()->getLeftTrue()->getText() != "Igen")
            FAIL() << "Hibás beolvasás sztringből." << std::endl;
        
        if (barkochba.getRoot()->getRightFalse()->getText() != "Nem")
            FAIL() << "Hibás beolvasás sztringből." << std::endl;
    } ENDM
    
    TEST(TEST6,gameplay) {
        std::cout.setstate(std::ios_base::failbit);
        std::stringstream temp_cin;
        std::streambuf *backup = std::cin.rdbuf();
        std::streambuf *psbuf = temp_cin.rdbuf();
        std::cin.rdbuf(psbuf);

        BinaryTree barkochba;

        temp_cin << "Élőlény?" << std::endl;
        temp_cin << "Ló" << std::endl;
        temp_cin << "Asztal" << std::endl;

        barkochba.newGame();
        std::string temp = barkochba.getRoot()->serialize();
        if (temp != "question~Élőlény?|guess~Ló|guess~Asztal|")
            FAIL() << "Hibásan kezelt felhasználó input." << std::endl;
        
        temp_cin << "Igen" << std::endl;
        temp_cin << "Nem" << std::endl;
        temp_cin << "Vízben él?" << std::endl;
        temp_cin << "Bálna" << std::endl;

        barkochba.newGame();

        temp = barkochba.getRoot()->serialize();
        if (temp != "question~Élőlény?|question~Vízben él?|guess~Bálna|guess~Ló|guess~Asztal|")
            FAIL() << "Hibásan kezelt felhasználó input." << std::endl;

        std::cin.rdbuf(backup);
        std::cout.clear();
    } ENDM

    TEST(TEST7,persistence) {
        BinaryTree barkochba;
        barkochba.load("empty.dat");
        if (barkochba.getRoot() != nullptr) 
            FAIL() << "Nem üres bináris fa töltödött be." << std::endl;

        std::istringstream temp("question~Kérdés?|guess~Igen|guess~Nem|");
        barkochba.setRoot(barkochba.deserialize(temp));
        barkochba.save("empty.dat");

        std::ifstream ifs("empty.dat");
        std::string line;
        std::getline(ifs, line);
        ifs.close();

        if (line != "question~Kérdés?|guess~Igen|guess~Nem|")
            FAIL() << "Hibás fájlba mentés." << std::endl;
        
        barkochba.load("empty.dat");
        line = barkochba.getRoot()->serialize();

        if (line != "question~Kérdés?|guess~Igen|guess~Nem|")
            FAIL() << "Hibás fájlból betöltés." << std::endl;

        std::ofstream ofs("empty.dat");
        ofs.close();
        
    } ENDM

  return 0;
}