#include "token.h"

Token::Token(TokenType t, std::string data) :
    m_type(t), m_data(data) {}

Token::~Token() {}

TokenType Token::getTokenType() {
    return m_type;
}

std::string Token::getData() {
    return m_data;
}
