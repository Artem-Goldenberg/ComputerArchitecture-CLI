#include "parser.h"
#include <iostream>

int main() {
    // init test input
    Parser parser;
    std::vector<Token> in_tokens; // g++ lib.hpp -DCMAKE_VERSION="c++21" -o lib.so
    in_tokens.push_back(Token(TokenType::mString, "g++"));
    in_tokens.push_back(Token(TokenType::mString, "lib.hpp"));
    in_tokens.push_back(Token(TokenType::mString, "-DCMAKE_VERSION"));
    in_tokens.push_back(Token(TokenType::mEquals, ""));
    in_tokens.push_back(Token(TokenType::mString, "c++21"));
    in_tokens.push_back(Token(TokenType::mString, "-o"));
    in_tokens.push_back(Token(TokenType::mString, "lib.so"));

    // get parser results
    std::variant<std::vector<CommandData>, std::string> var_ans = parser.parse(in_tokens);
    if( std::holds_alternative<std::string>(var_ans) ) {
        std::cout << "Parse error: " << std::get<std::string>(var_ans);
        return 1;
    }
    std::vector<CommandData> parse_ans = std::get<std::vector<CommandData>>(var_ans);


    // init true answer
    std::vector<CommandData> true_ans;

    {
        CommandData command = CommandData("g++");
        command.addArgument("lib.hpp");
        command.addArgument("-DCMAKE_VERSION");
        command.addArgument("=");
        command.addArgument("c++21");
        command.addArgument("-o");
        command.addArgument("lib.so");
        true_ans.push_back(command);
    }

    // check names&args
    if(true_ans.size() == parse_ans.size()) {
        for(int pos = 0; pos < true_ans.size(); pos++) {
            if(true_ans[pos].getName() != parse_ans[pos].getName() ) {
                std::cout << "got command name " << parse_ans[pos].getName() << ", expected " << true_ans[pos].getName() << std::endl;
                return 2;
            }
            if(true_ans[pos].getArgs().size() != parse_ans[pos].getArgs().size()) {
                std::cout << "got " << parse_ans[pos].getArgs().size() << " arguments, expected " << true_ans[pos].getArgs().size() << std::endl;
                return 3;
            }

            for(int arg_num = 0; arg_num < true_ans[pos].getArgs().size(); arg_num++) {
                if(true_ans[pos].getArgs()[arg_num] != parse_ans[pos].getArgs()[arg_num]) {
                    std::cout << arg_num << ". got argument: " << parse_ans[pos].getArgs()[arg_num] << ", expected " <<true_ans[pos].getArgs()[arg_num] << std::endl;
                    return 4;
                }
            }
        }
    } else {
        std::cout << "Got " << parse_ans.size() << " commands, expected " << true_ans.size() << std::endl;
        return 1;
    }

    // TODO: check pipes

    return 0;
}
