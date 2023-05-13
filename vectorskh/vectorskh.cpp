#include"iostream"
#include<cstdio>
#include"Fib.h"
#define DEFAULT_capcity 3
using namespace std;

//class Fib
//{
//protected:
//
//	int num=0;
//	int f(int n) {
//		if (n == 1 || n == 2)
//			return 1;
//		else
//			return f(n - 1) + f(n - 2);
//	}
//public:
//	Fib(int n)
//	{
//		num = n;
//	}
//
//	int get()
//	{
//		return f(num);
//	}
//	void prev()
//	{
//		num--;
//	}
//
//};

typedef int Rank;
template <typename T> class vectorskh
{
protected:
	Rank _size;int  _capacity;T* _elem;
	void copyFrom(T const* A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];_size = 0;
		while (lo < hi)
			_elem[_size++] = A[lo++];
	}
	void expand();
	void shrink();
	void selectionSort(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi)
	{
		bool sorted = true;
			for (int i = 0;i < hi-lo-1;i++)
			{
				sorted = true;
				for (int j = lo;j < hi-i;j++)
					if (_elem[j] > _elem[j + 1])
					{
						T t;
						t = _elem[j];
						_elem[j] = _elem[j + 1];
						_elem[j + 1] = t;
						sorted = false;
					}
			}
	}
	Rank max(Rank lo, Rank hi)
	{
		T MAX =NULL;
		for (int i = lo;i < hi;i++)
			MAX = _elem[MAX] < _elem[i] ? i : MAX;
		return MAX;
	}
	
	void merge(Rank lo, Rank mi,Rank hi);
	void mergeSort(Rank lo, Rank hi);

//	template <typename T> 
 static Rank fibsearch(T* A, T const& e, Rank lo, Rank hi)
	{
	 Fib fib(hi - lo);
	 while (lo < hi)
	 {
		 while (hi - lo < fib.get())fib.prev();
		 Rank mi = lo + fib.get() - 1;
		 if (e < A[mi])hi = mi;
		 else if (A[mi] < e)lo = mi + 1;
		 else return mi;
	 }
	}

public:
	vectorskh(int c = DEFAULT_capcity,int s=0,T v =0 )
	{
		//c = s > c ? s<<2 : c;
		_elem = new T[_capacity = c];for (_size = 0;_size < s;_elem[_size++] = v);
		//expand;

	}
	vectorskh(T const* A, Rank n) { copyFrom(A, 0, n); }
	vectorskh(T const*A,Rank lo,Rank hi) { copyFrom(A, lo, hi); }
	vectorskh(vectorskh<T>const&V) { copyFrom(V._elem, 0, V._size); }
	vectorskh(vectorskh<T>const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
	~vectorskh() { delete[]_elem; }
	Rank size() const { return _size; }
	T get(Rank r) { return _elem[r]; }
	void put(Rank r, T e) { _elem[r] = e; }
	bool empty()const { return !_size; }

	int disordered()const
	{
		int num=0;
		for (int i = 1;i < _size;i++)
			for (int j = 0;j < i;j++)
				num += _elem[j] > _elem[i] ? 1 : 0;
		return num;
	}

	Rank find(T const& e)const { return find(e, 0, _size); }
	Rank find(T const& e, Rank lo, Rank hi)const;
	Rank search(T const& e, Rank lo, Rank hi)const;
	Rank search(T const&e)const	{return (0 >= _size) ? -1 : search(e, 0, _size);}

	
	T& operator[](Rank r)const { return _elem[r]; }
	vectorskh<T>& operator = (vectorskh<T> const& V);
	int remove(Rank lo, Rank hi)
	{
		while (hi <_size)
			_elem[lo++] = _elem[hi++];
		_size = lo;
		shrink();
		return hi - lo;

	}
	T remove(Rank r)
	{
		T e = _elem[r];
		remove(r, r + 1);
		return e;

	}

	Rank insert(Rank r, T const& e)
	{
		_size++;
		expand();
		int i = _size;
		while (i>r)
		{
			_elem[i] = _elem[i - 1];
			i--;
		}
		_elem[r] = e;
		return r;

	}
	Rank insert(T const& e) { return insert(_size, e); }//----


	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }

	int deduplicate();
	int uniquify();

};

