#pragma once

#include <iostream>

/**
 * @brief 表达式类
 * @param m_int 对象代表的整数
 * @param m_expression m_int是通过怎样的算式得来的
 * @note  例如：一个Expression的对象，其m_int=10，其m_expression="(2+8)"
 */
class Expression {
public:
    int m_int;
    std::string m_expression;
public:
    Expression() {}
    /**
     * @brief  构造函数的重载
     *         拷贝构造函数，将expression的m_int和m_expression均进行拷贝
     * @param expression 被拷贝的对象
     */
    Expression(Expression& expression);
    /**
     * @brief 构造函数的重载
     *        用t_int初始化m_int，并将t_int转化为string类型存储在m_expression中
     * @param t_int      用于初始化Expression对象的参数
     */
    Expression(int t_int);
    ~Expression() {}
};