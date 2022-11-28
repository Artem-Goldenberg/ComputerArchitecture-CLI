#include "command.h"
#include <iostream>

int main() {
    std::cout << "Cat test 0 start:\n";
    Cat cat;
    std::vector<std::string> v = {"testInput.txt", "testInput2.txt"};
    Result res = cat.execute(v, "");
    std::string validStr =
    "some code some some code code\n"
    "more words more words\n"
    "there will be a leading space in this line here -->\n"
    "Not it won't be huh my ide just won't let me make it that easily\n"
    "'' is this counts as words?\n"
    "\n"
    "' ' \" `\n"
    "";
    puts(res.unwrap().c_str());
    puts("And now look what real cat did: ");
    std::string catCall = "cat textInput.txt textInput2.txt";
    system(catCall.c_str());
    puts("That was it ---------");
    
    std::cout << "Cat test 1 end\n";
    if (!res.isOk()) return 1;
    if (res.unwrap() != validStr) return 1;
    return 0;
}
