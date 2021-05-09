#include <fstream>
#include <iomanip>
#include <iostream>
#include "MyCompiler/RecursiveDescentParser.h"

void calc()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream in(line);
        try
        {
            MyCompiler::RecursiveDescentParser parser(in);
            auto pAst = parser.parse<MyCompiler::Expression>();
            parser.finish();
            if (pAst->pAddSubOp == nullptr && pAst->pTerm->pFactor->caseNum == 1 &&
                pAst->pTerm->vMulDivOpFactor.empty() && pAst->vAddSubOpExpression.empty())
                std::cout << pAst->pTerm->pFactor->pNumber->value << std::endl;
            else
                std::cout << "expressions with variable(s)" << std::endl;
        }
        catch (MyCompiler::LexicalError &err)
        {
            std::cout << err.what() << std::endl;
        }
        catch (MyCompiler::SyntaxError &err)
        {
            std::cout << err.what() << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        calc();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            calc();
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
