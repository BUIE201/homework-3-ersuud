#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;

	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

vector<int> b;

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}



void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}



int Find_Largest_Sum(Node* pRoot)
{
	if (!pRoot)
		return 0;

	int Left = Find_Largest_Sum(pRoot->pLeft);
	int Right = Find_Largest_Sum(pRoot->pRight);

	if (Left > Right)
		return Left + pRoot->i;
	else
		return Right + pRoot->i;
}

bool Find_Largest_Path(Node* pRoot, int branchsum)
{
	if (branchsum == 0)
		return true;

	if (!pRoot)
		return false;

	bool Left  = Find_Largest_Path(pRoot->pLeft, branchsum - pRoot->i);
	bool Right = Find_Largest_Path(pRoot->pRight, branchsum - pRoot->i);

	if (Left || Right)
		b.push_back(pRoot->i);
	if (Left)
		return Left;
	if (Right)
		return Right;
}

void main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}
	PrintTree(pRoot, 1);
	int largest_sum = Find_Largest_Sum(pRoot);
	cout << "Largest sum is: " << largest_sum << endl;
	cout << "Branch with the largest sum is: ";
	Find_Largest_Path(pRoot, largest_sum);
	reverse(b.begin(), b.end());
	for (int i = 0; i < b.size(); i++)
		cout << b[i] << " ";
}