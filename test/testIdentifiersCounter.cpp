#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "MyCompiler/LexicalAnalyzer.h"

void countIdentifiers()
{
    std::vector<std::string> sequence;
    std::unordered_map<std::string, int> countMap;

    while (std::cin.good())
    {
        auto token = MyCompiler::nextToken(std::cin);
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

    for (const std::string &id : sequence)
        std::cout << "(" << id << ": " << countMap[id] << ")" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc == 0)
        countIdentifiers();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            countIdentifiers();
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
