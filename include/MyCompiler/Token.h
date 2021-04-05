#ifndef COMPILER_PRINCIPLE_PROJECT__TOKEN_H
#define COMPILER_PRINCIPLE_PROJECT__TOKEN_H

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
        explicit Token(SymbolType symbolType)
                : symbolType(symbolType)
        {}

        explicit Token(SymbolType symbolType, std::string value)
                : symbolType(symbolType), value(std::move(value))
        {}

        SymbolType getSymbolType() const
        {
            return symbolType;
        }

        const std::string &getValue() const
        {
            return value;
        }
    };
}

#endif // COMPILER_PRINCIPLE_PROJECT__TOKEN_H