//------------------------------------------------------------------------------------

template <typename T>
Rank vectorskh<T>::find(T const& e, Rank lo, Rank hi)const
{
	while ((hi-- > lo) && (e != _elem[hi]));
	return hi;
}
template <typename T>
void vectorskh<T>::expand()
{
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_capcity)_capacity = DEFAULT_capcity;
	T* old = _elem;_elem = new T[_capacity <<= 1];
	for (int i = 0;i < _size;i++)
		_elem[i] = old[i];
	delete[]old;
}
template <typename T>
void vectorskh<T>::shrink()
{
	if (_capacity < DEFAULT_capcity << 1)return;
	if (_size << 2 > _capacity)return;
	T* old = _elem;_elem = new T[_capacity >>= 1];
	for (int i = 0;i < _size;i++)_elem[i] = old[i];
	delete[]old;
}
template <typename T> vectorskh<T>& vectorskh<T>:: operator = (vectorskh<T> const& V)
	{
		if (_elem) delete [] _elem;
		copyFrom(V._elem, 0, V.size());
		return *this;
	}

template <typename T>void vectorskh<T>:: mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)return;
	int mi = (lo + hi) / 2;
	mergeSort(lo, mi);mergeSort(mi, hi);
	merge(lo, mi, hi);
}
template <typename T>void vectorskh<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;
	int lb = mi - lo;T* B = new T[lb];
	for (Rank i = 0;i < lb;B[i] = A[i++]);
	int lc = hi - mi;T* C = _elem + mi;
	for (Rank i = 0, j = 0, k = 0;(j < lb) || (k < lc);)
	{
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] <= B[j])))A[i++] = C[k++];
	}
	delete[]B;
}


template <typename T>static Rank binsearch(T* A, T const& e, Rank lo, Rank hi)
{
	while (1 < hi - lo)
	{
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;
	}
	return(e == A[lo]) ? lo : -1;
}
template <typename T>void vectorskh<T>:: selectionSort(Rank lo, Rank hi)
{
	Rank r = -1;
	for (int i = lo;i < hi;i++)
	{
		r = max(lo, hi - i);
		insert(hi - i, _elem[r]);
		remove(r);
	}
}
template <typename T>	Rank vectorskh<T>::search(T const& e, Rank lo, Rank hi)const
{
	if (disordered())return -1;
	switch(rand() % 2)
	{
		case 0: return binsearch(_elem, e, lo, hi);break;
		case 1: return fibsearch(_elem, e, lo, hi);break;
	}
}
template <typename T>void vectorskh<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 3)
	{
	case 0:bubbleSort(lo,hi);break;
	case 1:selectionSort(lo,hi);break;
	case 2: mergeSort(lo, hi);break;
	default:
		break;
	}
}
//template <typename T>int vectorskh<T>::deduplicate()
//{
//	int oldsize = _size;
//	Rank i = 1;
//	while (i < _size)
//		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
//	return oldsize - _size;
//}
template <typename T> int vectorskh<T>::deduplicate()
{	int oldSize = _size;
	for (Rank i = 1;i < _size; i++)
	{ 
	Rank j = find(_elem[i], 0, i);
	if (j >= 0) remove(j);
	}
	return oldSize - _size;
}

template <typename T>int vectorskh<T>::uniquify()
{
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = i++;shrink();
	return j - i;
}
//template <typename T>
//template <typename T>








//int main()
//{
//	vectorskh<int> a(5,3,1);
////	a[0] = 0;
//	a.put(0,5);
//	a.put(1, 2);
//	a.put(2, 6);
//	a.insert(2);
//	a.insert(3);
//	a.insert(1);
//	a.sort();
//	for(int i=0;i<a.size();i++)
//		cout << a[i]<<endl;
//	cout << a.search(3) << endl;
//	cout << a.disordered() << endl;
//	//cout << a.size();
//	return 1;
//}
