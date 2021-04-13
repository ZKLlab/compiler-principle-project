#ifndef MY_COMPILER__TOKEN_H
#define MY_COMPILER__TOKEN_H

#include <string>
#include <utility>
#include "SymbolType.h"

namespace MyCompiler
{
    class Token
    {
    protected:
        SymbolType symbolType;
        std::string value;
    public:
        explicit Token(SymbolType symbolType);

        explicit Token(SymbolType symbolType, std::string value);

        SymbolType getSymbolType() const;

        const std::string &getValue() const;
    };
}

#endif // MY_COMPILER__TOKEN_H