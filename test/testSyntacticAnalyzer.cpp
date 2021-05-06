//
// Created by 穆润东 on 2021/5/3.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "MyCompiler/SyntacticAnalyzer.h"

int main(int argc, char *argv[])
{
    std::ifstream in;
    in.open("./src/definition/definition.bnf");
    if (!in.is_open())
    {
        throw std::runtime_error("definition.bnf is not found");
    }

    std::vector<std::string> def;
    std::string buffer;
    while (!in.eof())
    {
        getline(in, buffer);
        auto tmp = buffer;
        def.push_back(tmp);
    }
    MyCompiler::SyntacticAnalyzer syntacticAnalyzer(def);
    std::ifstream ss;
    ss.open("./test/Cases/6_Add/6_Add.in");

    if (ss.is_open()) std::cout << syntacticAnalyzer.tryParse(ss);
    else std::cout << "cannot find file" << std::endl;
}