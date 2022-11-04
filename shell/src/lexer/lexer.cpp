#include "lexer.h"

Lexer::Lexer() {}
Lexer::~Lexer() {}

std::vector<Token> Lexer::tokenize(std::string &in) {
    int cur_token_begin = 0;
    std::vector<Token> ans;

    for(int pos = 0; pos < in.length(); pos++) {
        switch(in[pos]) {
            case ' ':
                if(cur_token_begin != pos) {
                    ans.push_back(Token(TokenType::mString, std::string(in.begin()+cur_token_begin, in.begin()+pos)));
                }
                cur_token_begin = pos+1;
                continue;

            case '=':
                if(cur_token_begin != pos) {
                    ans.push_back(Token(TokenType::mString, std::string(in.begin()+cur_token_begin, in.begin()+pos)));
                }
                ans.push_back(Token(TokenType::mEquals, ""));
                cur_token_begin = pos+1;
                continue;

            case '|':
                if(cur_token_begin != pos) {
                    ans.push_back(Token(TokenType::mString, std::string(in.begin()+cur_token_begin, in.begin()+pos)));
                }
                ans.push_back(Token(TokenType::mPipe, ""));
                cur_token_begin = pos+1;
                continue;

            case '"':
            {
                if(cur_token_begin != pos) {
                    ans.push_back(Token(TokenType::mString, std::string(in.begin()+cur_token_begin, in.begin()+pos)));
                }

                int next_dquote = in.find('"', pos+1);

                if( next_dquote == std::string::npos) {
                    ans.push_back(Token(TokenType::mDoubleQuotes, std::string(in.begin()+pos+1, in.end())));
                    pos = in.size();
                    cur_token_begin = in.size();
                } else {
                    ans.push_back(Token(TokenType::mDoubleQuotes, std::string(in.begin()+pos+1, in.begin()+next_dquote)));
                    pos = next_dquote;
                    cur_token_begin = next_dquote+1;
                }
                continue;
            }

            case '\'':
            {
                if(cur_token_begin != pos) {
                    ans.push_back(Token(TokenType::mString, std::string(in.begin()+cur_token_begin, in.begin()+pos)));
                }

                int next_dquote = in.find('\'', pos+1);

                if( next_dquote == std::string::npos) {
                    ans.push_back(Token(TokenType::mSingleQuotes, std::string(in.begin()+pos+1, in.end())));
                    pos = in.size();
                    cur_token_begin = in.size();
                } else {
                    ans.push_back(Token(TokenType::mSingleQuotes, std::string(in.begin()+pos+1, in.begin()+next_dquote)));
                    pos = next_dquote;
                    cur_token_begin = next_dquote+1;
                }
                continue;
            }

            default:
                // Nothing to do
                break;
        }
    }
    if( cur_token_begin != in.size() ) {
        ans.push_back(Token(TokenType::mString, std::string(in.begin()+cur_token_begin, in.end())));
    }

    return ans;
}