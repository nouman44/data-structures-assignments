#include <iostream>
using namespace std;

//template class declaration for queue
template <class Type>
class CircularQueue
{
private:
	Type *queueArr; //array for queue
	int front;
	int end;
	int size;
	int maxSize;
public:
	CircularQueue(int userSize = 10) //paramertized constructor
	{
		maxSize = userSize;
		queueArr = new Type[maxSize];
		front = 0;
		end = -1;
		size = 0;
	}

	CircularQueue(const CircularQueue & source) //copy constructor
	{
		front = source.front;
		end = source.end;
		maxSize = source.maxSize;
		size = source.size;

		for (i = front; i < front+size; i++)
			queueArr[i] = source.queueArr[i];
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
		if (!IsFull())
		{
			end++;
			if (end == maxSize)
				end = 0;
			queueArr[end] = data;
			size++;
			return true;
		}
		else
			return false;
	}

	bool Dequeue(Type & data) //this function copies the data item from start of queue if it is not empty otherwise returns false
	{
		if (!IsEmpty())
		{
			data = queueArr[front];
			front++;
			if (front == maxSize)
				front = 0;
			size--;
			return true;
		}
		else
			return false;
	}

	//operator overload function for = operator. It makes the right object equal to the left one
	const CircularQueue & operator=(const CircularQueue & source)
	{
		if (this != &source) //condition to check if an object is not being set equal to itself as it is not necessary in that case
		{
			delete[] queueArr;
			maxSize = source.maxSize;
			queueArr = new Type[maxSize];
			front = source.front;
			end = source.end;
			size = source.size;

			for (int i = front; i < front + size; i++)
				queueArr[i] = source.queueArr[i];
		}

		return *this;
	}

	~CircularQueue() //destructor function
	{
		delete[] queueArr;
	}
};

int main()
{
	//below code is just for testing the circular queue class
	CircularQueue<int> S(20);
	int i, x;

	//add 0-19 numb to the queue
	for (i = 0; i < 20; i++)
	{
		S.Enqueue(i);
	}

	CircularQueue<int> X(10);

	X = S; //make queue X eqaul to S

	//dequeue 0-9 from queue
	for (i = 0; i < 10; i++)
	{
		X.Dequeue(x);
		cout << x << " ";
	}

	//add 0-9 to the queue
	for (i = 0; i < 10; i++)
	{
		X.Enqueue(i);
	}

	//print items of the q
	for (i = 0; i < 20; i++)
	{
		X.Dequeue(x);
		cout << x << " ";
	}

	return 0;
}
