#include "guess.h"
#include <iostream>

void Guess::askQuestion() {
    std::string answer;
    std::cout << text << ", erre gondoltál?" << std::endl;
    std::cout << "Igen / Nem" << std::endl;
    std::getline(std::cin, answer);
    if (answer == "Igen" || answer == "igen") std::cout << "Köszönöm, hogy játszottál!" << std::endl;
    else if (answer == "Nem" || answer == "nem") {
        addQuestion(); 
        std::cout << "Köszönöm, hogy játszottál!" << std::endl;
    }
}