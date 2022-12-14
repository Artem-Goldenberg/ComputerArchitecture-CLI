#include "parser.h"
#include <iostream>

int main() {
    // init test input
    Parser parser;
    std::vector<Token> in_tokens; // cat helloWorld.txt | grep Hello

    // get parser results
    std::variant<std::vector<CommandData>, std::string> var_ans = parser.parse(in_tokens);
    if( std::holds_alternative<std::string>(var_ans) ) {
        std::cout << "Parse error: " << std::get<std::string>(var_ans);
        return 1;
    }
    std::vector<CommandData> parse_ans = std::get<std::vector<CommandData>>(var_ans);


    // init true answer
    std::vector<CommandData> true_ans;


    // check names&args
    if(true_ans.size() == parse_ans.size()) {
        for(int pos = 0; pos < true_ans.size(); pos++) {
            if(true_ans[pos].getName() != parse_ans[pos].getName() ) return 2;
            if(true_ans[pos].getArgs().size() != parse_ans[pos].getArgs().size()) return 3;

            for(int arg_num = 0; arg_num < true_ans[pos].getArgs().size(); arg_num++) {
                if(true_ans[pos].getArgs()[arg_num] != parse_ans[pos].getArgs()[arg_num]) {
                    std::cout << arg_num << ". got argument: " << parse_ans[pos].getArgs()[arg_num] << ", expected " <<true_ans[pos].getArgs()[arg_num] << std::endl;
                    return 4;
                }
            }
        }
    } else {
        std::cout << "Got " << parse_ans.size() << " commands, expected " << true_ans.size();
    }

    // TODO: check pipes

    return 0;
}
