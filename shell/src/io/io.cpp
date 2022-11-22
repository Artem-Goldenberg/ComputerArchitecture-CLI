#include "io.h"
#include <iostream>

IO::IO() {
    std::cout << "\nHello World\n";
    std::cout.flush();
}

IO::~IO() {
    std::cout << "\nProcess exited" << std::endl;
}

std::string IO::getRequest() {
    std::string ans;
    std::cout << "Shell> ";
    std::getline(std::cin >> std::ws, ans);
    std::cout << "\n";
    return ans;
}

void IO::writeResponce(std::string ans) {
    if (!ans.empty()) {
        char sep = *(ans.end() - 1) == '\n' ? '\0' : '\n';
        std::cout << ans << sep << "\n";
    }
    std::cout.flush();
}
