#include<bits/stdc++.h>
using namespace std;

class node{
	public : int low,high,maxm;
	node* llink;
	node* rlink;
};
node* root = NULL;
vector<node* > vec;

int findmax(node* nnode)
{
	if(nnode->llink == NULL && nnode->rlink == NULL)
		return nnode->maxm;
	if(nnode->llink == NULL)
		return max(nnode->maxm , (nnode->rlink)->maxm);
	if(nnode->rlink == NULL)
		return max(nnode->maxm , (nnode->llink)->maxm);
	return max(max(nnode->maxm , (nnode->llink)->maxm),(nnode->rlink)->maxm);
}

void insert(node yo)
{
	
	node* nnode = new node();
	if(!root)
	{	root = nnode;
		nnode->low = yo.low;
		nnode->high = yo.high;
		nnode->maxm = yo.high;
		nnode->llink = NULL;
		nnode->rlink = NULL;
		return;
	}
	node* curr = root;
	node* parent;
	vec.clear();
	while(curr)
	{
		vec.push_back(curr);
		parent = curr;
		if(yo.low < curr->low)curr = curr->llink;
		else curr = curr->rlink;		
	}
//	cout<<"here";
	if(parent->low > yo.low)
	{
		parent->llink = nnode;
		nnode->low = yo.low;
		nnode->high = yo.high;
		nnode->maxm = yo.high;
		nnode->llink = NULL;
		nnode->rlink = NULL;
	}
	else
	{
		parent->rlink = nnode;
		nnode->low = yo.low;
		nnode->high = yo.high;
		nnode->maxm = yo.high;
		nnode->llink = NULL;
		nnode->rlink = NULL;
	}
	int i =vec.size()-1;
	
	while(i>=0)
	{
		vec[i]->maxm = findmax(vec[i]);i--;
	}
	
}
void printtree(node* nnode)
{
	if(!nnode)return ;
	cout << "{"<<nnode->low<<","<<nnode->high<<" max="<<nnode->maxm<<"}"<<endl;
	printtree(nnode->llink);
	printtree(nnode->rlink);
}
int main()
{
	
	node temp;
	for(int i=0;i<6;i++)
	{cin >> temp.low >> temp.high;
	insert(temp);
	}
	printtree(root);
	
	
	
}

/*
15 20
10 30
17 19
5 20
12 15
30 40
*/
