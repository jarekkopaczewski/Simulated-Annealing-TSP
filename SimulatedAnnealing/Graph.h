#pragma once
#include <vector>
using namespace std;

class Graph
{
	public:
		Graph();
		Graph(int);
		~Graph();
		void setMatrix(int**);				//ustawia macierz -> wykorzystywane przy wczytywaniu z pliku
		void showMatrix();					//wyswietlanie macierzy
		int** getGraphMatrix();				//zwraca macierz
		int getSize();						//zwraca wielkosc - ilo�� wierzcho�k�w
		int getBasicCycle();
		vector<vector<int>> getVector();
	private:
		vector<vector<int>> vecMatrix;
		int** matrix;						//macierz s�siedztwa
		int	edgeNumber;						//ilo�� kraw�dzi
		int vertexNumber;					//ilo�� wirzcholkow
		void clearMatrix();					//usuwanie tablicy -> u�ywane przez destruktor
		int* calcSpaces();					//oblicza odstepy potrzebne do rownego wyswietlenia macierzy
		int calcLength(int);				//oblicza dlugosc liczby
};