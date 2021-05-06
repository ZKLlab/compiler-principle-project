#include "MyCompiler/SyntaxError.h"

MyCompiler::SyntaxError::SyntaxError(const std::string &msg)
        : runtime_error(msg)
{}
