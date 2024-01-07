// Program to show segment tree to demonstrate lazy
// propagation
#include <stdio.h>
#include<bits/stdc++.h>
using namespace std ;
#include <math.h>




#define MAX 1000


#define cust long long
cust func(cust a, cust b) {
	
	return a+b ;
}
cust tree[MAX] = {0}; 
cust lazy[MAX] = {0}; 


void updateRangeUtil(int si, int ss, int se, int us,
					int ue, cust diff)
{
	if (lazy[si] != 0)
	{
		tree[si] = func(tree[si], (se-ss+1)*lazy[si]) ;

		if (ss != se)
		{
			lazy[si*2 + 1] = func(lazy[si], lazy[si*2 + 1]);
			lazy[si*2 + 2] = func(lazy[si], lazy[si*2 + 2]);
		}

		lazy[si] = 0;
	}

	if (ss>se || ss>ue || se<us)
		return ;

	if (ss>=us && se<=ue)
	{
		tree[si] += (se-ss+1)*diff;

		if (ss != se)
		{
			lazy[si*2 + 1] = func(diff, lazy[si*2 + 1]);
			lazy[si*2 + 2] = func(diff, lazy[si*2 + 2]);
		}
		return;
	}

	int mid = (ss+se)/2;
	updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
	updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);

	tree[si] = func(tree[si*2+1] , tree[si*2+2]);
}

void updateRange(int n, int us, int ue, int diff)
{
updateRangeUtil(0, 0, n-1, us, ue, diff);
}

int getSumUtil(int ss, int se, int qs, int qe, int si)
{
	if (lazy[si] != 0)
	{
		tree[si] = func(tree[si], (se-ss+1)*lazy[si]);

		if (ss != se)
		{
			lazy[si*2+1] = func(lazy[si], lazy[si*2+1]);
			lazy[si*2+2] = func(lazy[si], lazy[si*2+2]);
		}

		lazy[si] = 0;
	}

	// Out of range
	if (ss>se || ss>qe || se<qs)
		return 0;
	if (ss>=qs && se<=qe)
		return tree[si];

	int mid = (ss + se)/2;
	return getSumUtil(ss, mid, qs, qe, 2*si+1) +
		getSumUtil(mid+1, se, qs, qe, 2*si+2);
}
int getSum(int n, int qs, int qe)
{
	if (qs < 0 || qe > n-1 || qs > qe)
	{
		printf("Invalid Input");
		return -1;
	}

	return getSumUtil(0, n-1, qs, qe, 0);
}
void constructSTUtil(int arr[], int ss, int se, int si)
{
	if (ss > se)
		return ;

	if (ss == se)
	{
		tree[si] = arr[ss];
		return;
	}

	int mid = (ss + se)/2;
	constructSTUtil(arr, ss, mid, si*2+1);
	constructSTUtil(arr, mid+1, se, si*2+2);

	tree[si] = func(tree[si*2 + 1], tree[si*2 + 2]) ;
}
void constructST(int arr[], int n)
{
	constructSTUtil(arr, 0, n-1, 0);
}


int main()
{
	int arr[] = {1, 3, 5, 7, 9, 11};
	int n = sizeof(arr)/sizeof(arr[0]);

	// Build segment tree from given array
	constructST(arr, n);

	// Print sum of values in array from index 1 to 3
	printf("Sum of values in given range = %d\n",
		getSum(n, 1, 3));

	// Add 10 to all nodes at indexes from 1 to 5.
	updateRange(n, 1, 5, 10);

	// Find sum after the value is updated
	printf("Updated sum of values in given range = %d\n",
			getSum( n, 1, 3));

	cout<<getSum(n, 1,1)<<endl  ;
	cout<<getSum(n, 2,2)<<endl  ;
	cout<<getSum(n, 1,5)<<endl  ;

	return 0;
}
