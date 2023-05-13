#include<cstdio>
//#include<iostream>
//using namespace std;
using Rank = unsigned int; //秩
template <typename T> struct siglelistNode;
template <typename T> using siglelistNodePosi = siglelistNode<T>*;
template <typename T> struct siglelistNode { 
	T data; siglelistNodePosi<T> succ; 

	siglelistNode() {}
	siglelistNode(T e,siglelistNodePosi<T> s = NULL)
		: data(e), succ(s) {}

	siglelistNodePosi<T> insertAsSucc(T const& e);
};
//----------------------------------------------------------------------
template <typename T> class siglelist
{
private:
	Rank _size; siglelistNodePosi<T> header, trailer;
protected:
	void init();
	Rank clear();
	void copyNodes(siglelistNodePosi<T>, Rank);
	void selectionSort(siglelistNodePosi<T>, Rank);
public:
	
	siglelist() { init(); }
	siglelist(siglelist<T> const& L);
	siglelist(siglelist<T> const& L, Rank r, Rank n); 
	siglelist(siglelistNodePosi<T> p, Rank n); 
	
	~siglelist();

	Rank size() const { return _size; }
	siglelistNodePosi<T> operator[](Rank r) const; 
	siglelistNodePosi<T> first() const { return header->succ; }
	siglelistNodePosi<T> find(T const& e) const 
	{
		return find(e, _size, trailer);
	}
	siglelistNodePosi<T> find(T const& e, Rank n, siglelistNodePosi<T> p) const;
	siglelistNodePosi<T> search(T const& e) const 
	{
		return search(e, _size, trailer);
	}
	Rank size() { return _size; }
	siglelistNodePosi<T> search(T const& e, Rank n, siglelistNodePosi<T> p) const;
	siglelistNodePosi<T> selectMax(siglelistNodePosi<T> p, Rank n);
	siglelistNodePosi<T> selectMax() { return selectMax(header->succ, _size); }
	
	siglelistNodePosi<T> insertAsFirst(T const& e);
	siglelistNodePosi<T> insertAsLast(T const& e);
	siglelistNodePosi<T> insertA(siglelistNodePosi<T> p,T const& e);
	T remove(Rank r);

	T removeNode(siglelistNodePosi<T> p);

	void sort(siglelistNodePosi<T> p, Rank n);
	void sort() { sort(first(), _size); }
	Rank deduplicate();
	Rank uniquify();
	void reverse(Rank lo, Rank hi);
	void reverse() { reverse(0, _size); }
	

};
template <typename T> void siglelist <T>::init() { 
	header = new siglelistNode<T>; trailer = new siglelistNode<T>; 
	header->succ = trailer;
	trailer->succ = NULL; 
	_size = 0; 
}
template <typename T>
siglelist<T>::siglelist(siglelistNodePosi<T> p, Rank n) { copyNodes(p, n); }

template <typename T>
siglelist<T>::siglelist(siglelist<T> const& L) { copyNodes(L.first(), L._size); }

template <typename T> 
siglelist<T>::siglelist(siglelist<T> const& L, Rank r, Rank n) {
	siglelistNodePosi<T> p = L.first();
	while (0 < r--) p = p->succ;
	copyNodes(p, n);
}
template <typename T>
void siglelist<T>::copyNodes(siglelistNodePosi<T> p, Rank n) { 
	init();
	siglelistNodePosi<T> zhege=header;
	while (n--) { insertA(zhege, p->data);zhege=zhege->succ; p = p->succ; }
}
template <typename T> 
siglelistNodePosi<T> siglelistNode<T>::insertAsSucc(T const& e) {
	siglelistNodePosi<T> x = new siglelistNode(e,succ);
	succ = x;
	return x;
}
template <typename T> siglelist<T>::~siglelist()
{
	clear(); delete header; delete trailer;
}
template <typename T> Rank siglelist<T>::clear() {
	Rank oldSize = _size;
	while (0 < _size) remove(0);
	return oldSize;
}
template <typename T> siglelistNodePosi<T>  siglelist<T>::operator[](Rank r) const
{
	siglelistNodePosi<T> zhege;
	zhege = header;
	while (r--)zhege = zhege->succ;
	return zhege->succ;
}

template <typename T> siglelistNodePosi<T> siglelist<T>::
	find(T const& e, Rank n, siglelistNodePosi<T> p) const
{
	siglelistNodePosi<T> max= p;
	p = p->succ;
	while (0<--n) { max = p->data == e ? p : max;p = p->succ; }
	return max;
}
template <typename T> siglelistNodePosi<T> siglelist<T>::
	insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}
