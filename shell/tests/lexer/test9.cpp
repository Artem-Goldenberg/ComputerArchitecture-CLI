#include "lexer.h"

int main() {
    Lexer lex;
    std::string str = "'Venya'\"D'rkin\"|the_best'one''";
    std::vector<Token> true_ans;
    true_ans.push_back(Token(TokenType::mSingleQuotes, "Venya"));
    true_ans.push_back(Token(TokenType::mDoubleQuotes, "D'rkin"));
    true_ans.push_back(Token(TokenType::mPipe, ""));
    true_ans.push_back(Token(TokenType::mString, "the_best"));
    true_ans.push_back(Token(TokenType::mSingleQuotes, "one"));
    true_ans.push_back(Token(TokenType::mSingleQuotes, ""));

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
