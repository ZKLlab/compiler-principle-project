#ifndef MY_COMPILER__THREE_ADDRESS_CODE_H
#define MY_COMPILER__THREE_ADDRESS_CODE_H

#include <array>
#include <sstream>
#include <unordered_set>
#include <vector>
#include "AbstractSyntaxTree.h"

namespace MyCompiler
{
    void traverseIdentsExpression(Expression &ast, std::unordered_set<std::string> &usedIdents);

    void traverseIdentsTerm(Term &ast, std::unordered_set<std::string> &usedIdents);

    void traverseIdentsFactor(Factor &ast, std::unordered_set<std::string> &usedIdents);

    std::string nextTempIdent(std::unordered_set<std::string> &usedIdents,
                              int &tempIdentCounter);

    std::string visitExpression(
            Expression &ast,
            std::vector<std::array<std::string, 4>> &result,
            std::unordered_set<std::string> &usedIdents,
            int &tempIdentCounter);

    std::string visitTerm(
            Term &ast,
            std::vector<std::array<std::string, 4>> &result,
            std::unordered_set<std::string> &usedIdents,
            int &tempIdentCounter);

    std::string visitFactor(
            Factor &ast,
            std::vector<std::array<std::string, 4>> &result,
            std::unordered_set<std::string> &usedIdents,
            int &tempIdentCounter);
}

#endif // MY_COMPILER__THREE_ADDRESS_CODE_H