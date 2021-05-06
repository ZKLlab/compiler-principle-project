#ifndef MY_COMPILER__UTIL__AST_TO_DOT_H
#define MY_COMPILER__UTIL__AST_TO_DOT_H

#include <memory>
#include <sstream>
#include <utility>
#include <vector>
#include "MyCompiler/AbstractSyntaxTree.h"

namespace MyCompiler
{
    namespace Util
    {
        std::string astToYaml(Program &ast);

        template <typename T>
        void processAst(
                T &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Program>(
                Program &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Block>(
                Block &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<ConstDeclaration>(
                ConstDeclaration &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<ConstDefinition>(
                ConstDefinition &Ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<VarDeclaration>(
                VarDeclaration &Ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<ProcedureDeclaration>(
                ProcedureDeclaration &Ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Statement>(
                Statement &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Condition>(
                Condition &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Expression>(
                Expression &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Term>(
                Term &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);

        template <>
        void processAst<Factor>(
                Factor &ast, int level,
                std::vector<std::pair<int, std::string>> &items, const std::string &name);
    }
}

#endif // MY_COMPILER__UTIL__AST_TO_DOT_H