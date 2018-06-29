#include <iostream>
using namespace std;

//template class declaration for stack
template <class Type>
class Stack
{
private:
	Type *stackArr; //array for stack
	int stackPtr;
	int maxSize;

public:
	Stack(int size = 10) //paramertized constructor
	{
		maxSize = size;
		stackArr = new Type[maxSize];
		stackPtr = 0;
	}

	Stack(const Stack & source) //copy constructor
	{
		maxSize = source.maxSize;
		stackArr = new Type[maxSize];

		stackPtr = source.stackPtr;

		for (int i = 0; i < stackPtr; i++)
			stackArr[i] = source.stackArr[i];
	}

	bool IsFull() //function to check if stack if full
	{
		if (stackPtr == maxSize)
			return true;
		else
			return false;
	}

	bool IsEmpty() //function to check if stack is empty
	{
		if (stackPtr == 0)
			return true;
		else
			return false;
	}

	//this function pushes the data item on stack if it is not fulll otherwise returns false
	bool Push(const Type data) 
	{
		if (!IsFull())
		{
			stackArr[stackPtr] = data;
			stackPtr++;
			return true;
		}
		else
			return false;
	}

	//this function copies the data item on top of stack if it is not empty otherwise returns false
	bool Pop(Type & data)
	{
		if (!IsEmpty())
		{
			stackPtr--;
			data = stackArr[stackPtr];
			return true;
		}
		else
			return false;
	}

	//this function copies the data item on top of stack if it is not empty otherwise returns false
	bool Top(Type & data)
	{
		if(!IsEmpty())
		{
			data = stackArr[stackPtr - 1];
			return true;
		}
		else
			return false;
	}

	//operator overload function for = operator. It makes the right object equal to the left one
	const Stack & operator=(const Stack & source)
	{
		if (this != &source) //condition to check if an object is not being set equal to itself as it is not necessary in that case
		{
			delete[] stackArr;
			maxSize = source.maxSize;
			stackArr = new Type[maxSize];

			stackPtr = source.stackPtr;

			for (int i = 0; i < stackPtr; i++)
				stackArr[i] = source.stackArr[i];
		}

		return *this;
	}

	~Stack() //destructor function
	{
		if(maxSize!=0)
			delete[] stackArr;
	}

};

int main()
{
	//below code is just for testing the stack class
	
	Stack<int> S(20);
	int i, x;

	//push numbers 0-19 onto the stack
	for (i = 0; i < 20; i++)
	{
		S.Push(i);
	}

	Stack<int> X(10);

	X = S; //make object X equal to S

	//pop the items from stack X and display them
	for (i = 0; i < 20; i++)
	{
		X.Pop(x);
		cout << x << " ";
	}

	return 0;
}
