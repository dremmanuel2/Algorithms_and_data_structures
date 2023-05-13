#include"vectorskh.cpp"
#include<iostream>
using namespace std;
template<typename T> class stackskh :public vectorskh<T>
{
public:
	void push(T const& e) {this->insert(this->size(),e); }
	T pop() { return this->remove(this->size() - 1); }
	T& top() { return (*this)[this->size()-1]; }
};



