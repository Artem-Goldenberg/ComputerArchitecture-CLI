#import "command.h"
#import <iostream>

int main() {
    std::cout << "WordCount test 1 start:\n";
    system("wc testInput.txt testInput2.txt");
    WordCount wc;
    std::vector<std::string> args;
    Result res = wc.execute(args, "testInput2.txt");
    std::cout << res.unwrap() << std::endl;
    std::cout << "WordCount test 1 end\n";
    if (!res.isOk()) return 1;
    if (res.unwrap() != "1 1 14") return 1;
    return 0;
}