template <typename T> siglelistNodePosi<T> siglelist<T>::
	search(T const& e, Rank n, siglelistNodePosi<T> p) const
{
	siglelistNodePosi<T> i;
	i = header->succ;
	while (i != p)
	{
		i = i->succ;
	}
	while (i->data < e)
	{
		i = i->succ;
		n--;
	}
	while (i->data == i->succ->data&&n>0)
	{
		i = i->succ;
	}
	return i;
}
template <typename T> siglelistNodePosi<T> siglelist<T>::
	selectMax(siglelistNodePosi<T> p, Rank n)
{
	siglelistNodePosi<T> max;
	max=p;
	p = p->succ;
	while (1 < n--) { max = max->data < p->data ? p : max;p = p->succ; }
	return max;
}
template <typename T>siglelistNodePosi<T> siglelist<T>::
insertA(siglelistNodePosi<T> p,T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}
template <typename T> T siglelist<T>::
removeNode(siglelistNodePosi<T> p)
{
	_size--;
	siglelistNodePosi<T> i;
	siglelistNodePosi<T> j;
	i = header->succ;
	j = header;
	while (i!=p)
	{
			
			i = i->succ;
			j = j->succ;
	}
	T da = i->data;
	j->succ = i->succ;
	delete i;
	return da;
}
template <typename T> T  siglelist<T>::
remove(Rank r)
{
	siglelistNodePosi<T> y;
	siglelistNodePosi<T> x;
	x= header;
	for (Rank i = 0;i < r;i++)
		x = x->succ;
	y = x;
	x=x->succ;
	T da = x->data;
	_size--;
	y->succ = x->succ;
	delete x;
	return da;
}

template <typename T> siglelistNodePosi<T> siglelist<T>::
insertAsLast(T const& e)
{
	siglelistNodePosi p = header;
	for (int i = 0;i < _size;i++)
		p = p->succ;
	_size++;
	return p->insertAssucc(e);
}
template <typename T> void siglelist<T>::
sort(siglelistNodePosi<T> p, Rank n)
{
	selectionSort(p, n);
}


template <typename T> void siglelist<T>::
 selectionSort(siglelistNodePosi<T> p, Rank n)
{
	siglelistNodePosi<T> i;
	siglelistNodePosi<T> j;
	i = header->succ;
	j = header;
	while (i != p)
	{
		i = i->succ;
		j = j->succ;
	}

	while (0 < n--)
	{
		insertA(j,removeNode(selectMax(j->succ,n)));
		j = j->succ;
		
	}
}
template <typename T> Rank siglelist<T>::deduplicate() {
	Rank oldSize = _size;siglelistNodePosi<T> p = first();
	for (Rank r = 0; p != trailer; p = p->succ) 
		if (siglelistNodePosi<T> q = find(p->data, r, p))
			removeNode(q); 
		else r++; 
	return oldSize - _size; 
}
template <typename T> Rank siglelist<T>::uniquify() { 
	if (_size < 2) return 0; 
	Rank oldSize = _size; 
	siglelistNodePosi<T> p = first(); siglelistNodePosi<T> q;
	while (trailer != (q = p->succ)) 
		if (p->data != q->data) p = q; 
		else removeNode(q); 
	return oldSize - _size; 
}
template <typename T> void siglelist<T>:://第三题reverse
reverse(Rank lo, Rank hi)
{
	int n = hi-lo;
	siglelistNodePosi<T> i;
	i = header->succ;
	siglelistNodePosi<T> m;
	m = header;
	siglelistNodePosi<T> j;
	siglelistNodePosi<T> f;
	Rank k = 0;
	while (k<lo)
	{
		i = i->succ;
		m = m->succ;
		k++;
	}
	f = i;
	j = i;
	while (k < hi)
	{
		j = j->succ;
		k++;
	}
	siglelistNodePosi<T> p = j;
	Rank sizze=hi-lo;
	while (sizze--)
	{
		siglelistNodePosi<T> q = new siglelistNode<T>(i->data, p);
		_size++;
		f = i->succ;
		removeNode(i);
		i = f;
		p = q;
	}
	m->succ = p;

}
//int main()
//{
//	siglelist<int> list1;
//	siglelistNodePosi<int> listpois1;
//	for (int i = 0;i < 3;i++)
//			{
//				list1.insertAsFirst(rand()%9);
//			}
//	listpois1 = list1.first();
//
//	
//	cout << "输入： l1 = [";
//	for (Rank i = 0;i < list1.size();i++)
//	{
//
//		cout << listpois1->data;
//		if (i < list1.size() - 1)
//			cout << ',';
//		else
//			cout << ']';
//		listpois1 = listpois1->succ;
//
//	}
//	list1.reverse();
//	listpois1 = list1.first();
//	cout << "输入： l1 = [";
//	for (Rank i = 0;i < list1.size();i++)
//	{
//
//		cout << listpois1->data;
//		if (i < list1.size() - 1)
//			cout << ',';
//		else
//			cout << ']';
//		listpois1 = listpois1->succ;
//
//	}
//	return 0;
//}

