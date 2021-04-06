#ifndef MY_COMPILER__LEXICAL_ANALYZER_H
#define MY_COMPILER__LEXICAL_ANALYZER_H

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
        enum class State
        {
            START, WORD, NUM, LT, GT, COLON
        };
        static const std::unordered_map<std::string, SymbolType> keywordsMap = {
                {"begin",     SymbolType::BEGIN},
                {"end",       SymbolType::END},
                {"if",        SymbolType::IF},
                {"then",      SymbolType::THEN},
                {"while",     SymbolType::WHILE},
                {"write",     SymbolType::WRITE},
                {"read",      SymbolType::READ},
                {"do",        SymbolType::DO},
                {"call",      SymbolType::CALL},
                {"const",     SymbolType::CONST},
                {"var",       SymbolType::VAR},
                {"procedure", SymbolType::PROC},
                {"odd",       SymbolType::ODD}
        };
        static const std::unordered_map<char, SymbolType> startCharsSymbolTypeMap = {
                {'+', SymbolType::PLUS},
                {'-', SymbolType::MINUS},
                {'*', SymbolType::TIMES},
                {'/', SymbolType::SLASH},
                {'=', SymbolType::EQL},
                {'#', SymbolType::NEQ},
                {'(', SymbolType::LPAREN},
                {')', SymbolType::RPAREN},
                {',', SymbolType::COMMA},
                {';', SymbolType::SEMICOLON},
                {'.', SymbolType::PERIOD}
        };
        static const std::unordered_map<char, State> startCharsStateMap = {
                {'<', State::LT},
                {'>', State::GT},
                {':', State::COLON}
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
                else if (startCharsSymbolTypeMap.find(c) != startCharsSymbolTypeMap.end())
                {
                    stream.get();
                    return Token(startCharsSymbolTypeMap.at(c), std::string(1, c));
                }
                else if (startCharsStateMap.find(c) != startCharsStateMap.end())
                {
                    stream.get();
                    state = startCharsStateMap.at(c);
                }
                else
                    throw LexicalError(stream.tellg() + std::ios::pos_type(1));
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
                    return Token(SymbolType::LEQ, "<=");
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
                    return Token(SymbolType::GEQ, ">=");
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
                    return Token(SymbolType::BECOMES, ":=");
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
                return Token(SymbolType::IDENT, buffer);
        }
        else if (state == State::NUM)
            return Token(SymbolType::NUMBER, buffer);
        else if (state == State::LT)
            return Token(SymbolType::LSS, "<");
        else if (state == State::GT)
            return Token(SymbolType::GTR, ">");
        else if (state == State::COLON)
            throw LexicalError(stream.tellg());
        else
            return Token(SymbolType::NUL);
    }
}

#endif // MY_COMPILER__LEXICAL_ANALYZER_H