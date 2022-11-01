#include "lexer.h"

int main() {
    Lexer lex;
    std::string str = "   cd      some_dir   ";
    std::vector<Token> true_ans;
    true_ans.push_back(Token(TokenType::mString, "cd"));
    true_ans.push_back(Token(TokenType::mString, "some_dir"));

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
