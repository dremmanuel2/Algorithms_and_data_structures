#include <iostream>
#include "stackskh.cpp"
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <cmath>
using namespace std;

stackskh<int> num;  //放数值栈 
stackskh<char> op;  //放符号栈 

void eval()  //处理四则运算 
{
    auto b = num.pop();  //得到后面数字
 
    auto a = num.pop();  //得到前面的数字 

    auto c = op.pop(); //运算符号 
    int x;
    if (c == '+') 
        x = a + b;
    else if (c == '-')
        x = a - b;
    else if (c == '*')
        x = a * b;
    else if (c == '/')
        x = a / b;
    else if (c == '^')
        x = pow(a, b);
    num.push(x);  //结果放回stackskh中
}
int main()
{
    unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}}; //定义运算符优先级 
    string str;
    cin >> str; //输入表达式 
    for (int i = 0; i < str.size(); i++) 
    {
        auto c = str[i];  
        if (isdigit(c)) //如果是数字，获取 
        {
            int x = 0;
            int j = i;
            while (j < str.size() && isdigit(str[j]))
                x = x * 10 + str[j++] - '0'; //多位数处理
            i = j - 1; //退一个，得到数字位置
            num.push(x); //放入 
        }
        else if (c == '(') //括号处理 
            op.push(c);
        else if (c == ')')
        {
            while (op.top() != '(')
                eval(); 
            op.pop();
        }
        else //运算符情况
        {
            while (op.size() && pr[op.top()] >= pr[c])
                eval();
            op.push(c);
        }
    }
    while (op.size())
        eval();
    cout << num.top() << endl;
    return 0;
}
