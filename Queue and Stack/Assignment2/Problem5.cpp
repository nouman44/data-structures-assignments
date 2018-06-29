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

	void setMaxSize(int size) //function to reset the max size and declare array accordingly
	{
		maxSize = size;
		delete[] stackArr;
		stackArr = new Type[maxSize];
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

//template class declaration for queue
template <class Type>
class Queue
{
private:
	Stack<Type> S1; //declare stack object 1
	Stack<Type> S2; //declare stack object 1
	int size;
	int maxSize;
public:
	Queue(int userSize = 10) //paramertized constructor
	{
		maxSize = userSize;
		S1.setMaxSize(maxSize);
		S2.setMaxSize(maxSize);
		size = 0;
	}

	Queue(const Queue & source) //copy constructor
	{
		maxSize = source.maxSize;
		size = source.size;

		S1 = source.S1;
		S2 = source.S2;
	}

	bool IsFull() //function to check if queue is full
	{
		return (size == maxSize);
	}

	bool IsEmpty() //function to check if queue is empty
	{
		return (size == 0);
	}

	bool Enqueue(const Type data) //this function adds the data item in the end of queue if it is not fulll otherwise returns false
	{
		Type value = data;
		""

		if (!IsFull())
		{
			while (!S2.IsEmpty()) //push all items of stack 2 to stack 1
			{
				S2.Pop(value);
				S1.Push(value);
			}

			S1.Push(value);
			size++;
		}
		else
			return false;
	}

	bool Dequeue(Type & data) //this function copies the data item from start of queue if it is not empty otherwise returns false
	{
		Type value = data;

		if (!IsEmpty())
		{
			while (!S1.IsEmpty()) //push all items of stack 1 to stack 2
			{
				S1.Pop(value);
				S2.Push(value);
			}

			S2.Pop(value);
			data = value;
			size--;
		}
		else
			return false;
	}

	//operator overload function for = operator. It makes the right object equal to the left one
	const Queue & operator=(const Queue & source)
	{
		if (this != &source) //condition to check if an object is not being set equal to itself as it is not necessary in that case
		{
			maxSize = source.maxSize;
			size = source.size;

			S1 = source.S1;
			S2 = source.S2;
		}

		return *this;
	}

	~Queue() //destructor function
	{
		
	}
};

int main()
{
	//below code is just for testing the queue class
	Queue<int> S(20);
	int i, x;

	for (i = 0; i < 20; i++)
	{
		S.Enqueue(i);
	}

	Queue<int> X(10);

	X = S;

	for (i = 0; i < 10; i++)
	{
		X.Dequeue(x);
		cout << x << " ";
	}

	for (i = 0; i < 10; i++)
	{
		X.Enqueue(i);
	}

	for (i = 0; i < 20; i++)
	{
		X.Dequeue(x);
		cout << x << " ";
	}

	return 0;
}
