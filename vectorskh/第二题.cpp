#include"vectorskh.cpp"
#include<iostream>
using namespace std;

int getK(vectorskh<int>num1, int num1Size, vectorskh<int>num2, int num2Size, int k) {
	int sy1 = 0, sy2 = 0;

	while (true) {
		// 边界情况
		if (sy1 == num1Size) {
			return num2[sy2 + k - 1];
		}
		if (sy2 == num2Size) {
			return num1[sy1 + k - 1];
		}
		//将中位数左边的数全部删除了 
		if (k == 1) {
			return num1[sy1] > num2[sy2] ? num2[sy2] : num1[sy1];
		}

		// 正常情况：获取下一个中位线左边数据的下标 
		int newsy1 = (sy1 + k / 2 - 1) > (num1Size - 1) ? num1Size - 1 : (sy1 + k / 2 - 1);
		int newsy2 = (sy2 + k / 2 - 1) > (num2Size - 1) ? num2Size - 1 : (sy2 + k / 2 - 1);
		int pivot1 = num1[newsy1];
		int pivot2 = num2[newsy2];
		//比较这两个数 
		if (pivot1 <= pivot2) {
			k -= newsy1 - sy1 + 1;
			sy1 = newsy1 + 1;
		}
		else {
			k -= newsy2 - sy2 + 1;
			sy2 = newsy2 + 1;
		}
	}
}

double search(vectorskh<int>num1, int num1Size, vectorskh<int> num2, int num2Size) {
	int tlength = num1Size + num2Size;
	if (tlength % 2 == 1) {
		return getK(num1, num1Size, num2, num2Size, (tlength + 1) / 2);//两个数组的总数为奇数 
	}
	else {
		return (getK(num1, num1Size, num2, num2Size, tlength / 2) + getK(num1, num1Size, num2, num2Size, tlength / 2 + 1)) / 2.0;//两个数组的总数为偶数 
	}
}


int main()
{
	vectorskh<int> a(5, 3, 1);
	vectorskh<int> b(5, 3, 1);
		a[0] = 0;
		a.put(0,5);
		a.put(1, 2);
		a.put(2, 6);
		a.insert(2);
		a.insert(3);
		a.insert(1);
		a.sort();
		a.deduplicate();
		for (int i = 0;i < 6;i++)
			b.insert(i,i);
		cout << search(a,a.size(),b,b.size());

	return 1;
}