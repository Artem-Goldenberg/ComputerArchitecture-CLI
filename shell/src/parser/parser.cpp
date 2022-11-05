#include "parser.h"

#include <iostream>

Parser::Parser() {}

Parser::~Parser() {}

std::variant<std::vector<CommandData>, std::string> Parser::parse(std::vector<Token> &t) {
    std::vector<CommandData> ans;

    CommandData current_command = CommandData();

    for(int token_num = 0; token_num < t.size(); token_num++) {
        Token token = t[token_num];
        if(token.getTokenType() == TokenType::mPipe) return "no input before |";
        if(token.getTokenType() == TokenType::mEquals) return "equality error";

        if(token_num + 1 < t.size()) {
            switch (t[token_num+1].getTokenType()) {
                case mEquals:
                    if(token.getTokenType() != TokenType::mString) return "inappropriate variable name";
                    if( token_num+2 == t.size() ) return "incomplete equality";
                    if( t[token_num+2].getTokenType() == TokenType::mPipe) return "incomplete equality";
                    if( t[token_num+2].getTokenType() == TokenType::mEquals) return "unknown operand '=='";
                    if(current_command.getName() != "") {
                        current_command.addArgument(token.getData());
                        current_command.addArgument("=");
                        current_command.addArgument(t[token_num+2].getData());
                    } else {
                        current_command.setName("=");
                        current_command.addArgument(token.getData());
                        current_command.addArgument(t[token_num+2].getData());
                        ans.push_back(current_command);
                        current_command = CommandData();
                    }
                    token_num+=2;
                    // на a=b не работает, на 23 строчке уже проверялось это условие по идее
//                    if(token_num+1 == t.size()) return "incomplete equality";
                    break;

                case mPipe:
                {
                    if(current_command.getName() == "") {
                        if( token.getData() == "" ) return "command name cannot be empty";
                        current_command.setName(token.getData());
                    } else {
                        current_command.addArgument(token.getData());
                    }

                    Pipe* transition = new Pipe();
                    std::shared_ptr<Pipe> p(transition);
                    current_command.setOutputPipe(p);
                    ans.push_back(current_command);
                    current_command = CommandData(p);
                    token_num++;
                    if(token_num+1 == t.size()) return "nowhere to transfer";
                    break;
                }

                default:
                    if(current_command.getName() == "") {
                        if( token.getData() == "" ) return "command name cannot be empty";
                        current_command.setName(token.getData());
                    } else {
                        current_command.addArgument(token.getData());
                    }
                    break;
            }
        } else {
            if(token.getTokenType() == TokenType::mPipe) return "nowhere to transfer";

            if(current_command.getName() == "") {
                if( token.getData() == "" ) return "command name cannot be empty";
                current_command.setName(token.getData());
            } else {
                current_command.addArgument(token.getData());
            }
            ans.push_back(current_command);
        }
    }

    return ans;
}
