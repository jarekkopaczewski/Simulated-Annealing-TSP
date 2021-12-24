#include "SimAnnealing.h"
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

vector<vector<int>> SimAnnealing::matrix;
int SimAnnealing::size;

SimAnnealing::SimAnnealing()
{
}

SimAnnealing::~SimAnnealing()
{
}

int SimAnnealing::findSolution(Graph* graph, int type, int coolingType)
{	
	srand((unsigned)time(NULL));
	matrix = graph->getVector();
	size = graph->getSize();
	vector<int> temp(size, -1);
	vector<int> permutation = temp;
	vector <int> tempPermutation(size, -1);
	static std::default_random_engine e;
	static std::uniform_real_distribution<> dis(0, 1);

	for (int i = 0; i < size; i++)
		permutation[i] = i;

	random_shuffle(permutation.begin(), permutation.end());
	int distance = getTourLength(permutation);

	double coolingRate = 0.9999;
	double temperature = 30 * size;
	int deltaDistance = 0;
	double absoluteTemperature = 0.01; 
	double K = 50;
	double P = 0.0;
	double a = 1.0, b = 0.000005;

	vector <int> tempMinPermutation(size, -1);
	int tempMin = INT_MAX;

	while(temperature > absoluteTemperature)
	{
		int era = 0;
		tempMinPermutation = permutation;

		while(era < K)
		{
			tempPermutation = tempMinPermutation;
			if (type == 1)
				invert(tempPermutation);
			else if (type == 2)
				insert(tempPermutation);
			else
				swapp(tempPermutation);
			
			deltaDistance = getTourLength(tempPermutation);

			if ((deltaDistance < tempMin) ? 1 : exp(-(deltaDistance - tempMin) / temperature) > dis(e))
			{
				tempMin = deltaDistance;
				swap(tempMinPermutation, tempPermutation);
			}
			era++;
		}

		if ((tempMin < distance) ? 1 : exp(-(tempMin - distance) / temperature) > dis(e))
		{
			distance = tempMin;
			swap(tempMinPermutation, permutation);
		}

		temperature = coolingType == 1 ? temperature / (a + b * K) : temperature * coolingRate;
	}
	return distance ;
}

int SimAnnealing::getTourLength(vector<int> permutation)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if( i + 1 != size)
			sum += matrix[permutation[i]][permutation[i + 1]];
		else
			sum += matrix[permutation[i]][permutation[0]];
	}
	return sum;
}

void SimAnnealing::swapp(vector<int>& tempPermutation)
{
	int firstRandomCityIndex = rand() % (size)+0;
	int secondRandomCityIndex = rand() % (size)+0;

	if (firstRandomCityIndex != secondRandomCityIndex)
		swap(tempPermutation[firstRandomCityIndex], tempPermutation[secondRandomCityIndex]);
}

void SimAnnealing::invert(vector<int>& tempPermutation)
{
	int firstRandomCityIndex = rand() % (size)+0;
	int secondRandomCityIndex = firstRandomCityIndex + rand() % (size)+0;

	while (secondRandomCityIndex > size - 1)
	{
		secondRandomCityIndex--;
		firstRandomCityIndex--;
	}
	vector<int> rev, rev2;
	rev.insert(rev.begin(), tempPermutation.begin(), tempPermutation.begin() + firstRandomCityIndex);
	rev2.insert(rev2.begin(), tempPermutation.begin() + firstRandomCityIndex, tempPermutation.begin() + secondRandomCityIndex + 1);
	reverse(rev2.begin(), rev2.end());
	rev.insert(rev.end(), rev2.begin(), rev2.end());
	rev.insert(rev.begin() + secondRandomCityIndex + 1, tempPermutation.begin() + secondRandomCityIndex + 1, tempPermutation.end());

	tempPermutation = rev;
}

void  SimAnnealing::insert(vector<int>& tempPermutation)
{
	int firstRandomCityIndex = rand() % (size)+0;
	int secondRandomCityIndex = rand() % (size)+0;

	if (firstRandomCityIndex != secondRandomCityIndex)
	{
		vector<int> temp;
		for (int i = 0; i < tempPermutation.size(); i++)
		{
			if (i == firstRandomCityIndex)
			{
				temp.push_back(tempPermutation[secondRandomCityIndex]);
				temp.push_back(tempPermutation[firstRandomCityIndex]);
			}
			else if (i < secondRandomCityIndex)
				temp.push_back(tempPermutation[i]);
			else if (i > secondRandomCityIndex)
				temp.push_back(tempPermutation[i]);
		}
		tempPermutation = temp;
	}
}
