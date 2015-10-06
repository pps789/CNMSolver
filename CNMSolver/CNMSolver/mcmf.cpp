#include"mcmf.h"

MCMF::MCMF(int _n)
	:n(_n), g(_n), pi(_n, 0),
	distance(_n, -1), min_capacity(_n), back(_n) {};

void MCMF::add_edge(int from, int to, int cost, int capacity){
	int from_size = g[from].size();
	int to_size = g[to].size();

	g[from].emplace_back(edge{ to, cost, capacity, to_size });
	g[to].emplace_back(edge{ from, -cost, 0, from_size });
}

bool MCMF::dijkstra(int from, int to){
	typedef pair<int, int> pii;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	fill(distance.begin(), distance.end(), INT_MAX);
	fill(min_capacity.begin(), min_capacity.end(), INT_MAX);

	pq.emplace(0, from);
	distance[from] = 0;
	while (!pq.empty()){
		int v = pq.top().second;
		int d = pq.top().first;
		pq.pop();

		if (d <= distance[v]){
			for (int i = 0; i < g[v].size(); i++){
				const auto& e = g[v][i];
				if (e.capacity > 0){
					int there = e.target;
					int D = d + e.cost + pi[v] - pi[there];
					if (D < distance[there]){
						distance[there] = D;
						pq.emplace(D, there);
						back[there] = e.rev;
						min_capacity[there] = min(min_capacity[v], e.capacity);
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) pi[i] += distance[i];
	return distance[to] < INT_MAX;
}

int MCMF::mcmf(int source, int sink){
	fill(pi.begin(), pi.end(), 0);
	int ret = 0;

	while (dijkstra(source, sink)){
		int flow = min_capacity[sink];
		for (int it = sink; it != source; it = g[it][back[it]].target){
			int from = g[it][back[it]].target;
			int to = it;
			edge& neg_edge = g[to][back[to]];
			edge& pos_edge = g[from][neg_edge.rev];
			ret += pos_edge.cost * flow;
			pos_edge.capacity -= flow;
			neg_edge.capacity += flow;
		}
	}

	return ret;
}
