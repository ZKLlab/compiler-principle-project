#include "MyCompiler/ThreeAddressCode.h"

void MyCompiler::traverseIdentsExpression(MyCompiler::Expression &ast,
                                          std::unordered_set<std::string> &usedIdents)
{
    traverseIdentsTerm(*ast.pTerm, usedIdents);
    for (auto &item : ast.vAddSubOpExpression)
        traverseIdentsTerm(item.second, usedIdents);
}

void MyCompiler::traverseIdentsTerm(MyCompiler::Term &ast,
                                    std::unordered_set<std::string> &usedIdents)
{
    traverseIdentsFactor(*ast.pFactor, usedIdents);
    for (auto &item : ast.vMulDivOpFactor)
        traverseIdentsFactor(item.second, usedIdents);
}

void MyCompiler::traverseIdentsFactor(MyCompiler::Factor &ast,
                                      std::unordered_set<std::string> &usedIdents)
{
    switch (ast.caseNum)
    {
        case 2:
            return traverseIdentsExpression(*ast.pExpression, usedIdents);
        case 0:
            usedIdents.insert(ast.pIdent->value);
    }
}

std::string MyCompiler::nextTempIdent(std::unordered_set<std::string> &usedIdents,
                                      int &tempIdentCounter)
{
    std::string result;
    do
    {
        std::ostringstream out;
        out << 't' << ++tempIdentCounter;
        result = out.str();
    }
    while (usedIdents.find(result) != usedIdents.end());
    usedIdents.insert(result);
    return result;
}

std::string MyCompiler::visitExpression(MyCompiler::Expression &ast,
                                        std::vector<std::array<std::string, 4>> &result,
                                        std::unordered_set<std::string> &usedIdents,
                                        int &tempIdentCounter)
{
    std::string aTerm = visitTerm(*ast.pTerm, result, usedIdents, tempIdentCounter);

    bool negative = ast.pAddSubOp != nullptr && ast.pAddSubOp->value == "-";
    if (!negative && ast.vAddSubOpExpression.empty())
        return aTerm;

    bool moreTerm = false;
    std::string temp;

    if (negative)
    {
        temp = nextTempIdent(usedIdents, tempIdentCounter);
        moreTerm = true;
        result.push_back({"*", "-1", aTerm, temp});
    }

    for (auto &item : ast.vAddSubOpExpression)
    {
        std::string secondTerm = visitTerm(item.second, result, usedIdents, tempIdentCounter);
        if (!moreTerm)
            temp = nextTempIdent(usedIdents, tempIdentCounter);
        result.push_back({item.first.value,
                          moreTerm ? temp : aTerm,
                          secondTerm,
                          temp});
        moreTerm = true;
    }

    return temp;
}

std::string MyCompiler::visitTerm(MyCompiler::Term &ast,
                                  std::vector<std::array<std::string, 4>> &result,
                                  std::unordered_set<std::string> &usedIdents,
                                  int &tempIdentCounter)
{
    std::string aFactor = visitFactor(*ast.pFactor, result, usedIdents, tempIdentCounter);

    if (ast.vMulDivOpFactor.empty())
        return aFactor;

    bool moreFactor = false;
    std::string temp;

    for (auto &item : ast.vMulDivOpFactor)
    {

        std::string aSecondFactor = visitFactor(item.second, result, usedIdents, tempIdentCounter);
        if (!moreFactor)
            temp = nextTempIdent(usedIdents, tempIdentCounter);
        result.push_back({item.first.value,
                          moreFactor ? temp : aFactor,
                          aSecondFactor,
                          temp});
        moreFactor = true;
    }

    return temp;
}

std::string MyCompiler::visitFactor(MyCompiler::Factor &ast,
                                    std::vector<std::array<std::string, 4>> &result,
                                    std::unordered_set<std::string> &usedIdents,
                                    int &tempIdentCounter)
{
    switch (ast.caseNum)
    {
        case 0:
            return ast.pIdent->value;
        case 1:
            return ast.pNumber->value;
        default:
            return visitExpression(*ast.pExpression, result, usedIdents, tempIdentCounter);
    }
}