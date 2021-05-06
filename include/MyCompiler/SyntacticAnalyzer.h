//
// Created by 穆润东 on 2021/5/6.
//

#ifndef COMPILER_PRINCIPLE_PROJECT_SYNTACTICANALYZER_H
#define COMPILER_PRINCIPLE_PROJECT_SYNTACTICANALYZER_H

#include <stack>
#include <string>
#include "GrammarTable.h"
#include "SymbolType.h"

using MyCompiler::SymbolType;

class SyntacticAnalyzer : private GrammarTable {

    std::stack<std::string> stack;

public:
    explicit SyntacticAnalyzer(const std::vector<std::string> &def): GrammarTable(def) {
        auto pos = def[0].find("::=");
        std::string tmp(def[0].substr(0, pos));

        tmp = trim(tmp).substr(1, tmp.length() -2);
        stack.push(tmp);
    }

    bool tryParse(std::istream &stream);

};


#endif //COMPILER_PRINCIPLE_PROJECT_SYNTACTICANALYZER_H
