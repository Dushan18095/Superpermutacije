#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int findWeigth(vector<int> node1, vector<int> node2) // Funkcija za izracunavanje tezine veze izmedju argumenta node1 i node2
{
	unsigned int weigth = 0;
	for (unsigned int i = 0; i < node1.size(); i++)
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

	return node1.size();
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
			cout << char(permutations[i][j]+65);
		}
		cout << endl;
	}
}

int factorial(int n) // Vraca faktorijel broja
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

vector<int> tspBruteForce(vector<vector<int>> graph)
{
    int n = graph.size();
    vector<int> vertex;
    vector<int> path;
    for (int i = 1; i < n; i++)
        vertex.push_back(i);
    int min_cost = INT_MAX;
    while(next_permutation(vertex.begin(), vertex.end()))
     {
        int current_cost = 0;
        int j = 0;
        for (int i = 0; i < vertex.size(); i++) {
            current_cost += graph[j][vertex[i]];
            j = vertex[i];
        }
        current_cost += graph[j][0];
        if (current_cost < min_cost)
        {
            min_cost = min(min_cost, current_cost);
            path = vertex;
        }
	}
	path.insert(path.begin(), 0);
    return path;
}

vector<int> mergePerms(vector<int> perm1, vector<int> perm2)
{
    vector<int> result;
    set_union(perm1.begin(),perm1.end(), perm2.begin(),perm2.end(), back_inserter(result));
    return result;
}

int main()
{
	unsigned int numberOfElements = 3; // Broj elemenata skupa

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
	for(int i = 0; i < graph.size(); i++)
	{
		graph[i][0] = 0;
	}
	printAdjMatrix(graph); // Stampanje matrice povezanosti

    vector<int> pathIndex = tspBruteForce(graph);
    cout << "Shortest path by index:" << endl;
    for(int i = 0; i < pathIndex.size(); i++)
    {
        cout << pathIndex[i] << endl;
    }
    vector<int> m = mergePerms(permutations[0], permutations[3]);
    vector<int> superpermIndex;
    for (unsigned int i = 0; i < pathIndex.size(); i++)
    {
        superpermIndex = mergePerms(superpermIndex, permutations[pathIndex[i]);
    }

	return 0;
}
