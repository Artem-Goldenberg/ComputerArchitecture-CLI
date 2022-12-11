#include "io.h"
#include <iostream>

IO::IO() {
    std::cout << "\nWelcome to myshell\n";
    std::cout.flush();
}

IO::~IO() {
    std::cout << "\nProcess exited" << std::endl;
}

std::string IO::getRequest() {
    std::string ans;
    std::cout << "Shell> ";
    std::getline(std::cin, ans);
    return ans;
}

void IO::writeResponce(std::string ans) {
    if (!ans.empty()) {
        std::string end = *(ans.end() - 1) == '\n' ? "\n" : "\n\n";
        std::cout << "\n" << ans << end;
    }
    std::cout.flush();
}
