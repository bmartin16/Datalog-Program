#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    END,
    UNDEFINED
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    string description;
    int startLine;
    TokenType token;

public:
    Token(TokenType type, std::string description, int line);
    Token(TokenType type, char description, int line);
    string tokenToString(TokenType token);
    string toString();
    TokenType getTokenType();
    string getDescription();

    // TODO: add other needed methods
};

#endif // TOKEN_H

