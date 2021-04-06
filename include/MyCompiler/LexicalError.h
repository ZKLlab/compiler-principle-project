#ifndef COMPILER_PRINCIPLE_PROJECT__LEXICAL_ERROR_H
#define COMPILER_PRINCIPLE_PROJECT__LEXICAL_ERROR_H

#include <ios>
#include <stdexcept>

class LexicalError : public std::runtime_error
{
    std::ios::pos_type offset;

public:
    explicit LexicalError(std::ios::pos_type offset)
            : std::runtime_error("invalid token"), offset(offset)
    {}

    std::ios::pos_type getOffset() const noexcept
    {
        return offset;
    }
};

#endif // COMPILER_PRINCIPLE_PROJECT__LEXICAL_ERROR_H
