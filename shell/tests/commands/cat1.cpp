#include "command.h"
#include <iostream>

int main() {
    std::cout << "Cat test 1 start:\n";

    std::cout << '\t' << "Init variables... ";
        Cat cat;
        std::vector<std::string> v = {"testInput1.txt"};
        std::string true_ans = "";
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Executing... ";
        Result res = cat.execute(v, "hello World");
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Checking answers... ";
        if (!res.isOk()) {
            std::cout << "Error: unexpected error \"" << res.unwrap() << "\"" << std::endl;
            return 1;
        } else if ( res.unwrap() != true_ans) {
            std::cout << "Error: got answer \"" << res.unwrap() << "\", expected \"" << true_ans << "\"" << std::endl;
            return 2;
        }
    std::cout << "PASSED" << std::endl;

    return 0;
}
