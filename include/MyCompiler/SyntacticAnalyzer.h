//
// Created by 穆润东 on 2021/5/6.
//

#ifndef MY_COMPILER__SYNTACTIC_ANALYZER_H
#define MY_COMPILER__SYNTACTIC_ANALYZER_H

#include <iostream>
#include <stack>
#include "GrammarTable.h"
#include "LexicalAnalyzer.h"
#include "SymbolType.h"

namespace MyCompiler
{

    class SyntacticAnalyzer : private GrammarTable
    {
        std::stack<std::string> stack;
    public:
        explicit SyntacticAnalyzer(const std::vector<std::string> &def) : GrammarTable(def)
        {
            auto pos = def[0].find("::=");
            std::string tmp(def[0].substr(0, pos));

            tmp = trim(tmp).substr(1, tmp.length() - 2);
            stack.push(tmp);
        }

        bool tryParse(std::istream &stream);
    };
}

#endif // MY_COMPILER__SYNTACTIC_ANALYZER_H