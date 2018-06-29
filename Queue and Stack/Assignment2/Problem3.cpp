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
 
	bool IsEmpty()  //function to check if queue is empty
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

//this function returns the last customer served in a queue when n interchanges happen
int computeLastCustomer(int m, int n)
{
	CircularQueue<int> bankQueue(m); //declare queue object
	int i, j, num, size = m;

	//in this case numbers 1 to m are assgined to the queue indexes
	//so the number last served returned will be that accordingly
	for (i = 1; i <= m; i++)
	{
		bankQueue.Enqueue(i); 
	}

	for (i = 0; !bankQueue.IsEmpty(); i++) //loop until queue is empty
	{
		for (j = 0; j < n; j++) //ask customer at head to go back and repeat this n times
		{
			bankQueue.Dequeue(num); //dequeue item and assign it to num
			bankQueue.Enqueue(num); //enqueue num to the queue
		}
		bankQueue.Dequeue(num); //serve the cusomter at head
		size--;
	}

	return num; //return the number of customer last served. can be from 1 to m
}

int main()
{
	int m, n;

	cout << "Enter number of customers in queue: ";
	cin >> m;

	cout << "Enter the value for n: ";
	cin >> n;


	cout << "The cutomer to be served last is number " << computeLastCustomer(m, n);

	return 0;
}
