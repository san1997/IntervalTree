//This program inserts intervals in interval tree and searchs for any given interval
//If the interval is not found in the tree , then it returns the interval[-1,-1]
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

node search(node* nnode,node yo)
{
	node temp;
	temp.low = -1;temp.high = -1;
	
	if(nnode->low <= yo.low && nnode->high>=yo.low)return *nnode;
	if(nnode->low <= yo.high && nnode->high >=yo.high)return *nnode;
	
	if(nnode->llink != NULL &&  (nnode->llink)->maxm > yo.low)return search(nnode->llink,yo);
	if(nnode->rlink != NULL)return search(nnode->rlink,yo);
	return temp;
}
node* moveright(node* nnode)
{
	if(nnode->rlink == NULL)return nnode;
	return moveright(nnode->rlink);
}
node* moveleft(node* nnode)
{
	if(nnode->llink == NULL)return nnode;
	return moveleft(nnode->llink);
}

void findmaxms()
{
	queue<node* > q;
	q.push(root);
	vec.clear();
	while(q.size()!=0)
	{	
		node* f = (q.front());
	//	cout << q.front() <<" " <<f<<endl;
		vec.push_back(q.front());
		if((q.front())->llink != NULL)q.push(f->llink);
		if((q.front())->rlink != NULL)q.push(f->rlink);
		q.pop();
	}
//	cout <<"yup";
	int i =vec.size()-1;

	while(i>=0)
	{	//cout <<"yes";
		vec[i]->maxm = findmax(vec[i]);i--;
	}
}

void deletenode(node* nnode,node yo)
{
	if(yo.low == nnode->low && yo.high == nnode->high)
	{
		
		if(nnode->rlink!= NULL)
		{
			node* temp = moveleft(nnode->rlink);
			nnode->high = temp->high;
			nnode->low = temp->low;
			nnode->maxm = temp->maxm;
			temp = NULL;
		}
		if(nnode->llink != NULL)
		{
			node* temp = moveright(nnode->llink);
			nnode->high = temp->high;
			nnode->low = temp->low;
			nnode->maxm = temp->maxm;
			temp = NULL;
		}
		else{
			nnode = NULL;	
		}
		findmaxms();
		return ;
	}
	if(nnode->low >= yo.low)
	{
		deletenode(nnode->llink,yo);
	}
	else{
		deletenode(nnode->rlink,yo);
	}
	
}

int main()
{
	
	
	node temp;
	for(int i=0;i<6;i++)
	{cin >> temp.low >> temp.high;
	insert(temp);
	}
	//printtree(root);
	for(int i=0;i<2;i++){
		cin >> temp.low >> temp.high ;
		node found = search(root,temp);
		cout << "Overlaps with the interval {"<<found.low<<","<<found.high<<"}"<<endl;
	}
	
}

/*
15 20
10 30
17 19
5 20
12 15
30 40
14 16
21 23
*/
