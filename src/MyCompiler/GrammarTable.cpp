//
// Created by 穆润东 on 2021/5/3.
//

#include "MyCompiler/GrammarTable.h"

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

std::string &ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                           [](char c)
                           {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(s.begin(), it);
    return s;
}

std::string &rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                           [](char c)
                           {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(it.base(), s.end());
    return s;
}

std::string &MyCompiler::GrammarTable::trim(std::string &s)
{
    return ltrim(rtrim(s));
}

using MyCompiler::getSymbolTypeByName;
using MyCompiler::getSymbolTypeName;

void MyCompiler::GrammarTable::clear()
{
    rule.clear();
    non_terminator.clear();
    first.clear();
    follow.clear();
}

MyCompiler::GrammarTable::GrammarTable(const vector<std::string> &def)
{
    if (!rule.empty()) return;
    make_rule(def);
    make_first();
    make_follow();
    make_table();
}

void MyCompiler::GrammarTable::make_rule(const vector<string> &def)
{
    bool init = true;
    for (const auto &s : def)
    {
        auto delimiter = "::=";
        auto pos = s.find(delimiter);
        string tmp(s.substr(0, pos));
        auto key = trim(tmp);
        key = key.substr(1, key.length() - 2);
        non_terminator.insert(key);

        if (init)
        {
            // Normally it's '$', but we will use <Nul> instead.
            unordered_set<SymbolType> start({SymbolType::NUL});
            follow[key] = start;
            init = false;
        }

        auto raw(s.substr(pos + 3, s.length()));

        vector<vector<string>> val;
        std::stringstream ss(raw);
        string part;

        std::regex reg("<.*?>");

        while (getline(ss, part, '|'))
        {
            vector<string> frac;
            auto words_begin = std::sregex_iterator(part.begin(), part.end(), reg);
            for (auto t = words_begin; t != std::sregex_iterator(); ++t)
            {
                string k(t->str());
                k = k.substr(1, k.size() - 2);
                frac.push_back(k);
            }
            val.push_back(frac);
        }
        rule[key] = val;
    }
////   Debug
//    std::cout << "RULE DEBUG: " << std::endl;
//    for (const auto &map : rule) {
//        auto key = map.first;
//        auto val = map.second;
//        std::cout << "\t";
//        std::cout << "[@" << key << "]: " << std::endl;
//        std::cout << "\t\t| ";
//        for (const auto &v : val) {
//            for (const auto &f : v) {
//                std::cout << f << " ";
//            }
//            std::cout << "| ";
//        }
//        std::cout << std::endl;
//    }
}

void MyCompiler::GrammarTable::make_first()
{
    for (const auto &t : non_terminator)
    {
        unordered_set<SymbolType> s;
        first[t] = s;
    }

    for (auto &it : rule)
    {
        string left = it.first;
        auto right = it.second;
        for (const auto &v : right)
        {
            string fst = v[0];
            if (non_terminator.count(fst) == 0)
                first[left].insert(getSymbolTypeByName(fst));
        }
    }

    bool changed = true;
    while (changed)
    {
        changed = false;

        for (const auto &it : rule)
        {
            string left = it.first;
            auto right = it.second;
            for (const auto &v: right)
            {
                bool nullable = true;
                unordered_set<SymbolType> fstTmp;
                for (const auto &key: v)
                {
                    if (non_terminator.count(key) == 0)
                    {
                        fstTmp.insert(getSymbolTypeByName(key));
                        nullable = false;
                        break;
                    }
                    auto tmp = first.at(key);
                    fstTmp.insert(tmp.begin(), tmp.end());
                    fstTmp.erase(SymbolType::NUL);
                    if (tmp.count(SymbolType::NUL) == 0)
                    {
                        nullable = false;
                        break;
                    }
                }
                int prevLen = first[left].size();
                if (nullable)
                {
                    first[left].insert(SymbolType::NUL);
                }
                first[left].insert(fstTmp.begin(), fstTmp.end());
                if (prevLen != first[left].size()) changed = true;
            }
        }
    }

////    Debug
//    std::cout << "FIRST DEBUG:" << std::endl;
//    for (const auto &fst: first) {
//        std::cout << "\t";
//        std::cout << "[@" << fst.first << "]: \n";
//        std::cout << "\t\t";
//        for (const auto &snd: fst.second) {
//            std::cout << getSymbolTypeName(snd) << " ";
//        }
//        std::cout << std::endl;
//    }
}

