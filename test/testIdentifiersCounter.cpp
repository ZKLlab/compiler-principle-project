#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "MyCompiler/LexicalAnalyzer.h"

int countIdentifiers()
{
    std::vector<std::string> sequence;
    std::unordered_map<std::string, int> countMap;
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
                if (token.getSymbolType() == MyCompiler::SymbolType::NUL)
                    break;
                if (token.getSymbolType() == MyCompiler::SymbolType::IDENT)
                {
                    auto search = countMap.find(token.getValue());
                    if (search != countMap.end())
                        countMap[token.getValue()] = search->second + 1;
                    else
                    {
                        sequence.push_back(token.getValue());
                        countMap[token.getValue()] = 1;
                    }
                }
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

    for (const std::string &id : sequence)
        std::cout << "(" << id << ": " << countMap[id] << ")" << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 0)
        return countIdentifiers();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            int code = countIdentifiers();
            if (code > 0)
                return code;
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
