#import "command.h"
#import <iostream>

int main() {
    std::cout << "WordCount test 2 start:\n";
    system("wc testInput.txt testInput2.txt");
    WordCount wc;
    std::vector<std::string> args;
    args.push_back("testInput.txt");
    args.push_back("testInput2.txt");
    Result res = wc.execute(args, "");
    std::cout << res.unwrap() << std::endl;
    std::cout << "WordCount test 2 end\n";
    if (!res.isOk()) return 1;
    if (res.unwrap() != "6 42 198  testInput.txt\n2 4 9  testInput2.txt\n8 46 207  total") return 1;
    return 0;
}
