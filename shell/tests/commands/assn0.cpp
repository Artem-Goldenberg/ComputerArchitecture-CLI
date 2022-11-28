#include "command.h"
#include "environment.h"
#include <iostream>

int main() {
    // check if new variable assignment works
    std::cout << "Assignment test 0: " << std::endl;

    std::cout << '\t' << "Init... ";
        Environment env;
        AssigmentCommand eq(&env);
        std::vector<std::string> args = {"var1", "some"};
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Processing... ";
        eq.execute(args, "");
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Checking results... ";
        if (!env.findVar("var1")) {
            std::cout << "Error: no assignment done" << std::endl;
            return 1;
        } else if (env.getVar("var1") != "some") {
            std::cout << "Error: wrong value assigned" << std::endl;
            return 2;
        }
    std::cout << "PASSED" << std::endl;

    return 0;
}
