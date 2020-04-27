#include "question.h"
#include <iostream>

void Question::askQuestion() {
    std::string answer;
    std::cout << text << std::endl;
    std::cout << "Igen / Nem" << std::endl;
    std::getline(std::cin, answer);
    if (answer == "Igen" || answer == "igen") leftTrue->askQuestion();
    else if (answer == "Nem" || answer == "nem") rightFalse->askQuestion();
}