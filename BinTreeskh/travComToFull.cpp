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
