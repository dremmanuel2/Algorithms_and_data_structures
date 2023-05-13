#include <iostream>
#include "stackskh.cpp"
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <cmath>
using namespace std;

stackskh<int> num;  //����ֵջ 
stackskh<char> op;  //�ŷ���ջ 

void eval()  //������������ 
{
    auto b = num.pop();  //�õ���������
 
    auto a = num.pop();  //�õ�ǰ������� 

    auto c = op.pop(); //������� 
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
    num.push(x);  //����Ż�stackskh��
}
int main()
{
    unordered_map<char, int> pr{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}}; //������������ȼ� 
    string str;
    cin >> str; //������ʽ 
    for (int i = 0; i < str.size(); i++) 
    {
        auto c = str[i];  
        if (isdigit(c)) //��������֣���ȡ 
        {
            int x = 0;
            int j = i;
            while (j < str.size() && isdigit(str[j]))
                x = x * 10 + str[j++] - '0'; //��λ������
            i = j - 1; //��һ�����õ�����λ��
            num.push(x); //���� 
        }
        else if (c == '(') //���Ŵ��� 
            op.push(c);
        else if (c == ')')
        {
            while (op.top() != '(')
                eval(); 
            op.pop();
        }
        else //��������
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
