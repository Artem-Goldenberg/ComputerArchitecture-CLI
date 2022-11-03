#include "parser.h"
#include <iostream>

int main() {
    // init test input
    Parser parser;
    std::vector<Token> in_tokens; // "prime-run" steam-runtime | mygrep 'Error' "Warning" | "grep missing lib:" client_agent.so
    in_tokens.push_back(Token(TokenType::mDoubleQuotes, "prime-run"));
    in_tokens.push_back(Token(TokenType::mString, "steam-runtime"));
    in_tokens.push_back(Token(TokenType::mPipe, ""));
    in_tokens.push_back(Token(TokenType::mString, "mygrep"));
    in_tokens.push_back(Token(TokenType::mSingleQuotes, "Error"));
    in_tokens.push_back(Token(TokenType::mDoubleQuotes, "Warning"));
    in_tokens.push_back(Token(TokenType::mPipe, ""));
    in_tokens.push_back(Token(TokenType::mDoubleQuotes, "grep missing lib:"));
    in_tokens.push_back(Token(TokenType::mString, "client_agent.so"));

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
        CommandData command = CommandData("prime-run");
        command.addArgument("steam-runtime");
        true_ans.push_back(command);
    }
    {
        CommandData command = CommandData("mygrep");
        command.addArgument("Error");
        command.addArgument("Warning");
        true_ans.push_back(command);
    }
    {
        CommandData command = CommandData("grep missing lib:");
        command.addArgument("client_agent.so");
        true_ans.push_back(command);
    }

    // check names&args
    if(true_ans.size() == parse_ans.size()) {
        for(int pos = 0; pos < true_ans.size(); pos++) {
            if(true_ans[pos].getName() != parse_ans[pos].getName() ) std::cout << "Got name \"" << parse_ans[pos].getName() << "\", expected \"" << true_ans[pos].getName() << "\"" << std::endl;
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
