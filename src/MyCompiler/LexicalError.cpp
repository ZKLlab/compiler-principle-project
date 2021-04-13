#include "MyCompiler/LexicalError.h"

MyCompiler::LexicalError::LexicalError(std::ios::pos_type offset)
        : std::runtime_error("invalid token"), offset(offset)
{}

std::ios::pos_type MyCompiler::LexicalError::getOffset() const noexcept
{
    return offset;
}
