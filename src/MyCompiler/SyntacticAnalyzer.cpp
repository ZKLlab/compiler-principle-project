//
// Created by 穆润东 on 2021/5/6.
//

#include "MyCompiler/SyntacticAnalyzer.h"

using std::string;

bool MyCompiler::SyntacticAnalyzer::tryParse(std::istream &stream)
{
    MyCompiler::Token now(SymbolType::NUL);
    while (!stack.empty())
    {
        auto top = stack.top();
        while (top == getSymbolTypeName(now.getSymbolType()))
        {
            stack.pop();
            if (stack.empty()) break;
            top = stack.top();
            now = nextToken(stream);
        }
        if (stack.empty()) break;
        if (now.getSymbolType() == SymbolType::NUL)
        {
            now = nextToken(stream);
        }
        stack.pop();

        auto type = now.getSymbolType();
        auto table = getTable();

        if (table[top].count(type) == 0)
        {
            return false;
        }
        auto vec = table[top][type];
        for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        {
            if (*it != "Nul") stack.push(*it);
        }
////     Debug
//        std::cout << "[@Token]: \t" << getSymbolTypeName(type) << std::endl;
//        std::cout << "[@Stack]:" << std::endl;
//        std::cout << "\t";
//        std::stack<string> debug(stack);
//        while (!debug.empty()) {
//            std::cout << debug.top() << " ";
//            debug.pop();
//        }
//        std::cout << std::endl;
//        std::cout << "\t^" << std::endl;
    }
    return true;
}
