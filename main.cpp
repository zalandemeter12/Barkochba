#include "binarytree.h"
#include "gtest_lite.h"
#include "question.h"
#include "guess.h"

using std::cout;
using std::cin;
using std::endl;


int main() {
  TEST(TEST1, emptyRoot) {
      BinaryTree barkochba;
      if (barkochba.getRoot() != nullptr) 
          FAIL() << "Nem üres bináris fa jött létre." << endl;
  } ENDM

  TEST(TEST2, emptyLoad) {
      BinaryTree barkochba;
      barkochba.load();
      if (barkochba.getRoot() != nullptr) 
          FAIL() << "Nem üres bináris fa töltödött be." << endl;
  } ENDM

  TEST(TEST3, correctQuestion) {
      Question q1("Szülő", nullptr, nullptr, nullptr);
      Question q2("Helyesen jöttem létre?", new Guess("Igen", nullptr), new Guess("Nem", nullptr), &q1);
      if (q2.getText() != "Helyesen jöttem létre?") 
          FAIL() << "Helytelen szöveggel jött létre a kérdés." << endl;
      if (q2.getLeftTrue()->getText() != "Igen")
          FAIL() << "Helytelen szöveggel jött létre a tipp." << endl;
      if (q2.getRightFalse()->getText() != "Nem")
          FAIL() << "Helytelen szöveggel jött létre a tipp." << endl;
      if (q2.getParent()->getText() != "Szülő")
          FAIL() << "Helytelen szülővel jött létre a kérdés." << endl;
      q2.setParent(nullptr);
      if (q2.getParent() != nullptr)
          FAIL() << "Szülő beállítása sikertelen." << endl;
      delete q2.getLeftTrue();
      delete q2.getRightFalse();
      q2.setLeftTrue(nullptr);
      if (q2.getLeftTrue() != nullptr)
          FAIL() << "Bal pointer beállítása sikertelen." << endl;
      q2.setRightFalse(nullptr);
      if (q2.getRightFalse() != nullptr)
          FAIL() << "Jobb pointer beállítása sikertelen." << endl;
  } ENDM

  TEST(TEST4, correctGuess) {
      Question q("Szülő", nullptr, nullptr, nullptr);
      Guess g("Tipp", &q);
      if (g.getText() != "Tipp") 
          FAIL() << "Helytelen szöveggel jött létre a kérdés." << endl;
      if (g.getParent()->getText() != "Szülő")
          FAIL() << "Helytelen szülővel jött létre a kérdés." << endl;
      g.setParent(nullptr);
      if (g.getParent() != nullptr)
          FAIL() << "Szülő beállítása sikertelen." << endl;
  } ENDM

  TEST(TEST5, serialize) {
      Guess g1("Igen", nullptr);
      Guess g2("Nem", nullptr);
      Question q("Kérdés?", &g1, &g2, nullptr);
      if (q.serialize() != "question~Kérdés?|guess~Igen|guess~Nem|") 
          FAIL() << "Hibás sztringgé alakítás" << endl;
  } ENDM

  TEST(TEST6, deserialize) {
      BinaryTree barkochba;
      barkochba.deserialize("question~Kérdés?|guess~Igen|guess~Nem|");
      if (barkochba.getRoot()->getText() != "Kérdés?")
          FAIL() << "Hibás beolvasás sztringből." << endl;
      if (barkochba.getRoot()->getLeftTrue()->getText() != "Igen")
          FAIL() << "Hibás beolvasás sztringből." << endl;
      if (barkochba.getRoot()->getRightFalse()->getText() != "Nem")
          FAIL() << "Hibás beolvasás sztringből." << endl;
  } ENDM


  
  return 0;
}