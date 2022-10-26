#include <string>

#pragma once
enum TokenType {
    mEquals = 0,
    mPipe = 1,
    mString = 2,
    mSingleQuotes = 3,
    mDoubleQuotes = 4,
};

class Token {
    public:
        Token(TokenType t, std::string data);
        ~Token();

        TokenType getTokenType();
        std::string getData();

    private:
        TokenType m_type;
        std::string m_data;
};