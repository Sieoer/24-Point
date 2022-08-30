#include "Expression.h"
#include "Operators.h"
#include <sstream>
#include <algorithm>
#include <string>

/**
 * @brief ��Ҫͨ������ó���ֵ
 *        ��ʼ��Ϊ24
 */
int FINAL_NUMBER = 24;

/**
 * @brief �洢���������FINAL_NUMBER����ʽ
 */
std::vector<std::string> equations;

/**
 * @brief        �ж�t_str�Ƿ��Ѿ���equations��
 * @param t_str  ���жϵ�string
 * @return true  t_str��equations��
 * @return false t_str����equation��
 */
extern bool isInEquations(std::string t_str)
{
    for (auto it : equations)
    {
        if (!t_str.compare(it)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief ��ӡ��equations�ڵ����е�ʽ
 *        ���equationsΪ�գ������no
 */
extern void printEquations()
{
    if (equations.empty()) {
        std::cout << "no" << std::endl;
    }
    else {
        for (auto it : equations)
        {
            std::cout << it << std::endl;
        }
    }
}

/**
 * @brief ���ļ��㺯������
 * @param now_numbers   �������ֵ��ƴ���������ֵ�����
 * @param now_size      �����С
 * @param now_operators ��������������
 */
void mainCalculate(Expression*& now_numbers, int now_size, Operators& now_operators)
{
    // ���ô洢���������&�����ַ�
    const std::vector<fptr>& operatorlist = now_operators.m_operatorlist;
    const std::vector<char>& symbollist = now_operators.m_symbollist;
    // ��now_numbers�а�һ��˳��ȡ�������ֽ������
    for (int i = 0; i < now_size - 1; i++)
    {
        for (int j = i + 1; j < now_size; j++)
        {
            // ȡ������������
            int number_one = now_numbers[i].m_int;
            int number_two = now_numbers[j].m_int;
            // ��������±꣬�����жϵ�ǰʹ�õ�����һ�����������
            int g = 0;
            // ������������������������������㷽��������ȡ��������������
            for (auto it = operatorlist.begin(); it < operatorlist.end(); it++)
            {
                // ˳�����е��������main
                    // ���������Ľ��
                int t_result_main = (*it)(number_one, number_two);
                // ����һ���µ�Expression������m_int�Ǳ��μ���Ľ������m_expression�Ǽ�����������ʽ
                Expression next_expression_main(t_result_main);
                next_expression_main.m_expression = "(" + now_numbers[i].m_expression + symbollist[g] + now_numbers[j].m_expression + ")";

                // �������е��������vice
                int t_result_vice = (*it)(number_two, number_one);
                Expression next_expression_vice(t_result_vice);
                next_expression_vice.m_expression = "(" + now_numbers[j].m_expression + symbollist[g] + now_numbers[i].m_expression + ")";

                g++;

                // �ж��ǲ���FINAL_NUMBER
                if (now_size == 2)
                {
                    // ˳�����е��������main
                        // ����ʣ���������֡����ҽ������FINAL_NUMBERʱ
                    if (t_result_main == FINAL_NUMBER && (!isInEquations(next_expression_main.m_expression)))
                    {
                        // ��equations�в���������ʽ��������뵽equations��
                        // ��ֹ��ʽ�ظ����
                        equations.push_back(next_expression_main.m_expression);
                    }

                    // �������е��������vice
                    if (t_result_vice == FINAL_NUMBER && (!isInEquations(next_expression_vice.m_expression)))
                    {
                        equations.push_back(next_expression_vice.m_expression);
                    }
                }
                else
                {
                    // ˳�����е��������main
                        // �������µļ����������µ������������һ��Expression����
                    Expression* next_numbers_main = new Expression[now_size - 1]();
                    for (int s = 0, k = 0; k < now_size; k++) {
                        if (k == i || k == j) {
                            continue;
                        }
                        else {
                            next_numbers_main[s] = Expression(now_numbers[k]);
                            s++;
                        }
                    }
                    // ���μ���Ľ���洢����������һλ
                    next_numbers_main[now_size - 2] = Expression(next_expression_main);
                    // ����
                    mainCalculate(next_numbers_main, now_size - 1, now_operators);

                    // �������е��������vice
                    Expression* next_numbers_vice = new Expression[now_size - 1]();
                    for (int s = 0, k = 0; k < now_size; k++) {
                        if (k == i || k == j) {
                            continue;
                        }
                        else {
                            next_numbers_vice[s] = Expression(now_numbers[k]);
                            s++;
                        }
                    }
                    next_numbers_vice[now_size - 2] = Expression(next_expression_vice);
                    // ����
                    mainCalculate(next_numbers_vice, now_size - 1, now_operators);

                    //����
                    delete[] next_numbers_main;
                    delete[] next_numbers_vice;
                }
            }
        }
    }
}

/**
 * @brief vector->Expression��ת������
 * @param t_vector ��ת����vector(�洢�û����������)
 * @return Expression* �洢�û��������ֵġ���t_vector�ȴ��Expression��������
 */
Expression* IntToExpression(std::vector<int> t_vector)
{
    int t_size = t_vector.size();
    Expression* test = new Expression[t_size]();
    for (int i = 0; i < t_size; i++)
    {
        test[i] = Expression(t_vector[i]);
    }
    return test;
}

int main() {
    // �����������������
    Operators my_operstors;
    /**
     * @todo �û������ڴ�����Զ���������
     */

     // ��ȡ�û�����
    std::string str;
    std::getline(std::cin, str);

    // �����洢�û����������
    std::vector<int> my_vector;

    // ʹ��istringstream���λ��ÿ�����֣����洢��my_vector��
    std::istringstream is(str);
    int inter;
    while (is >> inter)
    {
        my_vector.push_back(inter);
    }
    // ��my_vector����С�����˳�����к�
    std::sort(my_vector.begin(), my_vector.end());

    // �����û��������ֵĸ���
    int my_size = my_vector.size();

    Expression* test = IntToExpression(my_vector);
    mainCalculate(test, my_size, my_operstors);
    printEquations();
    return 0;
}