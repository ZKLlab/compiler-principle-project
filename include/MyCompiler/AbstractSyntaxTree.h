#ifndef MY_COMPILER__ABSTRACT_SYNTAX_TREE_H
#define MY_COMPILER__ABSTRACT_SYNTAX_TREE_H

#include <functional>
#include <memory>
#include <sstream>
#include <vector>
#include "SymbolType.h"

namespace MyCompiler
{
#pragma region AstDeclarations

    struct AbstractAstNode;
    struct Program;
    struct Block;
    struct ConstDeclaration;
    struct ConstDefinition;
    struct VarDeclaration;
    struct ProcedureDeclaration;
    struct Statement;
    struct Condition;
    struct Expression;
    struct Term;
    struct Factor;
    struct Ident;
    struct Number;
    struct RelOp;
    struct AddSubOp;
    struct MulDivOp;

#pragma endregion

#pragma region AstDefinitions

    struct AbstractAstNode
    {
        static int counter;
        int id;
        int caseNum{0};
        std::string name;
        std::string value;

        explicit AbstractAstNode(std::string name);
    };

    // program = block "."
    struct Program : AbstractAstNode
    {
        std::shared_ptr<Block> pBlock;

        Program();
    };

    // block = [ const-declaration ] [ var-declaration ] { procedure-declaration } statement
    struct Block : AbstractAstNode
    {
        std::shared_ptr<ConstDeclaration> pConstDeclaration;
        std::shared_ptr<VarDeclaration> pVarDeclaration;
        std::vector<ProcedureDeclaration> vProcedureDeclaration;
        std::shared_ptr<Statement> pStatement;

        Block();
    };

    // const-declaration = "const" const-definition { "," const-definition } ";"
    struct ConstDeclaration : AbstractAstNode
    {
        std::vector<ConstDefinition> vConstDefinition;

        ConstDeclaration();
    };

    // const-definition = ident "=" number
    struct ConstDefinition : AbstractAstNode
    {
        std::shared_ptr<Ident> pIdent;
        std::shared_ptr<Number> pNumber;

        ConstDefinition();
    };

    // var-declaration = "var" ident { "," ident } ";"
    struct VarDeclaration : AbstractAstNode
    {
        std::vector<Ident> vIdent;

        VarDeclaration();
    };

    // procedure-declaration = "procedure" ident ";" block ";"
    struct ProcedureDeclaration : AbstractAstNode
    {
        std::shared_ptr<Ident> pIdent;
        std::shared_ptr<Block> pBlock;

        ProcedureDeclaration();
    };

    // statement = ident ":=" expression                          // Case 0
    //               | "if" condition "then" statement            // Case 1
    //               | "while" condition "do" statement           // Case 2
    //               | "call" ident                               // Case 3
    //               | "read" "(" ident { "," ident } ")"         // Case 4
    //               | "write" "(" ident { "," ident } ")"        // Case 5
    //               | "begin" statement { ";" statement } "end"  // Case 6
    //               | e                                          // Case 7
    struct Statement : AbstractAstNode
    {
        std::shared_ptr<Ident> pIdent;
        std::shared_ptr<Expression> pExpression;
        std::shared_ptr<Condition> pCondition;
        std::shared_ptr<Statement> pStatement;
        std::vector<Ident> vIdent;
        std::vector<Statement> vStatement;

        Statement();
    };

    // condition = expression ( "=" | "#" | "<" | "<=" | ">" | ">=" ) expression  // Case 0
    //              | "odd" expression                                            // Case 1
    struct Condition : AbstractAstNode
    {
        std::shared_ptr<Expression> pExpression1;
        std::shared_ptr<RelOp> pRelOp;
        std::shared_ptr<Expression> pExpression2;

        Condition();
    };

    // expression = [ "+" | "-" ] term { ( "+" | "-" ) term }
    struct Expression : AbstractAstNode
    {
        std::shared_ptr<AddSubOp> pAddSubOp;
        std::shared_ptr<Term> pTerm;
        std::vector<std::pair<AddSubOp, Term>> vAddSubOpExpression;

        Expression();
    };

    // term = factor { ( "*" | "/" ) factor }
    struct Term : AbstractAstNode
    {
        std::shared_ptr<Factor> pFactor;
        std::vector<std::pair<MulDivOp, Factor>> vMulDivOpFactor;

        Term();
    };

    // factor = ident                  // Case 0
    //           | number              // Case 1
    //           | "(" expression ")"  // Case 2
    struct Factor : AbstractAstNode
    {
        std::shared_ptr<Ident> pIdent;
        std::shared_ptr<Number> pNumber;
        std::shared_ptr<Expression> pExpression;

        Factor();
    };

    // ident = ( "A" | "B" | ... | "Z" | "a" | "b" | ... | "z" )
    //           { "A" | "B" | ... | "Z" | "a" | "b" | ... | "z"
    //             | "0" | "1" | ... | "9" }
    struct Ident : AbstractAstNode
    {
        Ident();
    };

    // number = ( "0" | "1" | ... | "9" ) { "0" | "1" | ... | "9" }
    struct Number : AbstractAstNode
    {
        int32_t num{0};

        Number();
    };

    // rel-op = "=" | "#" | "<" | "<=" | ">" | ">="
    struct RelOp : AbstractAstNode
    {
        RelOp();
    };

    // add-sub-op = "+" | "-"
    struct AddSubOp : AbstractAstNode
    {
        AddSubOp();
    };

    // mul-div-op = "*" | "/"
    struct MulDivOp : AbstractAstNode
    {
        MulDivOp();
    };

#pragma endregion
}
#endif // MY_COMPILER__ABSTRACT_SYNTAX_TREE_H