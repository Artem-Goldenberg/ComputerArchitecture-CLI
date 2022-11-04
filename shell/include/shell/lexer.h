#include <vector>
#include <string>

#include "token.h"

class Lexer {
    public:
        Lexer();
        ~Lexer();

        std::vector<Token> tokenize(std::string &in);
};