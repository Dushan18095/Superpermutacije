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

	return 3;
}

vector<vector<int>> connectGraph(vector<vector<int>> nodes) // Prosledjuju se cvorovi sa vrednostima permutacija i vraca se matrica povezanosti svih cvorova
{
	int numOfNodes = nodes.size();
	vector<vector<int>> graph;

	for (int i = 0; i < numOfNodes; i++)
	{
		vector<int> edges;
		for (int j = 0; j < numOfNodes; j++)
		{
			edges.push_back(findWeigth(nodes[i], nodes[j]));
		}
		graph.push_back(edges);
	}

	return graph;
}

void printAdjMatrix(vector<vector<int>> graph) // Funkcija koja stampa matricu povezanosti
{
	int n = graph.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

void printPermutations(vector<vector<int>> permutations) // Stampa sve elemenente vektora vektora
{
	for (unsigned int i = 0; i < permutations.size(); i++)
	{
		for (unsigned int j = 0; j < permutations[0].size(); j++)
		{
			cout << permutations[i][j];
		}
		cout << endl;
	}
}

int factorial(int n) // Vraca faktorijel broja
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main()
{
	unsigned int numberOfElements = 4; // Broj elemenata skupa

	vector<int> perm; // Osnovna permutacija ili skup elemenata

	for (unsigned int i = 0; i < numberOfElements; i++) // Ubacivanje elemenata od 0 do n-1
	{
		perm.push_back(i);
	}

	vector<vector<int>> permutations; // sve permutacije skupa perm

	do
	{
		permutations.push_back(perm);
	} while (next_permutation(perm.begin(), perm.end())); // Ubacivanje permtacija u vektor vektora permutations

	printPermutations(permutations); // Stampanje svih permtutacija

	vector<vector<int>> graph(connectGraph(permutations)); // Pravljenje matrice povezanosti grafa
	printAdjMatrix(graph);								   // Stampanje matrice povezanosti

	return 0;
}
