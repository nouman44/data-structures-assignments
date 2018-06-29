#include <iostream>
using namespace std;

//this function prints all k sized possible subsets by recursion
//index is used to select elements in the recursive process
//len is used to keep track of length to print subset
void PrintSubset(int *S, int *temp, int n, int k, int index, int len)
{
	if (k > 0) //check whether subset needs to be made
	{
		for (int i = index;i < n;i++)
		{
			temp[k - 1] = S[i]; //store item at index in temp array
			
			PrintSubset(S, temp, n, k - 1, i + 1, len + 1); //recursive call where k-1 sized subset is to be found
		}
	}
	else //otherwise print subset
	{
		for (int j = len - 1;j >= 0;j--) //loop to print subset
			cout << temp[j] << " ";

		cout << endl;
	}
}

//this is the wrapper function for the recursive calls
void ListSubsets(int *S, int n, int k)
{
	int *temp = new int[k]; //temp array to hold and print values

	PrintSubset(S, temp, n, k, 0, 0); //recursive function now called

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