#pragma once
#include"BinNodeskh.cpp"
#include<algorithm>
#include<memory>
template <typename T>class BinTreeskh
{
protected:
	int _size;BinNodePosiskh(T)_root;
	virtual int updataHeight(BinNodePosiskh(T) x);
	void updataHeightAbove(BinNodePosiskh(T)x);
public:
	BinTreeskh():_size(0),_root(NULL){}
	BinTreeskh(BinNodePosiskh(T) &ro ) :_size(1), _root(ro) {}
	~BinTreeskh() { if (0 < _size)remove(_root); }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosiskh(T) root() const { return _root;}
	BinNodePosiskh(T) insertAsRoot(T const& e);
	BinNodePosiskh(T) insertAsLC(BinNodePosiskh(T) x,T const& e);
	BinNodePosiskh(T) insertAsRC(BinNodePosiskh(T) x, T const& e);
	BinNodePosiskh(T) attachAsLC(BinNodePosiskh(T) x, BinTreeskh<T>* & T);
	BinNodePosiskh(T) attachAsRC(BinNodePosiskh(T) x, BinTreeskh<T>* & T);
	int remove(BinNodePosiskh(T) x);
	BinTreeskh<T>* secede(BinNodePosiskh(T) x);
	template<typename VST>
	void travLevel(VST& visit) { if (_root)_root->travLevel(visit); }
	template<typename VST>
	void travPre(VST& visit) { if (_root)_root->travPre(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root)_root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root)_root->travPost(visit); }
	void travLevelCompToFull() { if (_root)_root->travLevelCompToFull(); }
	bool operator<(BinTreeskh<T> const& t)
	{return _root && t._root && lt(_root, t._root);}//???
	bool operator==(BinTreeskh<T> const& t)
	{return _root && t._root && (_root==t._root);}
};

template <typename T>
void release(T* s)
{
	delete s;
}
//template <typename T>
//void release(T &s)
//{
//	T* a=NULL;
//	*a = s;
//	delete a;
//}
template<typename T> int BinTreeskh<T>::updataHeight(BinNodePosiskh(T)x)
{return x->height = 1 + std::max(stature(x->lc), stature(x->rc));}
template<typename T>void BinTreeskh<T>::updataHeightAbove(BinNodePosiskh(T)x)
{while (x) { updataHeight(x);x = x->parent; }}
template <typename T> BinNodePosiskh(T)BinTreeskh<T>::insertAsRoot(T const& e)
{_size = 1;return _root = new BinNodeskh<T>(e);}
template <typename T> BinNodePosiskh(T)BinTreeskh<T>::insertAsLC(BinNodePosiskh(T)x, T const& e)
{_size++;x->insertAsLC(e);updataHeightAbove(x);return x->lc;}
template <typename T> BinNodePosiskh(T)BinTreeskh<T>::insertAsRC(BinNodePosiskh(T)x, T const& e)
{_size++;x->insertAsRC(e);updataHeightAbove(x);return x->rc;}
template <typename T>
BinNodePosiskh(T) BinTreeskh<T>::attachAsLC(BinNodePosiskh(T)x,BinTreeskh<T>* &s)
{
	if (x->lc = s->_root)x->lc->parent = x;
	_size += s->_size;updataHeightAbove(x);
	s->_root = NULL;s->_size = 0;release(s);s = NULL;return x;
}
template<typename T>
BinNodePosiskh(T)BinTreeskh<T>::attachAsRC(BinNodePosiskh(T)x,BinTreeskh<T>*&s)
{
	if (x->rc = s->_root)x->rc->parent = x;
	_size += s->_size;updataHeightAbove(x);
	s->_root = NULL;s->_size = 0;release(s);s = NULL;return x;
}
template<typename T>
int BinTreeskh<T>::remove(BinNodePosiskh(T)x)
{
	FromParentTo(*x) = NULL;
	updataHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;

}
template <typename T>
static int removeAt(BinNodePosiskh(T)x)
{
	if (!x)return 0;
	int n = 1 + removeAt(x->lc)+removeAt(x->rc);
	//release(x->data);
	release(x);
	return n;
}
template <typename T> 
BinTreeskh<T>* BinTreeskh<T>::secede(BinNodePosiskh(T) x) 
{
	FromParentTo(*x) = NULL; 
	updataHeightAbove(x->parent); 
	BinTreeskh<T>* S = new BinTreeskh<T>; S->_root = x; x->parent = NULL; 
	S->_size = x->size(); _size -= S->_size; return S; 
}



