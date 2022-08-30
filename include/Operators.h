#pragma once

#include <vector>

/**
 * @brief  �Զ��庯��ָ������
 * @param  �����ǲ���������������
 * @return ����������
 */
typedef int (*fptr)(int, int);

/**
 * @brief  ��������ĺ�������
 * @return int
 */
extern int addOperator(int, int);
extern int minusOperator(int, int);
extern int multiOperator(int, int);
extern int divOperator(int, int);

/**
 * @brief �����������
 * @param m_operatorlist������ָ��������������ÿһ��Ԫ�ض�ָ��һ�����㺯��(�Ӽ��˳����Զ���)
 * @param m_symbollist�����㺯����Ӧ���ַ�(��ӷ�����->'+')��������ʽ�����
 * @note  ����(m_operatorlist)���±����ַ�(m_symbollist)���±���һһ��Ӧ��
 *        �û�����Զ��庯����ָ�������m_symbollist��ͬ�±괦��Ӵ����Զ���������ַ�
 */
class Operators {
public:
    std::vector<fptr> m_operatorlist;
    std::vector<char> m_symbollist;
public:
    /**
     * @brief Operators�Ĺ��캯��
     *        ���ӡ������ˡ������������ʼ����Operators������
     */
    Operators();
    // ��������
    ~Operators();
};