#include <iostream>
#include <ctime>
#include "datetime.h"

int main() {
    std::string text;
    DateTime *datetime = DateTime::getInstance();

    text = datetime->getCurrentDateString();
    std::cout << "getCurrentDateString: text = " << text << std::endl;

    text = datetime->getCurrentDateTimeString();
    std::cout << "getCurrentDateTimeString: text = " << text << std::endl;

    return 0;
}