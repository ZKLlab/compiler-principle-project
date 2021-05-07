//
// Created by 穆润东 on 2021/5/3.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "MyCompiler/SyntacticAnalyzer.h"

const char *BNF =
        "<程序> ::= <分程序> <Period>\n"
        "<分程序> ::= <分程序1> <分程序2> <分程序3> <语句>\n"
        "<分程序1> ::= <Nul> | <常量说明>\n"
        "<分程序2> ::= <Nul> | <变量说明>\n"
        "<分程序3> ::= <Nul> | <过程说明>\n"
        "<常量说明> ::= <ConstSym> <常量定义> <常量说明1> <Semicolon>\n"
        "<常量说明1> ::= <Nul> | <Comma> <常量定义> <常量说明1>\n"
        "<常量定义> ::= <标识符> <Eql> <Number>\n"
        "<变量说明> ::= <VarSym> <标识符> <变量说明1> <Semicolon>\n"
        "<变量说明1> ::= <Nul> | <Comma> <标识符> <变量说明1>\n"
        "<标识符> ::= <Ident> <标识符1>\n"
        "<标识符1> ::= <Nul> | <标识符2> <标识符1>\n"
        "<标识符2> ::= <Ident> | <Number>\n"
        "<过程说明> ::= <过程说明1> <过程说明2>\n"
        "<过程说明1> ::= <过程首部> <分程序> <Semicolon>\n"
        "<过程说明2> ::= <Nul> | <过程说明1> <过程说明2>\n"
        "<过程首部> ::= <ProcedureSym> <标识符> <Semicolon>\n"
        "<语句> ::= <赋值语句> | <条件语句> | <当循环语句> | <过程调用语句> | <复合语句> | <读语句> | <写语句> | <Nul>\n"
        "<赋值语句> ::= <标识符> <Becomes> <表达式>\n"
        "<复合语句> ::= <BeginSym> <语句> <复合语句1> <EndSym>\n"
        "<复合语句1> ::= <Nul> | <Semicolon> <语句> <复合语句1>\n"
        "<条件表达式> ::= <表达式> <关系运算符> <表达式> | <OddSym> <表达式>\n"
        "<表达式> ::= <表达式1> <项> <表达式2>\n"
        "<表达式1> ::= <Nul> | <Plus> | <Minus>\n"
        "<表达式2> ::= <Nul> | <加减法运算符> <项> <表达式2>\n"
        "<项> ::= <因子> <项1>\n"
        "<项1> ::= <Nul> | <乘除法运算符> <因子> <项1>\n"
        "<因子> ::= <标识符> | <Number> | <LParen> <表达式> <RParen>\n"
        "<加减法运算符> ::= <Plus> | <Minus>\n"
        "<乘除法运算符> ::= <Times> | <Slash>\n"
        "<关系运算符> ::= <Eql> | <Neq> | <Lss> | <Leq> | <Gtr> | <Geq>\n"
        "<条件语句> ::= <IfSym> <条件表达式> <ThenSym> <语句>\n"
        "<过程调用语句> ::= <CallSym> <标识符>\n"
        "<当循环语句> ::= <WhileSym> <条件表达式> <DoSym> <语句>\n"
        "<读语句> ::= <ReadSym> <LParen> <标识符> <读语句1> <RParen>\n"
        "<读语句1> ::= <Nul> | <Comma> <标识符> <读语句1>\n"
        "<写语句> ::= <WriteSym> <LParen> <表达式> <写语句1> <RParen>\n"
        "<写语句1> ::= <Nul> | <Comma> <表达式> <写语句1>";

void parse()
{
    std::istringstream in(BNF);
    std::vector<std::string> def;
    std::string buffer;
    while (getline(in, buffer))
        def.push_back(buffer);
    MyCompiler::SyntacticAnalyzer syntacticAnalyzer(def);

    try
    {
        std::cout << (syntacticAnalyzer.tryParse(std::cin) ? "ok" : "invalid syntax") << std::endl;
    }
    catch (MyCompiler::LexicalError &err)
    {
        std::cout << "invalid token" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        parse();
    else
        for (int i = 1; i < argc; i++)
        {
            std::ifstream fin(argv[i]);
            auto cinBuf = std::cin.rdbuf(fin.rdbuf());
            parse();
            fin.close();
            std::cin.rdbuf(cinBuf);
        }
}