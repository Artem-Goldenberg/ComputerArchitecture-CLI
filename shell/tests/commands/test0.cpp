#import "command.h"
#import <iostream>

int main() {
    std::cout << "WordCount test 0 start:\n";
    system("wc testInput.txt testInput2.txt");
    WordCount wc;
    std::vector<std::string> args;
    args.push_back("testInput.txt");
    Result res = wc.execute(args, "testInput2.txt");
    std::cout << res.unwrap() << std::endl;
    std::cout << "WordCount test 0 end\n";
    if (!res.isOk()) return 1;
    if (res.unwrap() != "6 42 198  testInput.txt") return 1;
    return 0;
}
