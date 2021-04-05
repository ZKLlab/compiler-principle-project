#include <fstream>
#include <iostream>
#include <unordered_map>
#include "MyCompiler/LexicalAnalyzer.h"

void analyze()
{
    typedef MyCompiler::SymbolType ST;
    static const std::unordered_map<ST, std::string> symbolTypeNameMap = {
            {ST::NUL,       "nul"},
            {ST::IDENT,     "ident"},
            {ST::NUMBER,    "number"},
            {ST::PLUS,      "plus"},
            {ST::MINUS,     "minus"},
            {ST::TIMES,     "times"},
            {ST::SLASH,     "slash"},
            {ST::EQL,       "eql"},
            {ST::NEQ,       "neq"},
            {ST::LSS,       "lss"},
            {ST::LEQ,       "leq"},
            {ST::GTR,       "gtr"},
            {ST::GEQ,       "geq"},
            {ST::LPAREN,    "lparen"},
            {ST::RPAREN,    "rparen"},
            {ST::COMMA,     "comma"},
            {ST::SEMICOLON, "semicolon"},
            {ST::PERIOD,    "period"},
            {ST::BECOMES,   "becomes"},
            {ST::BEGIN,     "beginsym"},
            {ST::END,       "endsym"},
            {ST::IF,        "ifsym"},
            {ST::THEN,      "thensym"},
            {ST::WHILE,     "whilesym"},
            {ST::WRITE,     "writesym"},
            {ST::READ,      "readsym"},
            {ST::DO,        "dosym"},
            {ST::CALL,      "callsym"},
            {ST::CONST,     "constsym"},
            {ST::VAR,       "varsym"},
            {ST::PROC,      "proceduresym"},
            {ST::ODD,       "oddsym"}
    };

    while (std::cin.good())
    {
        auto token = MyCompiler::nextToken(std::cin);
        if (token.getSymbolType() == ST::NUL)
            break;
        std::cout << "(" << symbolTypeNameMap.at(token.getSymbolType()) << ", " << token.getValue() << ")" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 0)
        analyze();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            analyze();
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
