#include "MyCompiler/Token.h"

MyCompiler::Token::Token(MyCompiler::SymbolType symbolType)
        : symbolType(symbolType)
{}

MyCompiler::Token::Token(MyCompiler::SymbolType symbolType, std::string value)
        : symbolType(symbolType), value(std::move(value))
{}

MyCompiler::SymbolType MyCompiler::Token::getSymbolType() const
{
    return symbolType;
}

const std::string &MyCompiler::Token::getValue() const
{
    return value;
}
