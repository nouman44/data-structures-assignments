#include <iostream>
using namespace std;

//this function prints all k sized possible subsets by recursive Pascal Identity
//len is used to keep track of length to print subset
void PascalIdentity(int *S, int *temp, int n, int k,int len)
{
	if (k <= n) //check if size of subset to be made is less and equal to number of elements in set
	{
		if (k > 0) //check whether subset needs to be made
		{
			temp[k - 1] = S[n-1]; //in this case nth element is chosen and then call made
			PascalIdentity(S, temp, n - 1, k - 1, len + 1); //recursive call made in which nth element is included.both n-1 and k-1
			
			PascalIdentity(S, temp, n - 1, k, len); //recursive call where nth element not included. only n-1
		}
		else //otherwise print subset
		{
			for (int j = 0;j < len;j++)
				cout << temp[j] << " ";

			cout << endl;
		}
	}
}

//this is the wrapper function for the recursive calls
void ListSubsets(int *S, int n, int k)
{
	int *temp = new int[k]; //temp array to hold and print values

	PascalIdentity(S, temp, n, k, 0); //recursive function now called

	delete[] temp;
}


int main()
{
	int n, k;

	cout << "Enter (n) the number of elements in set: ";
	cin >> n;
	cout << "Enter (k) the number of elements in subset: ";
	cin >> k;
	cout << endl;

	int *S = new int[n];

	for (int i = 0;i < n;i++)
		S[i] = i + 1;

	ListSubsets(S, n, k);

	return 0;
}