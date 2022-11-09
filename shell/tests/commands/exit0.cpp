#include "command.h"
#include <iostream>

using namespace std;

int main() {
    std::cout << "Exit test 0 end:\n";
    
    Exit ext;
    Result res = ext.execute({}, "");
    
    std::cout << "Exit test 0 end:\n";
     
    if (res.isOk()) return 1;
    if (res.unwrap() != "_EXIT") return 1;
    
    return 0;
}
