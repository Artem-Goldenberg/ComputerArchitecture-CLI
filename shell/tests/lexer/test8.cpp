#include "lexer.h"

int main() {
    Lexer lex;
    std::string str = "cat helloWorld.txt|grep 'Hello \"some\" world!' |xclip -r -selection clipboard ";
    std::vector<Token> true_ans;
    true_ans.push_back(Token(TokenType::mString, "cat"));
    true_ans.push_back(Token(TokenType::mString, "helloWorld.txt"));
    true_ans.push_back(Token(TokenType::mPipe, ""));
    true_ans.push_back(Token(TokenType::mString, "grep"));
    true_ans.push_back(Token(TokenType::mSingleQuotes, "Hello \"some\" world!"));
    true_ans.push_back(Token(TokenType::mPipe, ""));
    true_ans.push_back(Token(TokenType::mString, "xclip"));
    true_ans.push_back(Token(TokenType::mString, "-r"));
    true_ans.push_back(Token(TokenType::mString, "-selection"));
    true_ans.push_back(Token(TokenType::mString, "clipboard"));

    std::vector<Token> lex_ans = lex.tokenize(str);
    if( true_ans.size() == lex_ans.size() ) {
        for(int pos = 0; pos < true_ans.size(); pos++) {
            if(true_ans[pos].getTokenType() != lex_ans[pos].getTokenType() ||
               true_ans[pos].getData() != lex_ans[pos].getData() ) return 1;
        }
    } else {
        return 1;
    }


    return 0;
}
