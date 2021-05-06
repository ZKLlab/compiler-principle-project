#ifndef MY_COMPILER__SYNTAX_ERROR_H
#define MY_COMPILER__SYNTAX_ERROR_H

#include <stdexcept>

namespace MyCompiler
{
    class SyntaxError : public std::runtime_error
    {
    public:
        explicit SyntaxError(const std::string &msg);
    };
}

#endif // MY_COMPILER__SYNTAX_ERROR_H
