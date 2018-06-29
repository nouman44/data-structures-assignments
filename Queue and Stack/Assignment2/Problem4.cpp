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
		if (!IsEmpty())
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

	//destructor function
	~Stack()
	{
		if(maxSize!=0)
			delete[] stackArr;
	}

};

//this is a helper function t check if the parameter is an operator or not
bool isOperator(char input)
{
	if (input == '+' || input == '-' || input == '*' || input == '/' ||
		input == '%' || input == '<' || input == '>' || input == '&' ||
		input == '|' || input == '=' || input == '!' || input == '~')
		return true;
	else
		return false;
}

//this is a helper function to assign a numerical value to an operand for deciding precedence
int assignOpPrecedence(char op)
{
	int value = 10;

	if (op == '~')
		value = 1;
	else if (op == '!')
		value = 2;
	else if (op == '*' || op == '/' || op == '%')
		value = 3;
	else if (op == '+' || op == '-')
		value = 4;
	else if (op == '<')
		value = 5;
	else if (op == '>')
		value = 6;
	else if (op == '=')
		value = 7;
	else if (op == '&')
		value = 8;
	else if (op == '|')
		value = 9;

	return value;
}

//this function returns an expression which converted to postfix from infix
char* convertToPostfix(char * infix)
{
	int size = strlen(infix), index = 0, op1, op2, i;
	char *temp = new char[size]; //declare an temp array
	char value;
	bool stop = false;
	Stack<char> S(size); //declare stack object

	for (i = 0; i < size; i++) //loop until size of expression
	{
		stop = false;

		if (infix[i] == '(') //check if it a opening bracket
			S.Push(infix[i]);
		else if (isOperator(infix[i])) //check if it is an operator
		{
			while (!stop)
			{
				op1 = assignOpPrecedence(infix[i]); //assign operator precedence to first op
				S.Top(value);
				op2 = assignOpPrecedence(value); //assign operator precedence to second op
				if (S.IsEmpty() || op1 < op2)
				{
					S.Push(infix[i]);
					stop = true;
				}
				else
				{
					S.Pop(value);
					temp[index] = value; //add to the temp array
					index++;
				}
			}
		}
		else if (infix[i] == ')') //check if it is a closing bracket
		{
			S.Top(value);
			while (value != '(')
			{
				S.Pop(value);
				if (value != '(')
				{
					temp[index] = value; //add to the temp array
					index++;
				}
			}
		}
		else //otherwise add it as an operator
		{
			temp[index] = infix[i]; //add to the temp array
			index++;
		}
	}

	while (!S.IsEmpty()) //loop to add the values on stack to the temp array
	{
		S.Pop(value);
		temp[index] = value;
		index++;
	}

	char *postfix = new char[index + 1]; //declare array for returning

	for (i = 0; i < index; i++)
	{
		postfix[i] = temp[i]; //add the temp items to answer array
	}

	postfix[index] = NULL; //null terminate the answer array
	delete[] temp;

	return postfix;
}

int main()
{
	cout << "Enter infix expression to convert: ";
	char infix[50];
	cin >> infix;
	int size = strlen(infix), i;

	char *postfix = convertToPostfix(infix); //function call for converting to postfix
	cout << "The expression in postfix is: " << postfix;

	return 0;
}
