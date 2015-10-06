#include<vector>
#include<algorithm>
#include<queue>
#include<functional>
#include<climits>
using namespace std;

#ifndef _MCMF_H_
#define _MCMF_H_

class MCMF{
private:
	struct edge{
		int target;
		int cost;
		int capacity;
		int rev; // g[target][rev]
	};
	int n;
	vector<vector<edge> > g;

	vector<int> pi, distance, min_capacity;
	vector<int> back;
	bool dijkstra(int from, int to);

public:
	MCMF(int _n);
	void add_edge(int from, int to, int cost, int capacity);
	int mcmf(int source, int sink);
};

#endif
