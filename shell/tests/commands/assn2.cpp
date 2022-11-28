#include "command.h"
#include "environment.h"
#include <iostream>

int main() {
    // check if old variable assignment works
    std::cout << "Assignment test 2: " << std::endl;

    std::cout << '\t' << "Init... ";
        Environment env;
        AssigmentCommand eq(&env);

        env.addVar("var1", "some1");
        env.addVar("var2", "some2");
        env.addVar("var3", "some3");
        env.addVar("var4", "some4");

        std::vector<std::string> args = {"var2", "some5"};
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Processing... ";
        eq.execute(args, "");
    std::cout << "DONE" << std::endl;

    std::cout << '\t' << "Checking results... ";
        if (!env.findVar("var1")) {std::cout << "Error: variable \"var1\" dissapeared from env" << std::endl; return 1;}
        if (!env.findVar("var2")) {std::cout << "Error: variable \"var2\" dissapeared from env" << std::endl; return 1;}
        if (!env.findVar("var3")) {std::cout << "Error: variable \"var3\" dissapeared from env" << std::endl; return 1;}
        if (!env.findVar("var4")) {std::cout << "Error: variable \"var4\" dissapeared from env" << std::endl; return 1;}


        if (env.getVar("var1") != "some1") {std::cout << "Error: variable unexpectedly changed" << std::endl; return 2;}
        if (env.getVar("var3") != "some3") {std::cout << "Error: variable unexpectedly changed" << std::endl; return 2;}
        if (env.getVar("var4") != "some4") {std::cout << "Error: variable unexpectedly changed" << std::endl; return 2;}

        if (env.getVar("var2") != "some5") {
            std::cout << "Error: wrong value assigned" << std::endl;
            return 3;
        }
    std::cout << "PASSED" << std::endl;

    return 0;
}