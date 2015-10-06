#include<vector>
#include<algorithm>
#include<queue>
#include<functional>
#include<climits>
using namespace std;

#ifndef _MAXFLOW_H_
#define _MAXFLOW_H_

class MaxFlow{
private:
	struct edge{
		int target;
		int capacity;
		int rev; // g[target][rev]
	};
	int n;
	vector<vector<edge> > g;

	vector<int> min_capacity;
	vector<int> back;
	vector<bool> visited;
	bool bfs(int from, int to);

public:
	MaxFlow(int _n);
	void add_edge(int from, int to, int capacity);
	int maxflow(int source, int sink);
};

#endif
