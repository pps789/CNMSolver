#include<vector>
using namespace std;

#ifndef _MCMF_H_
#define _MCMF_H_

class MCMF{
private:
	struct edge{
		int target;
		int cost;
		int capacity;
	};
	int n;
	vector<vector<edge> > g;

public:
	MCMF(int _n);
	void add_edge(int from, int to, int cost, int capacity);
	int mcmf(int from, int to);
};

#endif
