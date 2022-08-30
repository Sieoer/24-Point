# 24点自动求解说明

这是清华大学软件学院2022夏季学期课程作业之一。我实现了一个自动求解24点的程序，用户只需要给出你的4个数字，你就可以得到所有可能的算式。**实际上，你还可以指定其他任意值、输入任意个数字计算指定值**，我的程序都可以帮你求解，只需要一些简单的重构工作。另外，**我为你提供了添加自定义运算的机会**。在加减乘除四则运算之外，你可以根据需求定义你独特的运算，并且很方便地加入到代码之中。


![image](https://user-images.githubusercontent.com/83334710/187372834-a7a1a9a0-7ec6-4e44-80a2-43b2d93865d3.png)


-----
### 下面是两个重要的类、基本实现思路、以及一个demo

- Operators类：

  首先自定义一个函数指针类型（参数为两个`int`类型，返回一个`int`类型）

  该类内部拥有一个该函数指针向量，每个指针都指向一个运算函数（加减乘除或者自定义运算），**用户若想添加自定义运算，只需要实现自己定义的运算函数，并将其添加到函数指针向量的末尾即可。这样基本实现了复用和拓展的功能。**

```c++
// Operators

/**
 * @brief  自定义函数指针类型
 * @note   每个该类型的函数指针都指向一个整型运算方法
 */
typedef int (*fptr)(int, int);

/**
 * @brief 运算操作符类
 * @param m_operatorlist：函数指针向量，向量中每一个元素都指向一个运算函数(加减乘除或自定义)
 * @param m_symbollist：运算函数对应的字符(如加法函数对应'+')，用于计算式子的格式化输出
 * @note  函数(m_operatorlist)的下标与字符(m_symbollist)的下标是一一对应的，二者顺序相同
 */
class Operators {
public:
    std::vector<fptr> m_operatorlist;
    std::vector<char> m_symbollist;
public:
    /**
     * @brief Operators的构造函数，将加、减、乘、除四则运算初始化到Operators对象中
     */
    Operators();
    ~Operators();
};
```

- Expression类：

  Expression类的每一个对象都对应一个整数，**不同的是Expression还存储了该整数是通过何种运算得来的**。例如，一个Expression对象对应的整数为10、对应的算式为（2+8）。

  这样的好处在于，对于相同的两个数字，其背后的算式可能不同（如10=2+8，10=2*5）。**通过Expression相当于为每个整数绑定了一个算式，方便最终的格式化输出。**

```c++
/**
 * @brief 表达式类
 * @param m_int: 对象代表的整数
 * @param m_expression: m_int是通过怎样的算式得来的
 * @note  例如：一个Expression的对象，其m_int=10，其m_expression="(2+8)"
 */
class Expression {
public:
    int m_int;
    std::string m_expression;
public:
    Expression() {}
    /**
     * @brief  构造函数的重载、拷贝构造函数，将expression的m_int和m_expression均进行拷贝
     */
    Expression(Expression& expression);
    /**
     * @brief 构造函数的重载，用t_int初始化m_int，并将t_int转化为string类型存储在m_expression中
     */
    Expression(int t_int);
    ~Expression() {}
};
```

- 主要的算法逻辑

  我将每次需要计算的基础数字对应的Expression对象存入一个数组中，称为`now_numbers`

  （基础数字：即本次计算需要用到的数字，如用户提供2、3、5、10，那2、3、5、10就是基础数字；经过一轮计算后，四个数字变为5、5、10，那5、5、10就是本轮次的基础数字）

  主要的计算函数为`mainCalculate()`，该函数接受本轮计算的`now_numbers`、共有几个数字、以及运算方法有哪些

  `mainCalculate()`函数首先会按一定顺序从`now_numbers`取两个对象，先按照正序对这两个对象对应的数字遍历运算符向量中的所有运算方法，得到正序运算结果；然后按照正序对这两个数字再遍历一遍运算方法，得到逆序运算结果。

  新创建一个Expression对象，将运算结果以及本次计算的算式存入到对象当中。

  然后进入判断：

  1.1 若仅剩两个数字，进入1.2；

  ​	  如果此时数字个数大于2，说明没有计算到最后，进入1.3。

  1.2 判断此时结果是否等于24`&&`算式不能重复，若都满足，将新算式添加到全局变量`equations`中

  1.3 将新创建的Expression对象和余下的Expression对象重新组成一个数组，作为参数传给`mainCalculate()`函数，进行递推

  1.4 调用`delete`释放创建新数组所用的空间

- 例子：

  用户输入6、2、3

  为6、2、3分别创建三个Expression变量，组成一个数组，和包含加减乘除的运算操作符对象一起传入`mainCalculate()`函数

  - `mainCalculate()`函数首先选择6、2
    - 加法运算
      - 正向加法，计算结果为8；新创建一个Expression变量，其值设为8，其表达式设为(6+2)
      - 反向加法，计算结果为8；新创建一个Expression变量，其值设为8，其表达式设为（2+6）
      - 判断：此时运算个数为3，未计算到最后
      - 将8对应的Expression和3对应的Expression再组成新数组，传给`mainCalculate()`函数（注：这里8对应的Expression有两个，所以组成了两个新数组）
        - `mainCalculate()`函数选择8、3
          - 加法运算
          - 减法运算
          - 乘法运算
            - 以正向乘法为例：计算结果为24；新创建一个Expression变量，其值设为24，其表达式设为（（6+2）x3）
            - 判断：此时运算数字的个数为2 -> 再判断此时结果是否是24 -> 再判断((6+2)x3)是否重复 -> 将((6+2）x3）存储到全局变量`equations`中 
          - 除法运算
      - 回溯，delete手动new出的数组
    - 6和2的减法运算……
    - ……
    - ……
  - `mainCalculate()`随后选择6、3
  - ……

  - 最后打印出`equations`中的所有表达式
