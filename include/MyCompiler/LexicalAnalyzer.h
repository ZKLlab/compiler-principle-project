#ifndef MY_COMPILER__LEXICAL_ANALYZER_H
#define MY_COMPILER__LEXICAL_ANALYZER_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include "Token.h"
#include "SymbolType.h"
#include "LexicalError.h"

namespace MyCompiler
{
    Token nextToken(std::istream &stream);
}

#endif // MY_COMPILER__LEXICAL_ANALYZER_H