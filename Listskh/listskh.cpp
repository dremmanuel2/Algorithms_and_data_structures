#include<cstdio>
#include<iostream>
using namespace std;
using Rank = unsigned int; //÷»

template <typename T> struct ListskhNode;
template <typename T> using ListskhNodePosi = ListskhNode<T>*; 
template <typename T> struct ListskhNode { 
	T data; ListskhNodePosi<T> pred, succ; 
	ListskhNode() {}
	ListskhNode(T e, ListskhNodePosi<T> p = NULL, ListskhNodePosi<T> s = NULL)
		: data(e), pred(p), succ(s) {} 

	ListskhNodePosi<T> insertAsPred(T const& e);
	ListskhNodePosi<T> insertAsSucc(T const& e); 
};
template<typename T>
class Listskh 
{
private:
	Rank _size; ListskhNodePosi<T> header, trailer;

protected:
	void init(); 
	Rank clear(); 
	void copyNodes(ListskhNodePosi<T>, Rank);
	void insertionSort(ListskhNodePosi<T>, Rank);
	void selectionSort(ListskhNodePosi<T>, Rank);
public:
	Listskh() { init(); } 
	Listskh(Listskh<T> const& L);
	Listskh(Listskh<T> const& L, Rank r, Rank n);
	Listskh(ListskhNodePosi<T> p, Rank n);

	~Listskh(); 

	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; } 
	ListskhNodePosi<T> operator[](Rank r) const;
	ListskhNodePosi<T> first() const { return header->succ; } 
	ListskhNodePosi<T> last() const { return trailer->pred; } 
	ListskhNodePosi<T> insertAsFirst(T const& e);
	ListskhNodePosi<T> insertAsLast(T const& e);
	ListskhNodePosi<T> insert(ListskhNodePosi<T> p, T const& e);
	ListskhNodePosi<T> insert(T const& e, ListskhNodePosi<T> p);
	ListskhNodePosi<T> selectMax(ListskhNodePosi<T> p, Rank n); 
	ListskhNodePosi<T> selectMax() { return selectMax(header->succ, _size); }

	T remove(ListskhNodePosi<T> p);
	void sort(ListskhNodePosi<T>, Rank);
	void sort() { sort(first(), _size); }
	ListskhNodePosi<T> search(T const& e) const
	{
		return search(e, _size, trailer);
	}
	ListskhNodePosi<T> search(T const& e, Rank n, ListskhNodePosi<T> p) const;
};
template <typename T> 
ListskhNodePosi<T> ListskhNode<T>::insertAsPred(T const& e) {
	ListskhNodePosi<T> x = new ListskhNode(e, pred, this); 
	pred->succ = x; pred = x; 
	return x; 
}
template <typename T>
ListskhNodePosi<T> ListskhNode<T>::insertAsSucc(T const& e) {
	ListskhNodePosi<T> x = new ListskhNode(e, this, succ);
	succ->pred = x; succ = x;
	return x;
}
template <typename T> 
void Listskh<T>::init()
{
	header = new ListskhNode<T>; trailer = new ListskhNode<T>; 
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}
template <typename T>
void Listskh<T>::copyNodes(ListskhNodePosi<T> p, Rank n)
{
	init();
	while (n--) { insertAsLast(p->data); p = p->succ; }
}
template <typename T>
Listskh<T>::Listskh(Listskh<T> const& L)
{
	copyNodes(L.first(), L.size());
}
template <typename T>
Listskh<T>::Listskh(Listskh<T> const& L, Rank r, Rank n)
{
	ListskhNodePosi<T> p = L.first();
	while (0 < r--) p = p->succ;
	copyNodes(p, n);
}
template <typename T>
Listskh<T>::Listskh(ListskhNodePosi<T> p, Rank n) 
{ copyNodes(p, n); }
template <typename T>
ListskhNodePosi<T> Listskh<T>::operator[](Rank r) const 
{
	ListskhNodePosi<T> p = first();
	while (0 < r--) p = p->succ;
	return p; 
}
template <typename T>
Listskh<T>:: ~Listskh()
{
	clear(); delete header; delete trailer;
}
template <typename T>
Rank Listskh<T>::clear()
{
	Rank oldSize = _size;
	while (0 < _size) remove(header->succ);
	return oldSize;
}
template <typename T>
T  Listskh<T>::remove(ListskhNodePosi<T> p)
{
	T e = p->data; 
	p->pred->succ = p->succ; p->succ->pred = p->pred;
	delete p; _size--; 
	return e;
}
template <typename T>
ListskhNodePosi<T> Listskh<T>::insertAsFirst(T const& e)
{
	_size++;
	 return header->insertAsSucc(e);
}
template <typename T>
ListskhNodePosi<T> Listskh<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}
template <typename T>
void Listskh<T>::sort(ListskhNodePosi<T> p, Rank n)
{
	switch (rand() % 2)
	{
	case 0:insertionSort(p, n);break;
	default:
		selectionSort(p, n);
		break;
	}
	
	
}
template <typename T>
void Listskh<T>::insertionSort(ListskhNodePosi<T> p, Rank n)
{
	for (Rank r = 0; r < n; r++) {
		insert(search(p->data, r, p), p->data);
		p = p->succ; remove(p->pred); 
	}
}
template <typename T> 
ListskhNodePosi<T> Listskh<T>::search(T const& e, Rank n, ListskhNodePosi<T> p) const {
	do { 
		p = p->pred; n--; 
	} while ((-1 != n) && (e < p->data));
	return p;
}
template <typename T> ListskhNodePosi<T> Listskh<T>::insert(ListskhNodePosi<T> p, T const& e)
{
	_size++; return p->insertAsSucc(e);
}

template <typename T> ListskhNodePosi<T> Listskh<T>::insert(T const& e, ListskhNodePosi<T> p)
{
	_size++; return p->insertAsPred(e);
}
template <typename T>
ListskhNodePosi<T> Listskh<T>::selectMax(ListskhNodePosi<T> p, Rank n)
{
	ListskhNodePosi<T> max = p;
	p = p->succ;
	for (int i = 0;i < n-1;i++)
	{
		max = ((max->data) <( p->data)) ? p : max;
		p = p->succ;
	}
	return max;
}
template <typename T>
void Listskh<T>::selectionSort(ListskhNodePosi<T> p, Rank n)
{
	ListskhNodePosi<T> pp = p;
	ListskhNodePosi<T> phead = p;
	ListskhNodePosi<T> ptrail = p->pred;
	for (int i = n;i >0;i--)
	{
		pp = selectMax(p, i);
		if (p != pp)
		{
			pp->pred->succ = pp->succ;
			pp->succ->pred = pp->pred;
			pp->succ = ptrail->succ;
			pp->pred = ptrail;
			ptrail->succ->pred = pp;
			ptrail->succ = pp;
		}
		else
		{
			p = p->succ;
			pp->pred->succ = pp->succ;
			pp->succ->pred = pp->pred;
			pp->succ = ptrail->succ;
			pp->pred = ptrail;
			ptrail->succ->pred = pp;
			ptrail->succ = pp;
		}

	}
}

//int main()
//{
//	Listskh<int> list1;
//	
//	for (int i = 0;i < 5;i++)
//		list1.insertAsFirst(rand()%8);
//	ListskhNodePosi<int> p = list1.first();
//	for (int i = 0;i < 5;i++)
//	{
//		cout << p->data;
//		p = p->succ;
//	}
//	cout << endl;
//	list1.sort();
//	p = list1.first();
//	for (int i = 0;i < 5;i++)
//	{
//		cout << p->data;
//		p = p->succ;
//	}
//	cout << endl;
//	return 0;
//}