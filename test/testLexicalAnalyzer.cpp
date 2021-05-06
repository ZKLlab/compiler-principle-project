#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "MyCompiler/LexicalAnalyzer.h"

int analyze()
{
    typedef MyCompiler::SymbolType ST;

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
                std::cout << "(" << MyCompiler::getSymbolTypeName(token.getSymbolType()) << ", " << token.getValue() << ")"
                          << std::endl;
            }
        }
        catch (MyCompiler::LexicalError &err)
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
    if (argc == 1)
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