void MyCompiler::GrammarTable::make_follow()
{
    for (const auto &t : non_terminator)
    {
        if (follow.count(t) != 0) continue;
        unordered_set<SymbolType> s;
        follow[t] = s;
    }

    for (auto &it : rule)
    {
        string left = it.first;
        auto right = it.second;
        for (const auto &v : right)
        {
            string fol = v[v.size() - 1];
            if (non_terminator.count(fol) == 0)
                follow[left].insert(getSymbolTypeByName(fol));
        }
    }

    bool changed = true;
    while (changed)
    {
        changed = false;

        for (const auto &it : rule)
        {
            string left = it.first;
            auto right = it.second;
            for (const auto &v: right)
            {
                bool nullable = true;
                unordered_set<SymbolType> folTmp;
                for (auto i = v.rbegin(); i != v.rend(); ++i)
                {
                    auto key = *i;

                    if (non_terminator.count(key) == 0)
                    {
                        nullable = false;
                        folTmp.clear();
                        folTmp.insert(getSymbolTypeByName(key));
                    }
                    else
                    {
                        int prevLen = follow[key].size();
                        follow[key].insert(folTmp.begin(), folTmp.end());
                        if (nullable)
                        {
                            follow[key].insert(follow[left].begin(), follow[left].end());
                        }
                        follow[key].erase(SymbolType::NUL);
                        if (prevLen != follow[key].size()) changed = true;

                        if (first[key].count(SymbolType::NUL) == 0)
                        {
                            nullable = false;
                            folTmp.clear();
                        }
                        folTmp.insert(first[key].begin(), first[key].end());
                    }
                }
            }
        }
    }

////      Debug
//    std::cout << "FOLLOW DEBUG:" << std::endl;
//    for (const auto &fol: follow) {
//        std::cout << "\t";
//        std::cout << "[@" << fol.first << "]: \n";
//        std::cout << "\t\t";
//        for (const auto &snd: fol.second) {
//            std::cout << getSymbolTypeName(snd) << " ";
//        }
//        std::cout << std::endl;
//    }
}

void MyCompiler::GrammarTable::make_table()
{
    for (const auto &r : rule)
    {
        string left = r.first;
        auto rights = r.second;
        unordered_map<SymbolType, vector<string>> tmp;
        for (const auto &right : rights)
        {
            for (const auto &head : right)
            {
                if (non_terminator.count(head) == 0)
                {
                    auto head_term = getSymbolTypeByName(head);
                    if (head_term == SymbolType::NUL)
                    {
                        for (const auto &fol: follow[left])
                        {
                            tmp[fol] = right;
                        }
                    }
                    else tmp[head_term] = right;
                    break;
                }
                else
                {
                    auto head_non_term = first[head];
                    bool nullable = false;
                    for (const auto &h: head_non_term)
                    {
                        if (h != SymbolType::NUL)
                        {
                            tmp[h] = right;
                        }
                        else
                        {
                            nullable = true;
                        }
                    }
                    if (!nullable) break;
                }
            }
        }
        table[left] = tmp;
    }

////    Debug
//    std::cout << "Table Debug:" << std::endl;
//    for (const auto &col: table) {
//        std::cout << "\t";
//        std::cout << "[@" << col.first << "]: \n";
//        for (const auto &item: col.second) {
//            std::cout << "\t\t" << getSymbolTypeName(item.first) << " -> ";
//            for (const auto &t:item.second)
//                std::cout << t << " ";
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//    }
}