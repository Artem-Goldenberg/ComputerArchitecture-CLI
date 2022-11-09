#include "command.h"
#include "environment.h"
#include <iostream>

int main() {
    std::cout << "Assignment test 0 start:\n";
    Environment env;
    AssigmentCommand eq(&env);
    std::vector<std::string> args;
    args.push_back("var1");
    args.push_back("some");
    eq.execute(args, "");
    std::cout << "Assignment test 0 end\n";
    if (!env.findVar("var1")) return 1;
    if (env.getVar("var1") != "some") return 1;
    return 0;
}
