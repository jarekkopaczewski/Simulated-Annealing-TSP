#pragma once
#include "Graph.h"
#include <vector>
using namespace std;

static class SimAnnealing
{
public:
	SimAnnealing();
	~SimAnnealing();
	static vector<vector<int>> matrix;
	static int size;
	static int findSolution(Graph*, int, int);
	static int getTourLength(vector<int>);
	static void swapp(vector<int>&);
	static void invert(vector<int>&);
	static void insert(vector<int>&);
};

