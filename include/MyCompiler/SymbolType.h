#ifndef MY_COMPILER__SYMBOL_TYPE_H
#define MY_COMPILER__SYMBOL_TYPE_H

#include <unordered_map>

namespace MyCompiler {
    enum class SymbolType {
        NUL, IDENT, NUMBER,                                // (null), <id>, <number>,
        PLUS, MINUS, TIMES, SLASH,                         // "+", "-", "*", "/",
        EQL, NEQ, LSS, LEQ, GTR, GEQ,                      // "=", "#", "<", "<=", ">", ">=",
        LPAREN, RPAREN, COMMA, SEMICOLON, PERIOD, BECOMES, // "(", ")", ",", ";", ".", ":=",
        BEGIN, END, IF, THEN, WHILE, WRITE, READ, DO,      // (keywords)
        CALL, CONST, VAR, PROC, ODD
    };

    static const SymbolType &getSymbolTypeByName(const std::string &name) {
        static const std::unordered_map<std::string, SymbolType> nameSymbolTypeMap = {
                {"Nul",          SymbolType::NUL},
                {"Ident",        SymbolType::IDENT},
                {"Number",       SymbolType::NUMBER},
                {"Plus",         SymbolType::PLUS},
                {"Minus",        SymbolType::MINUS},
                {"Times",        SymbolType::TIMES},
                {"Slash",        SymbolType::SLASH},
                {"Eql",          SymbolType::EQL},
                {"Neq",          SymbolType::NEQ},
                {"Lss",          SymbolType::LSS},
                {"Leq",          SymbolType::LEQ},
                {"Gtr",          SymbolType::GTR},
                {"Geq",          SymbolType::GEQ},
                {"LParen",       SymbolType::LPAREN},
                {"RParen",       SymbolType::RPAREN},
                {"Comma",        SymbolType::COMMA},
                {"Semicolon",    SymbolType::SEMICOLON},
                {"Period",       SymbolType::PERIOD},
                {"Becomes",      SymbolType::BECOMES},
                {"BeginSym",     SymbolType::BEGIN},
                {"EndSym",       SymbolType::END},
                {"IfSym",        SymbolType::IF},
                {"ThenSym",      SymbolType::THEN},
                {"WhileSym",     SymbolType::WHILE},
                {"WriteSym",     SymbolType::WRITE},
                {"ReadSym",      SymbolType::READ},
                {"DoSym",        SymbolType::DO},
                {"CallSym",      SymbolType::CALL},
                {"ConstSym",     SymbolType::CONST},
                {"VarSym",       SymbolType::VAR},
                {"ProcedureSym", SymbolType::PROC},
                {"OddSym",       SymbolType::ODD}
        };
        return nameSymbolTypeMap.at(name);
    }

    static const std::string &getSymbolTypeName(const SymbolType &type) {
        static const std::unordered_map<SymbolType, std::string> symbolTypeNameMap = {
                {SymbolType::NUL,       "Nul"},
                {SymbolType::IDENT,     "Ident"},
                {SymbolType::NUMBER,    "Number"},
                {SymbolType::PLUS,      "Plus"},
                {SymbolType::MINUS,     "Minus"},
                {SymbolType::TIMES,     "Times"},
                {SymbolType::SLASH,     "Slash"},
                {SymbolType::EQL,       "Eql"},
                {SymbolType::NEQ,       "Neq"},
                {SymbolType::LSS,       "Lss"},
                {SymbolType::LEQ,       "Leq"},
                {SymbolType::GTR,       "Gtr"},
                {SymbolType::GEQ,       "Geq"},
                {SymbolType::LPAREN,    "LParen"},
                {SymbolType::RPAREN,    "RParen"},
                {SymbolType::COMMA,     "Comma"},
                {SymbolType::SEMICOLON, "Semicolon"},
                {SymbolType::PERIOD,    "Period"},
                {SymbolType::BECOMES,   "Becomes"},
                {SymbolType::BEGIN,     "BeginSym"},
                {SymbolType::END,       "EndSym"},
                {SymbolType::IF,        "IfSym"},
                {SymbolType::THEN,      "ThenSym"},
                {SymbolType::WHILE,     "WhileSym"},
                {SymbolType::WRITE,     "WriteSym"},
                {SymbolType::READ,      "ReadSym"},
                {SymbolType::DO,        "DoSym"},
                {SymbolType::CALL,      "CallSym"},
                {SymbolType::CONST,     "ConstSym"},
                {SymbolType::VAR,       "VarSym"},
                {SymbolType::PROC,      "ProcedureSym"},
                {SymbolType::ODD,       "OddSym"}
        };
        return symbolTypeNameMap.at(type);
    }
}

#endif // MY_COMPILER__SYMBOL_TYPE_H