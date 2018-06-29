#include <iostream>
#include <fstream>
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

//this class is for term object of a polynomial
class Term
{
	int coefficient, exponent;

public:
	Term()  //constructor
	{
		coefficient = 0;
		exponent = 0;
	}

	~Term() //destructor
	{

	}

	//function tO update the numerator and denominator
	void updateTerm(int coeff, int exp)
	{
		exponent = exp;
		coefficient = coeff;
	}

	//operator overload for > sign to check if value is greater
	bool operator>(const Term & operand) const
	{
		if (exponent <= operand.exponent)
			return false;
		else
			return true;
	}

	//operator overload for < sign to check if value is less
	bool operator<(const Term & operand) const
	{
		if (exponent >= operand.exponent)
			return false;
		else
			return true;
	}

	//operator overload for = sign to make one term equal to the other
	const Term & operator=(const Term & source)
	{
		if (this != &source)
		{
			exponent = source.exponent;
			coefficient = source.coefficient;
		}

		return *this;
	}

	//operator overload for + operator to add two Terms
	Term operator+(const Term & operand) const
	{
		Term result;

		result.coefficient = coefficient + operand.coefficient;
		result.exponent = exponent;

		return result;
	}

	//operator overload for == sign to check if two terms have same exponent
	bool operator==(const Term & operand) const
	{
		if (exponent == operand.exponent)
			return true;
		else
			return false;
	}

	//operator overload for == sign to check if two terms do not have same exponent
	bool operator!=(const Term & operand) const
	{
		if (exponent == operand.exponent)
			return false;
		else
			return true;
	}

	//operator overload for output stream to print a term
	friend ostream & operator<<(ostream &strm, const Term & t)
	{
		if (t.coefficient >= 0)
			strm << '+';

		strm << t.coefficient;

		if (t.exponent >= 1)
			strm << 'x';
		if (t.exponent > 1)
			strm << '^' << t.exponent;

		return strm;
	}
};

//this is helper function used in InputPolynomial function of Polynomial class
//it converts char input to an integer
int convertToInt(char input)
{
	if (input == '0')
		return 0;
	else if (input == '1')
		return 1;
	else if (input == '2')
		return 2;
	else if (input == '3')
		return 3;
	else if (input == '4')
		return 4;
	else if (input == '5')
		return 5;
	else if (input == '6')
		return 6;
	else if (input == '7')
		return 7;
	else if (input == '8')
		return 8;
	else if (input == '9')
		return 9;

	return 0;
}

//this class is for a whole polynomial
class Polynomial
{
	List<Term> poly; //link list of terms for the polynomial

public:
	Polynomial() //constructor
	{
		
	}

	~Polynomial() //destructor
	{

	}
	
	//this function read a polynomial from an input file
	void InputPolynomial(char * filename)
	{
		ifstream inputStream(filename); //declare stream object

		char input;
		int multiplier = 10, coeff, exp, sign = 1;
		bool wasExp;

		Term temp;

		while (!inputStream.eof()) //continue while not end of file
		{
			coeff = 0, exp = 0, multiplier = 10, wasExp = false;

			inputStream >> input; //read a char from file

			while ((input != '+' && input != '-') && !inputStream.eof()) //continue if sign not reached or end of file
			{
				if (input >= 48 && input <= 57 && !wasExp) //condition to read coefficient
					coeff = (coeff*multiplier) + convertToInt(input);
				else if (input == 'x') //increment exponenet if x read
					exp++;
				else if (input == '^') //exponent starts if ^ is read
				{
					wasExp = true;
					exp = 0;
				}
				else if (input >= 48 && input <= 57 && wasExp) //condition to read exponent
					exp = (exp*multiplier) + convertToInt(input);

				inputStream >> input;
			}

			if (coeff != 0) //if coefficient not zero then insert in list
			{
				coeff = coeff * sign;
				temp.updateTerm(coeff, exp);
				poly.insertSorted(temp);
			}

			if (input == '+') //change sign to +
				sign = 1;
			else if (input == '-') //change sign to -
				sign = -1;
		}
	}

	//this function outputs a polynomial on screen
	void OutputPolynomial()
	{
		ListItem<Term> *curr = poly.getHead();

		while (curr != nullptr)
		{
			cout << curr->value;
			curr = curr->next;
		}
	}

	//this is an operator overload which adds two polynomials and then returns the result
	Polynomial operator+(Polynomial & P)
	{
		Polynomial result(*this); //copy first polynomial into result

		ListItem<Term> *curr = P.poly.getHead(), *search;

		while (curr != nullptr) //go through the whole second polynomial
		{
			search = result.poly.searchFor(curr->value); //if same degree term exists then search is not null

			if (search != nullptr)
				search->value = search->value + curr->value; //add the same degree terms
			else
				result.poly.insertSorted(curr->value); //insert new degree term to list

			curr = curr->next;
		}
		
		return result; //return the result
	}

	//operator overload for = sign to make one polynomial to another
	//used to store result of addition in this program
	const Polynomial & operator=(Polynomial & source)
	{
		if (this != &source)
		{
			ListItem<Term> *curr = poly.getHead(); //store head ponter
			ListItem<Term> *t1 = nullptr, *t2 = nullptr;
	
			while (curr != nullptr) //loop to delete all the existing terms of polynomial
			{
				poly.deleteHead();
				curr = poly.getHead();
			}

			curr = source.poly.getHead();

			while (curr != nullptr) //insert the terms of source into existing polynomial
			{
				poly.insertSorted(curr->value);
				curr = curr->next;
			}
		}

		return *this;
	}

};

int main()
{
	Polynomial x, y;

	char *file1 = "polynomial1.txt";
	char *file2 = "polynomial2.txt";

	x.InputPolynomial(file1); //read polynomial x
	y.InputPolynomial(file2); //read polynomial y

	cout << "Polynomial x: ";
	x.OutputPolynomial(); //output polynomial x
	cout << endl << endl;
	cout << "Polynomial y: ";
	y.OutputPolynomial(); //output polynomail y
	cout << endl << endl;

	x = x + y; //add x and y and store it in x

	cout << "Result of x+y (stored in x): ";
	x.OutputPolynomial(); //output the result of x + y

	cout << endl << endl;
	system("pause");
	return 0;
}