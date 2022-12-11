#include "command.h"
#include "environment.h"
#include <iostream>

int main() {
    // check if irrelevant assignment fails
    std::cout << "Assignment test 1 start:\n";
    Environment env;
    AssigmentCommand eq(&env);
    std::vector<std::string> args;
    args.push_back("$var");
    args.push_back("some");
    eq.execute(args, "");
    std::cout << "Assignment test 1 end\n";
    if (env.findVar("$var")) return 1;
    return 0;
}
