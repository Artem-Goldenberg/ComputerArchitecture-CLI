#include "command.h"
#include <iostream>

using namespace std;

int main() {
    std::cout << "Echo test 0 start:\n";
    
    Echo echo;
    vector<string> v;
    v.push_back("some");
    Result res = echo.execute(v, "");
    puts(res.unwrap().c_str());
    
    std::cout << "Echo test 0 end\n";
    
    if (!res.isOk()) return 1;
    if (res.unwrap() != "some") return 1;
    
    std::cout << "Echo test 1 start:\n";
    
    v.push_back("more");
    v.push_back("more ");
    v.push_back("");
    Result res1 = echo.execute(v, "and more ");
    puts(res1.unwrap().c_str());
    
    std::cout << "Echo test 1 end\n";
    
    if (!res1.isOk()) return 1;
    if (res1.unwrap() != "some more more   and more ") return 1;
    
    return 0;
}
