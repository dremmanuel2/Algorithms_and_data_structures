#pragma once
#include"BinTreeskh.cpp"
#include<iostream>
#include<vector>

using namespace std;
void visit(int x)
{
	static int y = NULL;
	if (y)
		cout << "->" << x;
	else
		cout << x;
	y = x;
}
void visit2(int x)
{
	static int y = 0;
	if (y++)
		if (x)
			cout << "," << x;
		else
			cout << "," << "null";
	else
		if (x)
			cout <<x;
		else
			cout << "null";
		
}
class Solution
{
public:
	BinNodeskh<int>* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		BinTreeskh<int>* Btree=new BinTreeskh<int>;
		BinNodePosiskh(int)ro= Btree->insertAsRoot(preorder[0]);
		vector<int>pre((preorder.begin() + 1), preorder.end());
		vector<int>ver1;vector<int>ver2;
		int posi = 0;
		while (inorder[posi] != preorder[0])posi++;
		for (int i = 0;i < posi;i++)
			ver1.push_back(inorder[i]);
		for (int i = posi + 1;i < inorder.size();i++)
			ver2.push_back(inorder[i]);
		if (ver1.size() > 0)
		{
			BinTreeskh<int>* LT = FindL(ver1, pre);
			Btree->attachAsLC(ro, LT);
		}
		if (ver2.size() > 0)
		{
			BinTreeskh<int>* RT = FindR(ver2, pre);
			Btree->attachAsRC(ro, RT);
		}
		ro->travLevelCompToFull();
		return ro;
	}
	BinTreeskh<int>* FindL(vector<int>& ver, vector<int>& pre)
	{
		if (ver.size() == 1) 
		{	BinTreeskh<int>* TL=new BinTreeskh<int>;
			TL->insertAsRoot(ver[0]);
			pre.erase(pre.begin());
			return TL;
		}
		BinTreeskh<int>* TIN=new BinTreeskh<int>;
		BinNodePosiskh(int) tin= TIN->insertAsRoot(pre[0]);
		vector<int>ver1;vector<int>ver2;
		int posi=0;
		while (ver[posi] != pre[0])posi++;
		for (int i = 0;i < posi;i++)
			ver1.push_back(ver[i]);
		for (int i = posi+1;i < ver.size();i++)
			ver2.push_back(ver[i]);
		pre.erase(pre.begin());
		if (ver1.size() > 0)
		{
			BinTreeskh<int>* LT = FindL(ver1, pre);
			TIN->attachAsLC(tin, LT);
		}
		if (ver2.size() > 0)
		{
			BinTreeskh<int>* RT = FindR(ver2, pre);
			TIN->attachAsRC(tin, RT);
		}
		return TIN;
	}
	BinTreeskh<int>* FindR(vector<int>& ver, vector<int>& pre)
	{
		if (ver.size() == 1)
		{
			BinTreeskh<int>* TL = new BinTreeskh<int>;
			TL->insertAsRoot(ver[0]);
			pre.erase(pre.begin());
			return TL;
		}
		BinTreeskh<int>* TIN = new BinTreeskh<int>;
		BinNodePosiskh(int) tin = TIN->insertAsRoot(pre[0]);
		vector<int>ver1;vector<int>ver2;
		int posi = 0;
		//cout << ver[posi]<<ver[1]<<ver[2];
		while (ver[posi] != pre[0])posi++;
		for (int i = 0;i < posi;i++)
			ver1.push_back(ver[i]);
		for (int i = posi + 1;i < ver.size();i++)
			ver2.push_back(ver[i]);
		pre.erase(pre.begin());
		if(ver1.size()>0)
		{
			BinTreeskh<int>* LT = FindL(ver1, pre);
			TIN->attachAsLC(tin, LT);
		}
		if (ver2.size() > 0)
		{
			BinTreeskh<int>* RT = FindR(ver2, pre);
			TIN->attachAsRC(tin, RT);
		}
		return TIN;
	}
};
int main()
{
	BinTreeskh<int> task1;
	BinNodePosiskh(int) node1 =task1.insertAsRoot(3);
	BinNodePosiskh(int) node2 = task1.insertAsLC(node1, 9);
	BinNodePosiskh(int) node3= task1.insertAsRC(node1, 20);
	BinNodePosiskh(int) node4=task1.insertAsLC(node3, 15);
	BinNodePosiskh(int) node5 = task1.insertAsRC(node3, 7);
	BinNodePosiskh(int) node6 = task1.insertAsRC(node2, 16);
	task1.travIn(visit);cout << endl;
	vector<int> preorder{3,9,20,15,7};
	vector<int> inorder{9,3,15,20,7};
	Solution method;
	BinNodePosiskh(int) root = method.buildTree(preorder, inorder);
	cout << "[";
	root->travLevel(visit2);
	cout << "]" << endl;
}