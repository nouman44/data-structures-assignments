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

//rational class to store the fraction as an object
class rational
{
	float numerator, denominator;

public:
	rational() //constructor
	{
		numerator = 0;
		denominator = 1;
	}

	//function to update the values of numerator and denominator
	void updateFraction(float num, float denom) 
	{
		numerator = num;
		denominator = denom;
	}

	//getter function to get the current values of numerator and denominator
	void getFraction(float & num, float & denom)
	{
		num = numerator;
		denom = denominator;
	}
	
	~rational() //destructor
	{
		
	}
};

//this function prints the n levels of farey fractions
void printFareyFractions(int n)
{
	List<rational> L; //declare link list for rationals
	rational frac; //declare rational object
	float a, b, c, d;
	ListItem<rational> *head, *tail, *curr, *temp, *prev; //pointers for insertion and reference nodes
	int i;

	if (n > 0)
	{
		L.insertAtHead(frac); //insert 0/1 at head of list
		frac.updateFraction(1, 1);
		L.insertAtTail(frac); //insert 1/1 at end of list

		head = L.getHead(); //store head ptr
		tail = L.getTail(); //store tail ptr

		for (i = 1;i <= n;i++) //iterate through for n levels starting at 1
		{
			curr = head; //assign curr value of head ptr

			while (curr != tail) //loop through the whole list
			{
				prev = curr;
				curr = curr->next; 
				prev->value.getFraction(a, c); //update values of a/c fraction
				curr->value.getFraction(b,d); //update values of b/d fraction

				if ((c + d) <= i) //if it fulfills condition then insert new fraction between the two nodes
				{
					temp = new ListItem<rational>;
					temp->value.updateFraction(a + b, c + d);
					prev->next = temp;
					temp->next = curr;
				}
			}

			curr = head; //reassgin curr the value of head ptr

			cout << "LEVEL " << i << ":" << endl;
			while (curr != nullptr) //loop through whole list to print the fraction level
			{
				curr->value.getFraction(a, b);
				cout << a << '/' << b << " , ";
				curr = curr->next;
			}

			cout << endl << endl;
		}
	}
	else
		cout << "Please pass a value greater than 0!";
}

int main()
{
	int n;
	cout << "Enter number of levels of Farey Fractions to print : ";
	cin >> n;
	cout << endl;

	printFareyFractions(n);

	return 0;
}