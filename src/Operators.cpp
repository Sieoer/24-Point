#include "Operators.h"


Operators::Operators() {
    fptr add_ptr = addOperator;
    m_operatorlist.push_back(add_ptr);
    m_symbollist.push_back('+');

    fptr minus_ptr = minusOperator;
    m_operatorlist.push_back(minus_ptr);
    m_symbollist.push_back('-');

    fptr mul_ptr = multiOperator;
    m_operatorlist.push_back(mul_ptr);
    m_symbollist.push_back('x');

    fptr div_ptr = divOperator;
    m_operatorlist.push_back(div_ptr);
    m_symbollist.push_back('/');
}

Operators::~Operators() {}



/**
 * @brief �Ӽ��˳��������㺯����ʵ��
 */
extern int addOperator(int x, int y) {
    return x + y;
}

extern int minusOperator(int x, int y) {
    return x - y;
}

extern int multiOperator(int x, int y) {
    return x * y;
}

extern int divOperator(int x, int y) {
    // �������������������߳���Ϊ0������9999����������
    if (y == 0)
    {
        return 9999;
    }
    else {
        if (x % y == 0)
        {
            return x / y;
        }
        else return 9999;
    }
}