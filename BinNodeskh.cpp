#pragma once
#define BinNodePosiskh(T) BinNodeskh<T>*
#define stature(p) ((p)?(p)->height:-1)
#include<cstdio>
#include<queue>
#include<iostream>
typedef enum {RB_RED,RB_BlACK} RBColor;

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )
#define sibling( p ) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*兄弟*/
#define uncle( x ) ( sibling( (x)->parent ) ) /*叔叔*/
#define FromParentTo( x ) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


template <typename T>struct BinNodeskh
{
	T data;
	BinNodePosiskh(T) parent; BinNodePosiskh(T) lc;BinNodePosiskh(T) rc;
	int height;
	int npl;
	RBColor color;
	BinNodeskh() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1),color(RB_RED){}
	BinNodeskh(T e, BinNodePosiskh(T)p = NULL, BinNodePosiskh(T)lc = NULL, BinNodePosiskh(T)rc = NULL,
				int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}
	//int size();
	BinNodePosiskh(T) insertAsLC(T const&);
	BinNodePosiskh(T) insertAsRC(T const&);
	BinNodePosiskh(T) succ();
	template <typename VST>void travLevel(VST&);
	template <typename VST>void travPre(VST&);
	template <typename VST>void travIn(VST&);
	template <typename VST>void travPost(VST&);
	void travLevelCompToFull();
	bool operator < (BinNodeskh const& bn) { return data < bn.data; }
	bool operator > (BinNodeskh const& bn) { return data > bn.data; }
	bool operator <= (BinNodeskh const& bn) { return data <= bn.data; }
	bool operator >= (BinNodeskh const& bn) { return data >= bn.data; }
	bool operator == (BinNodeskh const& bn) { return data == bn.data; }
	bool operator != (BinNodeskh const& bn) { return data != bn.data; }
};
template<typename T>BinNodePosiskh(T) BinNodeskh<T>:: insertAsLC(T const& e)
{return lc = new BinNodeskh(e, this);}
template<typename T>BinNodePosiskh(T) BinNodeskh<T>::insertAsRC(T const& e)
{return rc = new BinNodeskh(e, this);}
template<typename T>BinNodePosiskh(T) BinNodeskh<T>::succ()
{
	BinNodePosiskh(T)s = this;
	if (rc)
	{
		s = rc;
		while (HasLChild(*s))s = s->lc;
	}
	else
	{
		while (IsRChild(*s))s = s->parent;
		s = s->parent;
	}
	return s;
}
template <typename T>template <typename VST>
void BinNodeskh<T>::travPre(VST& visit)
{travPre_I(this, visit);}
template <typename T>template <typename VST>
void BinNodeskh<T>::travIn(VST& visit)
{travIn_I(this, visit);}
template <typename T>template <typename VST>
void BinNodeskh<T>::travPost(VST& visit)
{travPost_I(this, visit);}
template <typename T>template <typename VST>
void BinNodeskh<T>::travLevel(VST& visit)
{
	std::queue<BinNodePosiskh(T)> Q;
	Q.push(this);
	while (!Q.empty())
	{
		BinNodePosiskh(T)x = Q.front();
		Q.pop();
		visit(x->data);
		if (HasLChild(*x))Q.push(x->lc);
		if (HasRChild(*x))Q.push(x->rc);
	}
}
template <typename T>
void BinNodeskh<T>::travLevelCompToFull()
{
	std::queue<BinNodePosiskh(T)> Q;
	Q.push(this);
	while (!Q.empty())
	{
		BinNodePosiskh(T)y;
		BinNodePosiskh(T)x = Q.front();
		if (IsRoot(*x))
		{
			y = NULL;
			
		}
		else
		{
			y = (sibling(x));
		}
		Q.pop();
		if (HasLChild(*x))
		{
			Q.push(x->lc);
		}
		else if (y)
		{
			if (HasChild(*y))
				Q.push(x->insertAsLC(NULL));
			
		}
		if (HasRChild(*x))
		{
			Q.push(x->rc);
		}
		else if (y)
		{
			if (HasChild(*y))
				Q.push(x->insertAsRC(NULL));
		}
	}
}
template <typename T,typename VST>
void travPre_I(BinNodePosiskh(T) x, VST& visit)
{
	if (!x)return;
	visit(x->data);
	travPre_I(x->lc, visit);
	travPre_I(x->rc, visit);
}
template <typename T, typename VST>
void travIn_I(BinNodePosiskh(T) x, VST& visit)
{
	bool backtrack = false;
	while (true)
		if (!backtrack && HasLChild(*x))
			x = x->lc;
		else
		{
			visit(x->data);
			if (HasRChild(*x))
			{
				x = x->rc;
				backtrack = false;
			}
			else
			{
				if (!(x = x->succ()))break;
				backtrack = true;
			}
		}
}
template <typename T, typename VST>
void travPost_I(BinNodePosiskh(T) x, VST& visit)
{
	if (!x)return;
	travPost_I(x->lc, visit);
	travPost_I(x->rc, visit);
	visit(x->data);
}