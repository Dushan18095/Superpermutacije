#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

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
	for (unsigned int i = 0; i < graph.size(); i++)
	{
		graph[i][0] = 0;
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
			cout << char(permutations[i][j] + 65);
		}
		cout << endl;
	}
}

int factorial(int n) // Vraca faktorijel broja
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

vector<int> nearestNeighbor(const vector<vector<int>> graph) // Aproksimativni algoritam za resavanje TSP
{
	int n = graph.size();
	vector<int> path;
	vector<bool> visited(n, false);

	path.push_back(0);
	visited[0] = true;
	int currentCity = 0;

	for (int i = 1; i < n; ++i)
	{
		int minDist = INT_MAX;
		int nextCity = -1;

		for (int j = 0; j < n; ++j)
		{
			if (!visited[j] && graph[currentCity][j] < minDist)
			{
				minDist = graph[currentCity][j];
				nextCity = j;
			}
		}

		path.push_back(nextCity);
		visited[nextCity] = true;
		currentCity = nextCity;
	}

	return path;
}

vector<int> mergePerms(vector<int> perm1, vector<int> perm2) // Funkcija za spajanje dva niza sa uklanjanjem prekpalanja
{
	if (perm1.size() == 0)
		return perm2;
	if (perm2.size() == 0)
		return perm1;
	vector<int> result = perm1;

	unsigned int n;
	for (unsigned int i = 0; i < perm2.size(); i++)
	{
		n = 0;
		for (unsigned int j = 0; j < perm2.size() - i; j++)
		{
			if (perm1[perm1.size() - perm2.size() + i + j] == perm2[j])
			{
				n++;
			}
		}
		if (n == perm2.size() - i)
		{
			vector<int>::iterator it = perm2.begin();
			advance(it, n);
			result.insert(result.end(), it, perm2.end());
			return result;
		}
	}
	return result;
}

vector<int> tspDynamicProgramming(vector<vector<int>> graph) // Egzaktni algoritam za resavanje TSP
{
	int n = graph.size();
	vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX)); // DP tabela
	vector<vector<int>> parent(1 << n, vector<int>(n, -1));	 // Tabela roditelja
	dp[1][0] = 0;											 // Početni čvor

	for (int mask = 1; mask < (1 << n); mask++)
	{
		for (int u = 0; u < n; u++)
		{
			if (mask & (1 << u))
			{ // Provera da li je čvor u skupu mask
				for (int v = 0; v < n; v++)
				{
					if (!(mask & (1 << v)))
					{ // Provera da li je čvor v van skupa mask
						if (dp[mask | (1 << v)][v] > dp[mask][u] + graph[u][v])
						{
							dp[mask | (1 << v)][v] = dp[mask][u] + graph[u][v];
							parent[mask | (1 << v)][v] = u; // Pamćenje roditelja
						}
					}
				}
			}
		}
	}

	// Pronalaženje optimalne putanje
	int min_cost = INT_MAX;
	int last_node = -1;
	for (int i = 0; i < n; i++)
	{
		if (min_cost > dp[(1 << n) - 1][i])
		{
			min_cost = dp[(1 << n) - 1][i];
			last_node = i;
		}
	}

	// Rekonstrukcija putanje
	vector<int> path;
	int mask = (1 << n) - 1;
	while (last_node != -1)
	{
		path.push_back(last_node);
		int new_last_node = parent[mask][last_node];
		mask ^= (1 << last_node); // Brisanje poslednjeg čvora iz skupa mask
		last_node = new_last_node;
	}
	reverse(path.begin(), path.end()); // Rezultat se mora invertovati jer smo radili unazad

	return path;
}

int main()
{
	unsigned int numberOfElements = 4; // Broj elemenata skupa

	vector<int> perm; // Osnovna permutacija ili skup elemenata

	for (unsigned int i = 0; i < numberOfElements; i++) // Ubacivanje elemenata od 0 do n-1
	{
		perm.push_back(i);
	}

	vector<vector<int>> permutations; // sve permutacije vektora perm

	do
	{
		permutations.push_back(perm);
	} while (next_permutation(perm.begin(), perm.end())); // Ubacivanje permtacija u vektor vektora permutations

	printPermutations(permutations); // Stampanje svih permtutacija

	vector<vector<int>> graph(connectGraph(permutations)); // Pravljenje matrice povezanosti grafa
	
	//printAdjMatrix(graph); // Stampanje matrice povezanosti

	vector<int> pathIndex = nearestNeighbor(graph); // Koristi nearestNeighbor umesto tspBruteForce
	cout << "Shortest path by index:" << endl;
	for (unsigned int i = 0; i < pathIndex.size(); i++)
	{
		cout << pathIndex[i] << endl;
	}

	vector<int> superpermIndex;
	for (unsigned int i = 0; i < pathIndex.size(); i++)
	{
		superpermIndex = mergePerms(superpermIndex, permutations[pathIndex[i]]);
	}
	for (int num : superpermIndex)
	{
		cout << num+1;
	}
	return 0;
}
