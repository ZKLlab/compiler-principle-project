#include "MyCompiler/RecursiveDescentParser.h"

MyCompiler::RecursiveDescentParser::RecursiveDescentParser(std::istream &stream)
        : stream(stream), currentToken(SymbolType::NUL)
{}

void MyCompiler::RecursiveDescentParser::nextSym()
{
    currentToken = nextToken(stream);
    sym = currentToken.getSymbolType();
}

bool MyCompiler::RecursiveDescentParser::accept(SymbolType symbolType)
{
    if (sym == symbolType)
    {
        nextSym();
        return true;
    }
    return false;
}

void MyCompiler::RecursiveDescentParser::except(SymbolType symbolType, const std::string &msg)
{
    if (!accept(symbolType))
        throw SyntaxError(msg);
}

void MyCompiler::RecursiveDescentParser::start()
{
    nextSym();
}

void MyCompiler::RecursiveDescentParser::finish()
{
    except(SymbolType::NUL, "eof expected");
}

#pragma region Parsers

template <>
std::shared_ptr<MyCompiler::Program> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Program>();

    pResult->pBlock = parse<Block>();
    except(SymbolType::PERIOD, "period expected");

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Block> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Block>();

    if (sym == SymbolType::CONST)
        pResult->pConstDeclaration = parse<ConstDeclaration>();
    if (sym == SymbolType::VAR)
        pResult->pVarDeclaration = parse<VarDeclaration>();
    while (sym == SymbolType::PROC)
        pResult->vProcedureDeclaration.push_back(*parse<ProcedureDeclaration>());
    pResult->pStatement = parse<Statement>();

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::ConstDeclaration> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<ConstDeclaration>();

    accept(SymbolType::CONST);
    do
        pResult->vConstDefinition.push_back(*parse<ConstDefinition>());
    while (accept(SymbolType::COMMA));
    except(SymbolType::SEMICOLON, "semicolon or comma expected");

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::ConstDefinition> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<ConstDefinition>();

    pResult->pIdent = parse<Ident>();
    except(SymbolType::EQL, "identifier must be followed by =");
    pResult->pNumber = parse<Number>();

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::VarDeclaration> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<VarDeclaration>();

    accept(SymbolType::VAR);
    do
        pResult->vIdent.push_back(*parse<Ident>());
    while (accept(SymbolType::COMMA));
    except(SymbolType::SEMICOLON, "semicolon or comma expected");

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::ProcedureDeclaration> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<ProcedureDeclaration>();

    accept(SymbolType::PROC);
    pResult->pIdent = parse<Ident>();
    except(SymbolType::SEMICOLON, "semicolon expected");
    pResult->pBlock = parse<Block>();
    except(SymbolType::SEMICOLON, "semicolon expected");

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Statement> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Statement>();

    if (sym == SymbolType::IDENT)
    {
        pResult->caseNum = 0;
        pResult->pIdent = parse<Ident>();
        except(SymbolType::BECOMES, "assignment operator expected");
        pResult->pExpression = parse<Expression>();
    }
    else if (accept(SymbolType::IF))
    {
        pResult->caseNum = 1;
        pResult->pCondition = parse<Condition>();
        except(SymbolType::THEN, "then expected");
        pResult->pStatement = parse<Statement>();
    }
    else if (accept(SymbolType::WHILE))
    {
        pResult->caseNum = 2;
        pResult->pCondition = parse<Condition>();
        except(SymbolType::DO, "do expected");
        pResult->pStatement = parse<Statement>();
    }
    else if (accept(SymbolType::CALL))
    {
        pResult->caseNum = 3;
        pResult->pIdent = parse<Ident>();
    }
    else if (accept(SymbolType::READ))
    {
        pResult->caseNum = 4;
        except(SymbolType::LPAREN, "left parenthesis expected");
        do
            pResult->vIdent.push_back(*parse<Ident>());
        while (accept(SymbolType::COMMA));
        except(SymbolType::RPAREN, "right parenthesis expected");
    }
    else if (accept(SymbolType::WRITE))
    {
        pResult->caseNum = 5;
        except(SymbolType::LPAREN, "left parenthesis expected");
        do
            pResult->vIdent.push_back(*parse<Ident>());
        while (accept(SymbolType::COMMA));
        except(SymbolType::RPAREN, "right parenthesis expected");
    }
    else if (accept(SymbolType::BEGIN))
    {
        pResult->caseNum = 6;
        do
            pResult->vStatement.push_back(*parse<Statement>());
        while (accept(SymbolType::SEMICOLON));
        except(SymbolType::END, "semicolon or end expected");
    }
    else
        pResult->caseNum = 7;

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Condition> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Condition>();

    if (sym == SymbolType::ODD)
    {
        pResult->caseNum = 1;
        pResult->pExpression1 = parse<Expression>();
    }
    else
    {
        pResult->caseNum = 0;
        pResult->pExpression1 = parse<Expression>();
        pResult->pRelOp = parse<RelOp>();
        pResult->pExpression2 = parse<Expression>();
    }

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Expression> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Expression>();

    if (sym == SymbolType::PLUS || sym == SymbolType::MINUS)
        pResult->pAddSubOp = parse<AddSubOp>();
    pResult->pTerm = parse<Term>();
    if (pResult->pAddSubOp != nullptr && pResult->pTerm->pFactor->caseNum == 1 &&
        pResult->pTerm->vMulDivOpFactor.empty())
    {
        if (pResult->pAddSubOp->value == "-")
            pResult->pTerm->pFactor->pNumber->setNum(-pResult->pTerm->pFactor->pNumber->num);
        pResult->pAddSubOp = nullptr;
    }
    while (sym == SymbolType::PLUS || sym == SymbolType::MINUS)
    {
        auto p1 = parse<AddSubOp>();
        auto p2 = parse<Term>();
        if (pResult->pTerm->pFactor->caseNum == 1 && pResult->vAddSubOpExpression.empty() &&
            p2->pFactor->caseNum == 1 && p2->vMulDivOpFactor.empty())
        {
            if (p1->value == "+")
                pResult->pTerm->pFactor->pNumber->setNum(
                        pResult->pTerm->pFactor->pNumber->num + p2->pFactor->pNumber->num);
            else
                pResult->pTerm->pFactor->pNumber->setNum(
                        pResult->pTerm->pFactor->pNumber->num - p2->pFactor->pNumber->num);
            if (pResult->pTerm->pFactor->pNumber->num > std::numeric_limits<int32_t>::max()
                || pResult->pTerm->pFactor->pNumber->num < std::numeric_limits<int32_t>::min())
                throw SyntaxError(
                        p1->value == "+" ? "attempt to add with overflow" : "attempt to subtract with overflow");
        }
        else
            pResult->vAddSubOpExpression.emplace_back(*p1, *p2);
    }

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Term> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Term>();

    pResult->pFactor = parse<Factor>();
    while (sym == SymbolType::TIMES || sym == SymbolType::SLASH)
    {
        auto p1 = parse<MulDivOp>();
        auto p2 = parse<Factor>();
        if (pResult->pFactor->caseNum == 1 && p2->caseNum == 1 && pResult->vMulDivOpFactor.empty())
        {
            if (p1->value == "*")
                pResult->pFactor->pNumber->setNum(pResult->pFactor->pNumber->num * p2->pNumber->num);
            else if (p2->pNumber->num != 0)
                pResult->pFactor->pNumber->setNum(pResult->pFactor->pNumber->num / p2->pNumber->num);
            else
                throw SyntaxError("attempt to division by zero");
            if (pResult->pFactor->pNumber->num > std::numeric_limits<int32_t>::max()
                || pResult->pFactor->pNumber->num < std::numeric_limits<int32_t>::min())
                throw SyntaxError(
                        p1->value == "*" ? "attempt to multiply with overflow" : "attempt to divide with overflow");
        }
        else
            pResult->vMulDivOpFactor.emplace_back(*p1, *p2);
    }

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Factor> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Factor>();

    if (sym == SymbolType::IDENT)
    {
        pResult->caseNum = 0;
        pResult->pIdent = parse<Ident>();
    }
    else if (sym == SymbolType::NUMBER)
    {
        pResult->caseNum = 1;
        pResult->pNumber = parse<Number>();
    }
    else
    {
        except(SymbolType::LPAREN, "expression expected");
        pResult->caseNum = 2;
        pResult->pExpression = parse<Expression>();
        except(SymbolType::RPAREN, "right parenthesis expected");
        if (pResult->pExpression->pAddSubOp == nullptr && pResult->pExpression->vAddSubOpExpression.empty() &&
            pResult->pExpression->pTerm->pFactor->caseNum == 1 && pResult->pExpression->pTerm->vMulDivOpFactor.empty())
        {
            pResult->caseNum = 1;
            pResult->pNumber = pResult->pExpression->pTerm->pFactor->pNumber;
            pResult->pExpression = nullptr;
        }
    }

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Ident> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Ident>();

    if (sym != SymbolType::IDENT)
        except(SymbolType::IDENT, "identifier expected");
    pResult->value = currentToken.getValue();
    accept(sym);

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::Number> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<Number>();

    if (sym != SymbolType::NUMBER)
        except(SymbolType::NUMBER, "number expected");
    int64_t val;
    std::istringstream in(currentToken.getValue());
    in >> std::noshowbase >> std::setbase(10) >> val;
    if (in.fail() || val > std::numeric_limits<int32_t>::max() || val < std::numeric_limits<int32_t>::min())
        except(SymbolType::NUMBER, "this number is too large");
    pResult->setNum(val);
    std::ostringstream out;
    out << val;
    pResult->value = out.str();
    accept(sym);

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::RelOp> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<RelOp>();

    if (sym == SymbolType::EQL || sym == SymbolType::NEQ || sym == SymbolType::LSS
        || sym == SymbolType::LEQ || sym == SymbolType::GTR || sym == SymbolType::GEQ)
    {
        switch (sym)
        {
            case SymbolType::EQL:
                pResult->value = "=";
                break;
            case SymbolType::NEQ:
                pResult->value = "#";
                break;
            case SymbolType::LSS:
                pResult->value = "<";
                break;
            case SymbolType::LEQ:
                pResult->value = "<=";
                break;
            case SymbolType::GTR:
                pResult->value = ">";
                break;
            default: // case SymbolType::GEQ:
                pResult->value = ">=";
        }
        accept(sym);
    }
    else
        except(SymbolType::EQL, "relational operator expected");

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::AddSubOp> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<AddSubOp>();

    switch (sym)
    {
        case SymbolType::PLUS:
            pResult->value = "+";
            break;
        default: // case SymbolType::MINUS:
            pResult->value = "-";
    }
    accept(sym);

    return pResult;
}

template <>
std::shared_ptr<MyCompiler::MulDivOp> MyCompiler::RecursiveDescentParser::parse()
{
    auto pResult = std::make_shared<MulDivOp>();

    switch (sym)
    {
        case SymbolType::TIMES:
            pResult->value = "*";
            break;
        default: // case SymbolType::SLASH:
            pResult->value = "/";
    }
    accept(sym);

    return pResult;
}

#pragma endregion