#include "io.h"
#include <iostream>

IO::IO() {
    std::cout << "\nHello World\nShell> ";
    std::cout.flush();
}

IO::~IO() {
    std::cout << "\nProcess exited" << std::endl;
}

std::string IO::getRequest() {
    std::string ans;
    std::getline(std::cin >> std::ws, ans);
    return ans;
}

void IO::writeResponce(std::string ans) {
    std::cout << ans << "\nShell> ";
    std::cout.flush();
}