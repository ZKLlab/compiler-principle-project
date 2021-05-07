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

        template <typename T>
        std::shared_ptr<T> parse();
    };

#pragma region ParserDeclarations

    template <>
    std::shared_ptr<Program> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Block> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<ConstDeclaration> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<ConstDefinition> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<VarDeclaration> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<ProcedureDeclaration> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Statement> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Condition> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Expression> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Term> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Factor> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Ident> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<Number> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<RelOp> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<AddSubOp> RecursiveDescentParser::parse();

    template <>
    std::shared_ptr<MulDivOp> RecursiveDescentParser::parse();

#pragma endregion
}

#endif // MY_COMPILER__RECURSIVE_DESCENT_PARSER_H