#include <iostream>
#include <vector>
using namespace std;

class node
{
public:
	char data;
	node* next;
};


class Stack
{
	node* top = NULL;

public:
	void Push(char newelement);
	char Pop();
	bool IsEmpty();
	void PopDiscard();
	char Top();

};

bool Stack::IsEmpty()
{
	if (top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Stack::Push(char newelement)
{
	node* newptr;
	newptr = new node;

	newptr->data = newelement;
	newptr->next = top;

	top = newptr;
}

char Stack::Pop()
{
	char returnValue;

	node* tempptr = top;
	returnValue = top->data;
	top = top->next;
	delete tempptr;

	return returnValue;
}

void Stack::PopDiscard()
{
	node* temp = top;
	top = top->next;
	delete temp;
}

char Stack::Top()
{
	if (top)
	{
		return top->data;
	}
	else
	{
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////
//------------------OPERATOR PRECEDENCE FUNCTION--------------------//
/////////////////////////////////////////////////////////////////////

bool prcd(char a, char b)
{
	if ((a == '*' && b == '+') || (a == '*' && b == '-') || (a == '/' && b == '+') || (a == '/' && b == '-') || (a == '-' && b == '+') || (a == '/' && b == '*'))
		return true;
	else if ((a == '+' && b == '*') || (a == '+' && b == '/') || (a == '-' && b == '*') || (a == '-' && b == '/') || (a == '+' && b == '-') || (a == '*' && b == '/'))
		return false;
	else if ((a == '+' && b == '+') || (a == '-' && b == '-') || (a == '*' && b == '*') || (a == '/' && b == '/'))
		return true;
	else if ((a == '+' && b == ')') || (a == '-' && b == ')') || (a == '*' && b == ')') || (a == '/' && b == ')'))
		return true;
	else if ((a == '+' && b == '(') || (a == '-' && b == '(') || (a == '*' && b == '(') || (a == '/' && b == '('))
		return false;
	else if ((a == '(' && b == '+') || (a == '(' && b == '-') || (a == '(' && b == '*') || (a == '(' && b == '/'))
		return false;
	else if ((a == '(' && b == ')'))
		return false;
}

///////////////////////////////////////////////////////////////////////
//--------------------INFIX TO POSTFIX FUNCTION---------------------//
/////////////////////////////////////////////////////////////////////

string infixTopostfix(string expression)
{
	Stack optstck;
	char symb;
	vector<char> postString;

	int counter = 0;

	int i = 0;
	while (expression[i])
	{
		symb = expression[i];

		if (symb != '+' && symb != '-' && symb != '*' && symb != '/' && symb != '(' && symb != ')')
		{
			postString.push_back(symb);
			cout << "Operand added..." << endl;
			counter++;
		}
		else
		{
			while (!optstck.IsEmpty() && prcd(optstck.Top(), symb))
			{
				char topsymb = optstck.Pop();
				cout << "Operator Popped due to Precedence..." << endl;
				postString.push_back(topsymb);
			}
			if (optstck.IsEmpty() || symb != ')')
			{
				cout << "Operator Pushed to Stack..." << endl;
				optstck.Push(symb);
				counter++;
			}
			else
			{
				optstck.PopDiscard();
				counter--;
			}
		}

		i++;
	}

	//output remaining operators
	while (!optstck.IsEmpty())
	{
		char topsymb = optstck.Pop();
		postString.push_back(topsymb);
	}

	//Shift array to string for Return
	string postfixExp;
	
	for(int i = 0; i < counter; i++)
	{
		postfixExp = postfixExp + postString[i];
	}

	return postfixExp;
}

void main()
{
	string exp = "(5+3)*4";

	cout << exp << endl << endl;

	string postExp = infixTopostfix(exp);
	cout << endl;

	cout << postExp << endl << endl;



	system("pause");
}