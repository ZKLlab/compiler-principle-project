#include <fstream>
#include <iomanip>
#include <iostream>
#include "MyCompiler/RecursiveDescentParser.h"
#include "MyCompiler/Util/AstToYaml.h"

int parse()
{
    MyCompiler::RecursiveDescentParser parser(std::cin);
    try
    {
        parser.start();
        auto pAst = parser.parse<MyCompiler::Program>();
        parser.finish();
        std::cout << MyCompiler::Util::astToYaml(*pAst) << std::endl;
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
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        return parse();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            int code = parse();
            if (code > 0)
                return code;
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
