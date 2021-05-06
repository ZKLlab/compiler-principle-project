#include <fstream>
#include <iomanip>
#include <iostream>
#include "MyCompiler/RecursiveDescentParser.h"
#include "MyCompiler/Util/AstToYaml.h"

volatile void *sink;

void parse()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream in(line);
        try
        {
            MyCompiler::RecursiveDescentParser parser(in);
            auto pAst = parser.parse<MyCompiler::Condition>();
            parser.finish();
            sink = (void *) pAst.get();
            std::cout << "ok" << std::endl;
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
        parse();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            parse();
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}
