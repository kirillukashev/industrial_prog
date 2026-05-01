#include <iostream>
#include "main.h"

int main() {
    std::cout << "Project: " << PROJECT_NAME << " v" << PROJECT_VERSION << std::endl;
    std::cout << "Magic numbers: ";
    for (int i = 0; i < MAGIC_COUNT; i++) {
        std::cout << MAGIC_NUMBERS[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "2 + 3 = " << add(2, 3) << std::endl;
    std::cout << "4 * 5 = " << multiply(4, 5) << std::endl;
    std::cout << "fibonacci(10) = " << fibonacci(10) << std::endl;
    return 0;
}
