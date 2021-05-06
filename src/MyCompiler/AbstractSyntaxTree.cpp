#include "MyCompiler/AbstractSyntaxTree.h"

#include <utility>

int MyCompiler::AbstractAstNode::counter = 0;

MyCompiler::AbstractAstNode::AbstractAstNode(std::string name)
        : id(counter++), name(std::move(name))
{}

MyCompiler::Program::Program()
        : AbstractAstNode("Program")
{}

MyCompiler::Block::Block()
        : AbstractAstNode("Block")
{}

MyCompiler::ConstDeclaration::ConstDeclaration()
        : AbstractAstNode("ConstDeclaration")
{}

MyCompiler::ConstDefinition::ConstDefinition()
        : AbstractAstNode("ConstDefinition")
{}

MyCompiler::VarDeclaration::VarDeclaration()
        : AbstractAstNode("VarDeclaration")
{}

MyCompiler::ProcedureDeclaration::ProcedureDeclaration()
        : AbstractAstNode("ProcedureDeclaration")
{}

MyCompiler::Statement::Statement()
        : AbstractAstNode("Statement")
{}

MyCompiler::Condition::Condition()
        : AbstractAstNode("Condition")
{}

MyCompiler::Expression::Expression()
        : AbstractAstNode("Expression")
{}

MyCompiler::Term::Term()
        : AbstractAstNode("Term")
{}

MyCompiler::Factor::Factor()
        : AbstractAstNode("Factor")
{}

MyCompiler::Ident::Ident()
        : AbstractAstNode("Ident")
{}

MyCompiler::Number::Number()
        : AbstractAstNode("Number")
{}

MyCompiler::RelOp::RelOp()
        : AbstractAstNode("RelOp")
{}

MyCompiler::AddSubOp::AddSubOp()
        : AbstractAstNode("AddSubOp")
{}

MyCompiler::MulDivOp::MulDivOp()
        : AbstractAstNode("MulDivOp")
{}
