#include "Token.h"
#include <string>
#include <iostream>

Token::Token(TokenType type, std::string description, int line) {
    this->token = type;
    this->description = description;
    this->startLine = line;
}

Token::Token(TokenType type, char description, int line) {
    this->token = type;
    this->description = description;
    this->startLine = line;
}

string Token::tokenToString(TokenType token) {
    switch(token) {
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON-DASH"; break;
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::Q_MARK: return "Q_MARK"; break;
        case TokenType::LEFT_PAREN: return "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::STRING: return "STRING"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        case TokenType::END: return "EOF"; break;
    }
    return "";
}

string Token::toString() {
    string tokenString;

    tokenString = "(" + tokenToString(token) + ",\"" + description + "\"," + to_string(startLine) + ")";
    return tokenString;
}
