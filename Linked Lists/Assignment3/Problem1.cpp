#include <iostream>
using namespace std;

/* This class just holds a single data item. */
template <class T>
struct ListItem
{
	T value;
	ListItem<T> *next;
};

/* This is the generic List class */
template <class T>
class List
{
	ListItem<T> *head;

public:

	// Constructor
	List()
	{
		head = nullptr;
	}

	// Copy Constructor
	List(const List<T>& otherList)
	{
		ListItem<T> *curr = otherList.head;
		ListItem<T> *t1 = nullptr, *t2 = nullptr;
		head = nullptr;

		if (curr != nullptr)
		{
			t1 = new ListItem<T>;
			t1->value = curr->value;
			head = t1;
			curr = curr->next;
		}

		while (curr != nullptr)
		{
			t2 = new ListItem<T>;
			t2->value = curr->value;
			curr = curr->next;
			t1->next = t2;
			t1 = t2;
		}

		t1->next = nullptr;
	}

	// Destructor
	~List()
	{
		ListItem<T> *t1, *t2;
		t1 = head;

		while (t1 != nullptr)
		{
			t2 = t1->next;
			delete t1;
			t1 = t2;
		}
	}

	// Insert at head of the link list
	void insertAtHead(T item)
	{
		ListItem<T> *temp = new ListItem<T>;
		temp->value = item;
		temp->next = nullptr;

		if (head != nullptr)
		{
			temp->next = head;
			head = temp;
		}
		else
			head = temp;
	}

	//function to insert at end of link list
	void insertAtTail(T item)
	{
		ListItem<T> *temp = new ListItem<T>;
		temp->value = item;
		temp->next = nullptr;

		if (head != nullptr)
		{
			ListItem<T> *curr = head;

			while (curr->next != nullptr)
				curr = curr->next;

			curr->next = temp;
		}
		else
			head = temp;
	}

	//function to insert in order in a link list by descending order
	void insertSorted(T item)
	{
		ListItem<T> *temp = new ListItem<T>;
		temp->value = item;
		ListItem<T> *curr = head, *prev = nullptr;

		while (curr != nullptr && curr->value > item)
		{
			prev = curr;
			curr = curr->next;
		}

		temp->next = curr;

		if (curr == head)
			head = temp;
		else
			prev->next = temp;
	}

	// Lookup Funtction to return the head pointer of list
	ListItem<T> *getHead()
	{
		return head;
	}

	// Lookup Funtction to return the tail(end) pointer of list
	ListItem<T> *getTail()
	{
		if (head != nullptr)
		{
			ListItem<T> *curr = head;

			while (curr->next != nullptr)
				curr = curr->next;

			return curr;
		}
		else
			return nullptr;
	}

	//Lookup Funtction to return the pointer of a specific object
	ListItem<T> *searchFor(T item)
	{
		ListItem<T> *curr = head;

		while (curr != nullptr)
		{
			if (curr->value == item)
				return curr;

			curr = curr->next;
		}

		return curr;
	}

	// function to delete a specific item from list
	void deleteElement(T item)
	{
		ListItem<T> *curr = head, *prev = nullptr;

		while (curr != nullptr && curr->value != item)
		{
			prev = curr;
			curr = curr->next;
		}

		if (curr != nullptr && curr->value == item)
		{
			if (curr == head)
				head = head->next;
			else
				prev->next = curr->next;

			delete curr;
		}
	}

	// function to delete head item of a list
	void deleteHead()
	{
		if (head != nullptr)
		{
			ListItem<T> *temp = head->next;
			delete head;
			head = temp;
		}
	}

	// function to delete tail item of a list
	void deleteTail()
	{
		if (head != nullptr)
		{
			ListItem<T> *curr = head, *prev = nullptr;
			while (curr->next != nullptr)
			{
				prev = curr;
				curr = curr->next;
			}

			if (curr == head)
				head = nullptr;
			else
				prev->next = nullptr;

			delete curr;
		}
	}

	// Utility Function to return length of list
	int length()
	{
		int len = 0;
		ListItem<T> *curr = head;

		while (curr != nullptr)
		{
			curr = curr->next;
			len++;
		}

		return len;
	}

	// Utility Function to print all items of list
	void Print()
	{
		ListItem<T> *curr = head;

		while (curr != nullptr)
		{
			cout << curr->value << " ";
			curr = curr->next;
		}
	}
};

int main()
{
	//the following code is just for the testing of the list class
	List<int> L;

	L.insertAtHead(41);
	L.insertAtTail(60);

	for (int i = 0;i < 10;i++)
	{
		L.insertSorted(i);
	}

	List<int> X(L);

	X.Print();
	L.deleteHead();
	L.deleteTail();
	cout << endl;
	L.Print();
	L.deleteElement(6);
	cout << endl;
	L.Print();
	cout << endl;
	X.Print();
	X.insertAtHead(4);
	L.insertAtTail(55);
	cout << endl;
	L.Print();
	cout << endl;
	X.Print();
	cout << endl;
	cout << X.length();

	return 0;
}