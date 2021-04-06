#ifndef COMPILER_PRINCIPLE_PROJECT__LEXICAL_ANALYZER_H
#define COMPILER_PRINCIPLE_PROJECT__LEXICAL_ANALYZER_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include "Token.h"
#include "SymbolType.h"
#include "LexicalError.h"

namespace MyCompiler
{
    Token nextToken(std::istream &stream)
    {
        typedef SymbolType ST;
        enum class State
        {
            START, WORD, NUM, LT, GT, COLON
        };
        static const std::unordered_map<std::string, SymbolType> keywordsMap = {
                {"begin",     ST::BEGIN},
                {"end",       ST::END},
                {"if",        ST::IF},
                {"then",      ST::THEN},
                {"while",     ST::WHILE},
                {"write",     ST::WRITE},
                {"read",      ST::READ},
                {"do",        ST::DO},
                {"call",      ST::CALL},
                {"const",     ST::CONST},
                {"var",       ST::VAR},
                {"procedure", ST::PROC},
                {"odd",       ST::ODD}
        };

        std::string buffer;
        State state = State::START;
        while (stream.good())
        {
            if (state == State::START)
            {
                std::ws(stream);
                if (!stream.good())
                    break;
                char c = stream.peek();
                if (std::isalpha(c))
                {
                    buffer.push_back(stream.get());
                    state = State::WORD;
                }
                else if (std::isdigit(c))
                {
                    buffer.push_back(stream.get());
                    state = State::NUM;
                }
                else if (c == '+')
                {
                    stream.get();
                    return Token(ST::PLUS, "+");
                }
                else if (c == '-')
                {
                    stream.get();
                    return Token(ST::MINUS, "-");
                }
                else if (c == '*')
                {
                    stream.get();
                    return Token(ST::TIMES, "*");
                }
                else if (c == '/')
                {
                    stream.get();
                    return Token(ST::SLASH, "/");
                }
                else if (c == '=')
                {
                    stream.get();
                    return Token(ST::EQL, "=");
                }
                else if (c == '#')
                {
                    stream.get();
                    return Token(ST::NEQ, "#");
                }
                else if (c == '(')
                {
                    stream.get();
                    return Token(ST::LPAREN, "(");
                }
                else if (c == ')')
                {
                    stream.get();
                    return Token(ST::RPAREN, ")");
                }
                else if (c == ',')
                {
                    stream.get();
                    return Token(ST::COMMA, ",");
                }
                else if (c == ';')
                {
                    stream.get();
                    return Token(ST::SEMICOLON, ";");
                }
                else if (c == '.')
                {
                    stream.get();
                    return Token(ST::PERIOD, ".");
                }
                else if (c == ':')
                {
                    stream.get();
                    state = State::COLON;
                }
                else if (c == '<')
                {
                    stream.get();
                    state = State::LT;
                }
                else if (c == '>')
                {
                    stream.get();
                    state = State::GT;
                }
                else
                {
                    throw LexicalError(stream.tellg() + std::ios::pos_type(1));
                }
            }
            else if (state == State::WORD)
            {
                char c = stream.peek();
                if (std::isalnum(c))
                    buffer.push_back(stream.get());
                else
                    break;
            }
            else if (state == State::NUM)
            {
                char c = stream.peek();
                if (std::isdigit(c))
                    buffer.push_back(stream.get());
                else
                    break;
            }
            else if (state == State::LT)
            {
                char c = stream.peek();
                if (c == '=')
                {
                    stream.get();
                    return Token(ST::LEQ, "<=");
                }
                else
                    break;
            }
            else if (state == State::GT)
            {
                char c = stream.peek();
                if (c == '=')
                {
                    stream.get();
                    return Token(ST::GEQ, ">=");
                }
                else
                    break;
            }
            else // if (state == State::COLON)
            {
                char c = stream.peek();
                if (c == '=')
                {
                    stream.get();
                    return Token(ST::BECOMES, ":=");
                }
                else
                    break;
            }
        }
        if (state == State::WORD)
        {
            std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
            auto search = keywordsMap.find(buffer);
            if (search != keywordsMap.end())
                return Token(search->second, buffer);
            else
                return Token(ST::IDENT, buffer);
        }
        else if (state == State::NUM)
            return Token(ST::NUMBER, buffer);
        else if (state == State::LT)
            return Token(ST::LSS, "<");
        else if (state == State::GT)
            return Token(ST::GTR, ">");
        else if (state == State::COLON)
            throw LexicalError(stream.tellg());
        else
            return Token(ST::NUL);
    }
}

#endif // COMPILER_PRINCIPLE_PROJECT__LEXICAL_ANALYZER_H