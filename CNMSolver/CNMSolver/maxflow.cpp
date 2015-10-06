#include"maxflow.h"

MaxFlow::MaxFlow(int _n)
	:n(_n), g(_n), min_capacity(_n), back(_n), visited(_n) {};

void MaxFlow::add_edge(int from, int to, int capacity){
	int from_size = g[from].size();
	int to_size = g[to].size();

	g[from].emplace_back(edge{ to, capacity, to_size });
	g[to].emplace_back(edge{ from, 0, from_size });
}

bool MaxFlow::bfs(int from, int to){
	queue<int> q;
	fill(min_capacity.begin(), min_capacity.end(), INT_MAX);
	fill(visited.begin(), visited.end(), false);

	q.push(from);
	visited[from] = true;
	while (!q.empty()){
		int v = q.front();
		q.pop();

		for (int i = 0; i < g[v].size(); i++){
			const auto& e = g[v][i];
			if (e.capacity > 0){
				int there = e.target;
				if(!visited[there]){
					q.push(there);
					back[there] = e.rev;
					min_capacity[there] = min(min_capacity[v], e.capacity);
					visited[there] = true;
				}
			}
		}
	}

	return visited[to];
}

int MaxFlow::maxflow(int source, int sink){
	int ret = 0;

	while (bfs(source, sink)){
		int flow = min_capacity[sink];
		for (int it = sink; it != source; it = g[it][back[it]].target){
			int from = g[it][back[it]].target;
			int to = it;
			edge& neg_edge = g[to][back[to]];
			edge& pos_edge = g[from][neg_edge.rev];
			pos_edge.capacity -= flow;
			neg_edge.capacity += flow;
		}
		ret += flow;
	}

	return ret;
}
