#include "MyCompiler/Util/AstToYaml.h"

std::string MyCompiler::Util::astToYaml(Program &ast)
{
    std::vector<std::pair<int, std::string>> items;
    processAst<Program>(ast, 0, items, "program");
    std::ostringstream out;
    for (auto &item : items)
        out << std::string(item.first * 2, ' ') << item.second << std::endl;
    return out.str();
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Program>(
        Program &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, name + ":");
    processAst(*ast.pBlock, level + 1, items, "block");
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Block>(
        Block &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, name + ":");
    if (ast.pConstDeclaration != nullptr)
        processAst(*ast.pConstDeclaration, level + 1, items, "const-declaration");
    if (ast.pVarDeclaration != nullptr)
        processAst(*ast.pVarDeclaration, level + 1, items, "var-declaration");
    if (!ast.vProcedureDeclaration.empty())
    {
        items.emplace_back(level + 1, "procedure-declarations:");
        for (ProcedureDeclaration &subAst : ast.vProcedureDeclaration)
            processAst(subAst, level + 2, items, "");
    }
    processAst(*ast.pStatement, level + 1, items, "");
}

template <>
void MyCompiler::Util::processAst<MyCompiler::ConstDeclaration>(
        ConstDeclaration &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, name + ":");
    for (ConstDefinition &subAst : ast.vConstDefinition)
        processAst(subAst, level + 1, items, "");
}

template <>
void MyCompiler::Util::processAst<MyCompiler::ConstDefinition>(
        ConstDefinition &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, std::string("- ident: \"") + ast.pIdent->value + "\"");
    items.emplace_back(level, std::string("  number: ") + ast.pNumber->value);
}

template <>
void MyCompiler::Util::processAst<MyCompiler::VarDeclaration>(
        VarDeclaration &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, name + ":");
    for (Ident &subAst : ast.vIdent)
        items.emplace_back(level + 1, std::string("- ident: \"") + subAst.value + "\"");
}

template <>
void MyCompiler::Util::processAst<MyCompiler::ProcedureDeclaration>(
        ProcedureDeclaration &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, std::string("- ident: \"") + ast.pIdent->value + "\"");
    processAst(*ast.pBlock, level + 1, items, "block");
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Statement>(
        Statement &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    int offset = name.empty() ? 0 : 1;
    switch (ast.caseNum)
    {
        case 0:
            items.emplace_back(level, name + "assignment-statement:");
            items.emplace_back(level + 1 + offset, std::string("ident: \"") + ast.pIdent->value + "\"");
            processAst(*ast.pExpression, level + 1 + offset, items, "expression");
            break;
        case 1:
            items.emplace_back(level, name + "condition-statement:");
            processAst(*ast.pCondition, level + 1 + offset, items, "condition");
            processAst(*ast.pStatement, level + 1 + offset, items, "");
            break;
        case 2:
            items.emplace_back(level, name + "while-loop-statement:");
            processAst(*ast.pCondition, level + 1 + offset, items, "condition");
            processAst(*ast.pStatement, level + 1 + offset, items, "");
            break;
        case 3:
            items.emplace_back(level, name + "call-statement:");
            items.emplace_back(level + 1 + offset, std::string("ident: \"") + ast.pIdent->value + "\"");
            break;
        case 4:
            items.emplace_back(level, name + "read-statement:");
            for (Ident &subAst : ast.vIdent)
                items.emplace_back(level + 1 + offset, std::string("- ident: \"") + subAst.value + "\"");
            break;
        case 5:
            items.emplace_back(level, name + "write-statement:");
            for (Ident &subAst : ast.vIdent)
                items.emplace_back(level + 1 + offset, std::string("- ident: \"") + subAst.value + "\"");
            break;
        case 6:
            items.emplace_back(level, name + "compound-statement:");
            for (Statement &subAst : ast.vStatement)
                processAst(subAst, level + 1 + offset, items, "- ");
            break;
        default:
            break;
    }
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Condition>(
        Condition &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    switch (ast.caseNum)
    {
        case 0:
            items.emplace_back(level, "relational-condition:");
            processAst(*ast.pExpression1, level + 1, items, "expression-1(expression)");
            items.emplace_back(level + 1, std::string("rel-op: \"") + ast.pRelOp->value + "\"");
            processAst(*ast.pExpression2, level + 1, items, "expression-2(expression)");
            break;
        default:
            items.emplace_back(level, "odd-condition:");
            processAst(*ast.pExpression1, level + 1, items, "expression");
    }
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Expression>(
        Expression &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, name + ":");
    if (ast.pAddSubOp != nullptr)
        items.emplace_back(level + 1, std::string("add-sub-op: \"") + ast.pAddSubOp->value + "\"");
    processAst(*ast.pTerm, level + 1, items, "term");
    if (!ast.vAddSubOpExpression.empty())
    {
        items.emplace_back(level + 1, "add-sub-op-terms:");
        for (auto &pair : ast.vAddSubOpExpression)
        {
            items.emplace_back(level + 2, std::string("add-sub-op: \"") + pair.first.value + "\"");
            processAst(pair.second, level + 2, items, "term");
        }
    }
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Term>(
        Term &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    items.emplace_back(level, name + ":");
    processAst(*ast.pFactor, level + 1, items, "");
    if (!ast.vMulDivOpFactor.empty())
    {
        items.emplace_back(level + 1, "mul-div-op-factors:");
        for (auto &pair : ast.vMulDivOpFactor)
        {
            items.emplace_back(level + 2, std::string("mul-div-op: \"") + pair.first.value + "\"");
            processAst(pair.second, level + 2, items, "");
        }
    }
}

template <>
void MyCompiler::Util::processAst<MyCompiler::Factor>(
        Factor &ast, int level,
        std::vector<std::pair<int, std::string>> &items, const std::string &name)
{
    switch (ast.caseNum)
    {
        case 0:
            items.emplace_back(level, "ident-factor:");
            items.emplace_back(level + 1, "ident: \"" + ast.pIdent->value + "\"");
            break;
        case 1:
            items.emplace_back(level, "number-factor:");
            items.emplace_back(level + 1, "number: " + ast.pNumber->value);
            break;
        default:
            items.emplace_back(level, "expression-factor:");
            processAst(*ast.pExpression, level + 1, items, "expression");
    }
}