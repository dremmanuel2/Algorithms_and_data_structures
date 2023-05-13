#include<iostream>
#include<cstdio>
#include"listskh.cpp"

using namespace std;
using T = int;
class  Solution//第二题第一个任务
{
public:
	siglelistNodePosi<T>  addTwoNumbers
	(siglelistNodePosi<T> l1, siglelistNodePosi<T> l2)
	{
		siglelistNodePosi<T> l3;
		l3 = new siglelistNode<T>;
		return l3->insertAsSucc((l1->data) + (l2->data));
	}
};

int main()
{
	T num1, num2, num3;
	num1 = num2 = num3 = 0;
	siglelist<int> list1, list2;
	siglelistNodePosi<T> listpois1, listpois2, listpois3;
	for (int i = 0;i < 3;i++)
	{
		list1.insertAsFirst(rand()%8);
		list2.insertAsFirst(rand()%8);
	}
	siglelist<int> list3;
	listpois1 = list1.first();
	listpois2 = list2.first();
	
	Solution add;
	cout << "输入： l1 = [";
	for (Rank i = 0;i < list1.size();i++)
	{

		cout << listpois1->data;
		num1 += pow(10, i)* listpois1->data;
		if (i < list1.size() - 1)
			cout << ',';
		else
			cout << ']';
		listpois1 = listpois1->succ;

	}
	cout << " l2 = [";
	for (Rank i = 0;i < list2.size();i++)
	{

		cout << listpois2->data;
		num2 += pow(10, i) * listpois2->data;
		if (i < list2.size() - 1)
			cout << ',';
		else
			cout << ']';
		listpois2 = listpois2->succ;
	}
	cout << endl;
	listpois1 = list1.first();
	listpois2 = list2.first();
	listpois3 = list3.first();
	T yushu = 0;
	for (Rank i = 0;i < (list1.size() < list2.size() ? list1.size() : list2.size());i++)
	{
		T da = ((add.addTwoNumbers(listpois1, listpois2))->data)+yushu;
		if (i == 0)
		{
			list3.insertAsFirst(da % 10);
			da /= 10;
			listpois3 = list3.first();
			yushu =(da > 0)? da : 0;
			
		}
		else
		{
			list3.insertA(listpois3,da%10);
			da /= 10;
			listpois3 = listpois3->succ;
			yushu = (da > 0) ? da : 0;
		}
		
		listpois1 = listpois1->succ;
		listpois2 = listpois2->succ;
		
	}
	if (yushu > 0)
		list3.insertA(listpois3, yushu);
	
	listpois3 = list3.first();
	
	cout << "输出：[";
	for (Rank i = 0;i < list3.size();i++)
	{

		cout << listpois3->data;
		num3 += pow(10, i) * listpois3->data;
		if (i < list3.size() - 1)
			cout << ',';
		else
			cout << ']';

		listpois3 = listpois3->succ;
	}
	cout <<endl<< "解释: " << num1 << "+" << num2 << "=" << num3;
	return 0;
}