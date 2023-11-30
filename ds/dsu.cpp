// C++ implementation of disjoint set

#include <bits/stdc++.h>
using namespace std;

class DisjSet {
	int *rank, *parent, n;

public:
	int comp ;
	DisjSet(int n) ;
	void makeSet() ;
	int find(int x) ;
	void Union(int x, int y) ;
	int countDscnt() ;

};

DisjSet::DisjSet(int n) {
	rank = new int[n];
	parent = new int[n];
	this->n = n;
	this->comp = n;
	makeSet();
}

void DisjSet::makeSet()
{
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
}


int DisjSet::find(int x)
{
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	return parent[x];
}


void DisjSet::Union(int x, int y)
{
	int xset = find(x);
	int yset = find(y);
	if (xset == yset)
		return;
	comp-- ;
	if (rank[xset] < rank[yset]) {
		parent[xset] = yset;
	}
	else if (rank[xset] > rank[yset]) {
		parent[yset] = xset;
	}
	else {
		parent[yset] = xset;
		rank[xset] = rank[xset] + 1;
	}
}

int DisjSet::countDscnt() {
	int count=0 ;
	for (int i = 0; i < n; ++i)
	{
		if (parent[i]==i) count++ ; 
	}

	return count ;
}


// Driver Code
int main()
{

	// Function Call
	DisjSet obj(5);
	obj.Union(0, 2);
	obj.Union(4, 2);
	obj.Union(3, 1);

	if (obj.find(4) == obj.find(0))
		cout << "Yes\n";
	else
		cout << "No\n";
	if (obj.find(1) == obj.find(0))
		cout << "Yes\n";
	else
		cout << "No\n";

	return 0;
}
