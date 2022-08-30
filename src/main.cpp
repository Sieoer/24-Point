#include "Expression.h"
#include "Operators.h"
#include <sstream>
#include <algorithm>
#include <string>

/**
 * @brief 想要通过计算得出的值
 *        初始化为24
 */
int FINAL_NUMBER = 24;

/**
 * @brief 存储所有能算出FINAL_NUMBER的算式
 */
std::vector<std::string> equations;

/**
 * @brief        判断t_str是否已经在equations里
 * @param t_str  待判断的string
 * @return true  t_str在equations中
 * @return false t_str不在equation中
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
 * @brief 打印出equations内的所有等式
 *        如果equations为空，则输出no
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
 * @brief 核心计算函数声明
 * @param now_numbers   包含本轮递推待计算的数字的数组
 * @param now_size      数组大小
 * @param now_operators 运算操作符类对象
 */
void mainCalculate(Expression*& now_numbers, int now_size, Operators& now_operators)
{
    // 引用存储运算操作符&代表字符
    const std::vector<fptr>& operatorlist = now_operators.m_operatorlist;
    const std::vector<char>& symbollist = now_operators.m_symbollist;
    // 从now_numbers中按一定顺序取两个数字进行组合
    for (int i = 0; i < now_size - 1; i++)
    {
        for (int j = i + 1; j < now_size; j++)
        {
            // 取出的两个数字
            int number_one = now_numbers[i].m_int;
            int number_two = now_numbers[j].m_int;
            // 运算符的下标，用于判断当前使用的是哪一种运算操作符
            int g = 0;
            // 遍历运算操作符向量，调用所有运算方法作用在取出的两个数字上
            for (auto it = operatorlist.begin(); it < operatorlist.end(); it++)
            {
                // 顺序排列的情况——main
                    // 本次运算后的结果
                int t_result_main = (*it)(number_one, number_two);
                // 创建一个新的Expression对象，其m_int是本次计算的结果，其m_expression是计算出结果的算式
                Expression next_expression_main(t_result_main);
                next_expression_main.m_expression = "(" + now_numbers[i].m_expression + symbollist[g] + now_numbers[j].m_expression + ")";

                // 逆序排列的情况——vice
                int t_result_vice = (*it)(number_two, number_one);
                Expression next_expression_vice(t_result_vice);
                next_expression_vice.m_expression = "(" + now_numbers[j].m_expression + symbollist[g] + now_numbers[i].m_expression + ")";

                g++;

                // 判断是不是FINAL_NUMBER
                if (now_size == 2)
                {
                    // 顺序排列的情况——main
                        // 当仅剩下两个数字、并且结果等于FINAL_NUMBER时
                    if (t_result_main == FINAL_NUMBER && (!isInEquations(next_expression_main.m_expression)))
                    {
                        // 若equations中不包含该算式，将其加入到equations中
                        // 防止算式重复输出
                        equations.push_back(next_expression_main.m_expression);
                    }

                    // 逆序排列的情况——vice
                    if (t_result_vice == FINAL_NUMBER && (!isInEquations(next_expression_vice.m_expression)))
                    {
                        equations.push_back(next_expression_vice.m_expression);
                    }
                }
                else
                {
                    // 顺序排列的情况——main
                        // 将本次新的计算结果和余下的数字重新组成一个Expression数组
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
                    // 本次计算的结果存储到数组的最后一位
                    next_numbers_main[now_size - 2] = Expression(next_expression_main);
                    // 递推
                    mainCalculate(next_numbers_main, now_size - 1, now_operators);

                    // 逆序排列的情况——vice
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
                    // 递推
                    mainCalculate(next_numbers_vice, now_size - 1, now_operators);

                    //回溯
                    delete[] next_numbers_main;
                    delete[] next_numbers_vice;
                }
            }
        }
    }
}

/**
 * @brief vector->Expression的转换函数
 * @param t_vector 带转换的vector(存储用户输入的数字)
 * @return Expression* 存储用户输入数字的、与t_vector等大的Expression类型数组
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
    // 创建运算操作符对象
    Operators my_operstors;
    /**
     * @todo 用户可以在此添加自定义的运算符
     */

     // 获取用户输入
    std::string str;
    std::getline(std::cin, str);

    // 创建存储用户输入的向量
    std::vector<int> my_vector;

    // 使用istringstream依次获得每个数字，并存储到my_vector中
    std::istringstream is(str);
    int inter;
    while (is >> inter)
    {
        my_vector.push_back(inter);
    }
    // 把my_vector按从小到大的顺序排列好
    std::sort(my_vector.begin(), my_vector.end());

    // 计算用户输入数字的个数
    int my_size = my_vector.size();

    Expression* test = IntToExpression(my_vector);
    mainCalculate(test, my_size, my_operstors);
    printEquations();
    return 0;
}