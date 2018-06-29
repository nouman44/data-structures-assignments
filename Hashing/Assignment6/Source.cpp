#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

//this is a helper function for the acid hash function
int AssignVal(char input)
{
	if (input == 'a' || input == 'A') //if A assign 1
		return 1;
	else if (input == 'c' || input == 'C') //if C assign 2
		return 2;
	else if (input == 'g' || input == 'G') //if G assign 3
		return 3;
	else if (input == 't' || input == 'T') //if T assign 4
		return 4;
	else
		return -1; //else return -1
}

//this is the primary acid hash function
int AcidHashFunction(char *arr) //an arr of size 3 is input
{
	int val, c = 2, index = 0;
	
	for (int i = 0;i < 3;i++) //loop to calculate the index
	{
		val = AssignVal(arr[i]);

		if (val != -1)
			index = index + (val*pow(c, i)*pow(c, i));
		else
			return 0;
	}

	return index; //calculated index is then returned
}

//this is the primary acid hash function
int SinglesHashFunction(char *arr) //an arr of size 3 is input
{
	int index = 0;

	for (int i = 0;i < 3;i++) //loop to calculate the index
	{
		if (i == 2)
			index = index + (3 * arr[i]);
		else
			index = index - arr[i];
	}

	index = index % 41; //take modulus with table size

	return index; //calculated index is then returned
}

//this function reads the values of nucelotides from a file and then stores them as amino acids
void FillAcidHash(char **table)
{
	ifstream inStrm("acidhash.txt"); //input file
	char c;
	int comb = 64, size = 3, index;
	char *arr = new char[size];

	for (int i = 0;i < comb;i++) //loop till number of combinations
	{
		for (int j = 0;j < size;j++) //read polynucleotide seq of 3 
		{
			inStrm >> c;
			arr[j] = c;
		}

		index = AcidHashFunction(arr); //apply acid hash function to get index

		for (int j = 0;j < size;j++) //store the amino acid seq in the acid hash table
		{
			inStrm >> c;
			table[index][j] = c;
		}
	}

	inStrm.close(); //close stream

	delete[] arr;
}

int hash2(char str[])
{
	return (str[0] + str[1] - (3 * str[2]));
}

//this function reads the values of amino acids from a file and then stores them as single letter abbrv
void FillSinglesHash(char *table)
{
	ifstream inStrm("singleshash.txt"); //input file
	char c;
	int amino = 21, size = 3, index;
	char *arr = new char[size];

	for (int i = 0;i < amino;i++) //loop till number of combinations
	{
		for (int j = 0;j < size;j++) //read amino acid seq of 3 
		{
			inStrm >> c;
			arr[j] = c;
		}

		index = SinglesHashFunction(arr); //apply singles hash function to get index
		inStrm >> c;
		table[index] = c; //store the single abbrev in the singles hash table
	}

	inStrm.close(); //close stream

	delete[] arr;
}

//this is a helper function which removes spaces from input and converts it to uppercase
void RemoveSpaces(char * &arr, int & size)
{
	int i, index = 0;

	char *temp = new char[100];

	for (i = 0;i < size;i++)
	{
		if (arr[i] != 32) //copy characters other than spaces
		{
			temp[index] = arr[i] - 32;
			index++;
		}
	}

	temp[index] = NULL;

	delete[] arr;
	arr = temp;
	size = index; //update size
}

//this function deletes the acid hash and singles hash tables
void DeallocateArrays(char **table1, char *table2, int size1)
{
	for (int i = 0;i < size1;i++)
		delete[] table1[i];

	delete[] table1;

	delete[] table2;
}

int main()
{
	char **acidHash, *singlesHash, *arr, *seq; //declaration for all character arrays
	int acidSize = 127, singlesSize = 41, index, len, counter, pos; //int vars declared
	char *input = new char[100];
	arr = new char[3];

	acidHash = new char*[acidSize]; //allocate space to acid hash table

	for (int i = 0;i < acidSize;i++)
		acidHash[i] = new char[3];

	singlesHash = new char[singlesSize]; //allocate space to singles hash table

	FillAcidHash(acidHash); //call function to fill acid hash table

	FillSinglesHash(singlesHash); //call function to fill singles hash table

	cout << "Enter a nucleotide sequence, or just press ENTER to quit: ";
	cin.getline(input, 100); //take input
	len = strlen(input);
	RemoveSpaces(input, len); //remove spaces and convert to uppercase

	while (len != 0) //loop until user presses enter
	{
		pos = 0;

		if (len % 3 == 0) //if there is a complete set of triples
		{
			counter = len / 3; //number of seq
			seq = new char[counter];

			for (int i = 0;i < counter;i++) //loop no of sequence
			{
				for (int j = 0;j < 3;j++) //read a sequence
				{
					arr[j] = input[pos];
					pos++;
					cout << arr[j];
				}
				cout << "   ";

				index = AcidHashFunction(arr); //calculate index for the amino acid

				if (index != 0) //if valid seq
				{
					for (int j = 0;j < 3;j++) //output the amino acid seq
					{
						arr[j] = acidHash[index][j];
						cout << acidHash[index][j];
					}
						
					index = SinglesHashFunction(arr); //calculate index for single letter abbrev

					seq[i] = singlesHash[index]; 
				}
				else //if invalid seq
				{
					cout << "invalid sequence";
					seq[i] = '?';
				}

				cout << endl;
			}

			cout << "One-letter abbreviations: ";
			for (int j = 0;j < counter;j++) //ouput one letter abbrev
				cout << seq[j];

			delete[] seq;
			cout << endl;
		}
		else //if not complete set of triples then error
			cout << "Error: You must give complete triples." << endl;

		//take input from user
		cout << endl << "Enter a nucleotide sequence, or just press ENTER to quit: ";
		cin.getline(input, 100);
		len = strlen(input);
		RemoveSpaces(input, len);
	}

	DeallocateArrays(acidHash, singlesHash, acidSize); //delete the acid hash and singles hash table

	delete[] arr;
	delete[] input; //delete input arr

	return 0;
}