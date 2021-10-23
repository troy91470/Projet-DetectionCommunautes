#include <iostream>
#include <vector>
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph
{
	public:
		Graph();
		virtual ~Graph();
        	void printDab();
        	void addVertex(int num);
        	void addEdge(int v1, int v2);

    	protected:

    	private:
        	int countVertices;
        	vector<vector<int>> adjacencyList;
};

#endif // GRAPH_H