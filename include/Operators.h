#pragma once

#include <vector>

/**
 * @brief  自定义函数指针类型
 * @param  参数是参与计算的两个整数
 * @return 返回运算结果
 */
typedef int (*fptr)(int, int);

/**
 * @brief  四则运算的函数声明
 * @return int
 */
extern int addOperator(int, int);
extern int minusOperator(int, int);
extern int multiOperator(int, int);
extern int divOperator(int, int);

/**
 * @brief 运算操作符类
 * @param m_operatorlist：函数指针向量，向量中每一个元素都指向一个运算函数(加减乘除或自定义)
 * @param m_symbollist：运算函数对应的字符(如加法函数->'+')，用于算式的输出
 * @note  函数(m_operatorlist)的下标与字符(m_symbollist)的下标是一一对应的
 *        用户添加自定义函数的指针后，需在m_symbollist相同下标处添加代表自定义运算的字符
 */
class Operators {
public:
    std::vector<fptr> m_operatorlist;
    std::vector<char> m_symbollist;
public:
    /**
     * @brief Operators的构造函数
     *        将加、减、乘、除四则运算初始化到Operators对象中
     */
    Operators();
    // 析构函数
    ~Operators();
};