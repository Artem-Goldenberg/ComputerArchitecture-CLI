#include "command.h"
#include <iostream>

int main() {
    std::cout << "WordCount test 0:" << std::endl;

    // std::cout << '\t' << "Get system's wc answer... ";
    // std::system("wc testInput.txt testInput2.txt");
    // std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Testing wc answer... ";
    WordCount wc;
    std::vector<std::string> args = {"testInput.txt"};
    Result res = wc.execute(args, "testInput2.txt");
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Checking answers... ";
    if (!res.isOk()) {
        std::cout << "Execution error: " << res.unwrap() << std::endl;
        return 1;
    } else if (res.unwrap() != "6 42 198  testInput.txt") {
        std::cout << "Error: expected \"6 42 198  testInput.txt\", but got: \"" << res.unwrap() << "\"" << std::endl;
        return 1;
    }
    std::cout << "PASSED" << std::endl;

    return 0;
}
