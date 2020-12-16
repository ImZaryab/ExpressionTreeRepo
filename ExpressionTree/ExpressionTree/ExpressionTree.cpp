/*
* @author Zaryab Husain Ghori(190899)
* @date 16-12-20
* @Lab Assignment # 2
*/

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

class TreeNode
{
public:
	char value;
	TreeNode* leftChild;
	TreeNode* rightChild;
	TreeNode* next;

	TreeNode()
	{
		leftChild = NULL;
		rightChild = NULL;
		next = NULL;
	}
};

class BinaryTree
{
	TreeNode* root;

public:
	void setRoot(TreeNode* node)
	{
		root = node;
	}

	TreeNode* getRoot()
	{
		return root;
	}

};

class NodeStack
{
	TreeNode* Top = NULL;

public:
	void PushNode(char data);
	void OprNode(char data);
	TreeNode* PopNode();
	TreeNode* getTop()
	{
		return Top;
	}
};

void NodeStack::PushNode(char data)
{
	TreeNode* newptr;
	newptr = new TreeNode;

	newptr->value = data;
	newptr->next = Top;

	Top = newptr;
}

TreeNode* NodeStack::PopNode()
{
	TreeNode* temp = Top;
	Top = Top->next;

	return temp;
}

void NodeStack::OprNode(char data)
{
	TreeNode* newptr;
	newptr = new TreeNode;

	newptr->value = data;
	newptr->rightChild = PopNode();
	newptr->leftChild = PopNode();
	newptr->next = Top;
	Top = newptr;
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
	else if ((a == '+' && b == '(') || (a == '-' && b == '(') || (a == '*' && b == '(') || (a == '/' && b == '(') || (a == ')' && b == '('))
		return false;
	else if ((a == '(' && b == '+') || (a == '(' && b == '-') || (a == '(' && b == '*') || (a == '(' && b == '/') || (a == '(' && b == '(') || (a == ')' && b == ')'))
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

///////////////////////////////////////////////////////////////////////
//----------------GENERATE EXPRESSION TREE FUNCTION-----------------//
/////////////////////////////////////////////////////////////////////

BinaryTree generateExpressionTree(string exp)
{
	int i = 0;
	char symb;
	NodeStack nodestck;

	while (exp[i])
	{
		symb = exp[i];

		if (symb != '+' && symb != '-' && symb != '*' && symb != '/' && symb != '(' && symb != ')')
		{
			nodestck.PushNode(exp[i]);
		}
		if (symb == '+' || symb == '-' || symb == '*' || symb == '/')
		{
			nodestck.OprNode(exp[i]);
		}
		i++;
	}

	TreeNode* exptree = nodestck.getTop();
	BinaryTree BinaryExpressionTree;
	BinaryExpressionTree.setRoot(exptree);

	return BinaryExpressionTree;
}

///////////////////////////////////////////////////////////////////////
//-----------------CHAR TO INT CONVERSION FUNCTION------------------//
/////////////////////////////////////////////////////////////////////

int convertToInt(char c)
{
	int num = int(c) - '0';
	
	return num;
}

///////////////////////////////////////////////////////////////////////
//----------------EVALUATE EXPRESSION TREE FUNCTION-----------------//
/////////////////////////////////////////////////////////////////////

int EvaluateExpTree(TreeNode* root)
{
	TreeNode* currNode = root;

	if (!currNode)
	{
		cout << "Empty Tree!" << endl;
		return NULL;
	}

	if (currNode->leftChild == NULL && currNode->rightChild == NULL)
	{
		return convertToInt(currNode->value);
	}

	int leftValue = EvaluateExpTree(currNode->leftChild);

	int rightValue = EvaluateExpTree(currNode->rightChild);

	if (currNode->value == '+')
	{
		return leftValue + rightValue;
	}
	else if (currNode->value == '-')
	{
		return leftValue - rightValue;
	}
	else if (currNode->value == '*')
	{
		return leftValue * rightValue;
	}
	else if (currNode->value == '/')
	{
		return leftValue / rightValue;
	}
}

///////////////////////////////////////////////////////////////////////
//----------------------------MAIN BODY-----------------------------//
/////////////////////////////////////////////////////////////////////

void main()
{
	string exp;

	cout << "Enter Expression without spaces: ";
	cin >> exp;

	cout << "Given Expression: " << exp << endl << endl;

	string postExp = infixTopostfix(exp);
	cout << endl;

	cout << "-Conversion To Infix Completed-" << endl << endl;

	cout << "Converted Expression: " << postExp << endl << endl;

	cout << "Creating Expression Tree..." << endl << endl;

	BinaryTree ExpressionTree = generateExpressionTree(postExp);

	cout << "-Exprssion Tree Created Successfully-" << endl << endl;

	cout << "Evaluating Expression Tree..." << endl << endl;

	int result_of_expTree = EvaluateExpTree(ExpressionTree.getRoot());

	cout << "Result of Expression Tree: " << result_of_expTree << endl << endl;

	system("pause");
}