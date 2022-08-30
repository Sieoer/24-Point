#include "Expression.h"
#include <string>

Expression::Expression(Expression& expression)
{
    m_int = expression.m_int;
    m_expression = expression.m_expression;
}

Expression::Expression(int t_int)
{
    m_int = t_int;
    m_expression = std::to_string(t_int);
}