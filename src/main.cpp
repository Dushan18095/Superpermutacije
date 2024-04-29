#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findWeigth(vector<int> node1, vector<int> node2) // Funkcija za izracunavanje tezine veze izmedju argumenta node1 i node2
{
	unsigned int weigth = 0;
	for (unsigned int i = 1; i < node1.size(); i++)
	{
		weigth = node1.size();
		for (unsigned int j = i; j < node1.size(); j++)
		{
			if (node1[j] == node2[j - i])
			{
				weigth--;
			}
			else
			{
				weigth = node1.size();
				break;
			}
		}
		if (weigth != node1.size())
			return weigth;
	}

	return weigth;
}

vector<vector<int>> connectGraph(vector<vector<int>> nodes)
{
	int numOfNodes = nodes.size();
	vector<vector<int>> graph(numOfNodes);

	for (int i = 0; i < numOfNodes; i++)
	{
		vector<int> currNode = nodes[i];
		vector<int> edges(numOfNodes);
	}

	return graph;
}

int main()
{
	unsigned int numberOfElements = 4;

	vector<int> perm;

	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		perm.push_back(i);
	}

	vector<vector<int>> permutacije;

	do
	{
		permutacije.push_back(perm);
	} while (next_permutation(perm.begin(), perm.end()));

	for (unsigned int i = 0; i < permutacije.size(); i++)
	{
		for (unsigned int j = 0; j < numberOfElements; j++)
		{
			cout << permutacije[i][j];
		}
		cout << endl;
	}

	return 0;
}
