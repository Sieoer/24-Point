#pragma once

#include <iostream>

/**
 * @brief ���ʽ��
 * @param m_int ������������
 * @param m_expression m_int��ͨ����������ʽ������
 * @note  ���磺һ��Expression�Ķ�����m_int=10����m_expression="(2+8)"
 */
class Expression {
public:
    int m_int;
    std::string m_expression;
public:
    Expression() {}
    /**
     * @brief  ���캯��������
     *         �������캯������expression��m_int��m_expression�����п���
     * @param expression �������Ķ���
     */
    Expression(Expression& expression);
    /**
     * @brief ���캯��������
     *        ��t_int��ʼ��m_int������t_intת��Ϊstring���ʹ洢��m_expression��
     * @param t_int      ���ڳ�ʼ��Expression����Ĳ���
     */
    Expression(int t_int);
    ~Expression() {}
};