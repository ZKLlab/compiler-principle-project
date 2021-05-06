//
// Created by 穆润东 on 2021/5/3.
//

#ifndef MY_COMPILER__GRAMMAR_TABLE_H
#define MY_COMPILER__GRAMMAR_TABLE_H

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "SymbolType.h"

namespace MyCompiler
{
    class GrammarTable
    {
        std::unordered_map<std::string, std::vector<std::vector<std::string>>> rule;
        std::unordered_set<std::string> non_terminator;
        std::unordered_map<std::string, std::unordered_set<SymbolType>> first;
        std::unordered_map<std::string, std::unordered_set<SymbolType>> follow;
        std::unordered_map<std::string, std::unordered_map<SymbolType, std::vector<std::string>>> table;

        void make_rule(const std::vector<std::string> &def);

        void make_first();

        void make_follow();

        void make_table();

    protected:

        explicit GrammarTable(const std::vector<std::string> &def);

        void clear();

        static std::string &trim(std::string &s);

        const auto &getTable()
        { return table; }
    };
}

#endif // MY_COMPILER__GRAMMAR_TABLE_H