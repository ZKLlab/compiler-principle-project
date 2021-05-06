#ifndef MY_COMPILER__RECURSIVE_DESCENT_PARSER_H
#define MY_COMPILER__RECURSIVE_DESCENT_PARSER_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>
#include "AbstractSyntaxTree.h"
#include "LexicalAnalyzer.h"
#include "SymbolType.h"
#include "SyntaxError.h"
#include "Token.h"

namespace MyCompiler
{
    class RecursiveDescentParser
    {
    protected:
        std::istream &stream;
        Token currentToken;
        SymbolType sym{SymbolType::NUL};

        void nextSym();

        bool accept(SymbolType symbolType);

        void except(SymbolType symbolType, const std::string &msg);

    public:
        explicit RecursiveDescentParser(std::istream &stream);

        void finish();

#pragma region ParserDeclarations

        template <typename T>
        std::shared_ptr<T> parse();

        template <>
        std::shared_ptr<Program> parse();

        template <>
        std::shared_ptr<Block> parse();

        template <>
        std::shared_ptr<ConstDeclaration> parse();

        template <>
        std::shared_ptr<ConstDefinition> parse();

        template <>
        std::shared_ptr<VarDeclaration> parse();

        template <>
        std::shared_ptr<ProcedureDeclaration> parse();

        template <>
        std::shared_ptr<Statement> parse();

        template <>
        std::shared_ptr<Condition> parse();

        template <>
        std::shared_ptr<Expression> parse();

        template <>
        std::shared_ptr<Term> parse();

        template <>
        std::shared_ptr<Factor> parse();

        template <>
        std::shared_ptr<Ident> parse();

        template <>
        std::shared_ptr<Number> parse();

        template <>
        std::shared_ptr<RelOp> parse();

        template <>
        std::shared_ptr<AddSubOp> parse();

        template <>
        std::shared_ptr<MulDivOp> parse();

#pragma endregion
    };
}

#endif // MY_COMPILER__RECURSIVE_DESCENT_PARSER_H