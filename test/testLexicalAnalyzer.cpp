#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "MyCompiler/LexicalAnalyzer.h"

int analyze()
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
    std::string line;
    int lineNum = 0;

    while (std::getline(std::cin, line))
    {
        lineNum += 1;
        std::istringstream lineStream(line);
        try
        {
            while (true)
            {
                auto token = MyCompiler::nextToken(lineStream);
                if (token.getSymbolType() == ST::NUL)
                    break;
                std::cout << "(" << symbolTypeNameMap.at(token.getSymbolType()) << ", " << token.getValue() << ")"
                          << std::endl;
            }
        }
        catch (LexicalError &err)
        {
            std::clog << line << std::endl;
            std::clog << std::setw(int(err.getOffset())) << "^" << std::endl;
            std::clog << "Line [" << lineNum << "]: LexicalError: " << err.what() << std::endl;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 0)
        return analyze();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            int code = analyze();
            if (code > 0)
                return code;
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
