#include <array>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
#include "MyCompiler/RecursiveDescentParser.h"
#include "MyCompiler/ThreeAddressCode.h"

int generate()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::vector<std::array<std::string, 4>> result;
        std::unordered_set<std::string> usedIdents;
        std::istringstream in(line);
        int counter = 0;
        MyCompiler::RecursiveDescentParser parser(in);
        try
        {
            parser.start();
            auto pAst = parser.parse<MyCompiler::Expression>();
            parser.finish();

            MyCompiler::traverseIdentsExpression(*pAst, usedIdents);
            std::cout << MyCompiler::visitExpression(*pAst, result, usedIdents, counter)
                      << "=" << line << std::endl;

            for (auto &item : result)
                std::cout << "(" << item[0] << ", " << item[1] << ", " << item[2] << ", " << item[3] << ")"
                          << std::endl;
        }
        catch (MyCompiler::LexicalError &err)
        {
            std::cerr << err.what() << std::endl;
            return 1;
        }
        catch (MyCompiler::SyntaxError &err)
        {
            std::cerr << err.what() << std::endl;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        return generate();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            int code = generate();
            if (code > 0)
                return code;
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}