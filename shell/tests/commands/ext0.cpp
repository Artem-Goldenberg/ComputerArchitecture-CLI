#import "command.h"
#import <iostream>

int main() {
    std::cout << "ExternalCommand test 0 start:\n";
    
    ExternalCommand cmd;
    std::vector<std::string> args;
    args.push_back("find");
    args.push_back("testInput.txt");
    Result res = cmd.execute(args, "");
    std::cout << res.unwrap() << std::endl;
    
    std::cout << "ExternalCommand test 0 end\n";
    
    if (!res.isOk()) return 1;
    if (res.unwrap() != "testInput.txt\n") return 1;
    return 0;
}
