#ifndef MY_COMPILER__LEXICAL_ERROR_H
#define MY_COMPILER__LEXICAL_ERROR_H

#include <ios>
#include <stdexcept>

namespace MyCompiler
{
    class LexicalError : public std::runtime_error
    {
        std::ios::pos_type offset;

    public:
        explicit LexicalError(std::ios::pos_type offset);

        std::ios::pos_type getOffset() const noexcept;
    };
}

#endif // MY_COMPILER__LEXICAL_ERROR_H
