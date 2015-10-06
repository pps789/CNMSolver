#include"helper.h"
#include"mcmf.h"

const int heuristic_engine::dx[] = { 1, -1, 0, 0 }, heuristic_engine::dy[] = { 0, 0, -1, 1 };

void heuristic_engine::update_dp(int x, int y){
	auto &here = dp[x][y];
	queue<pair<int, int> > q;
	q.emplace(x, y);
	here[x][y] = 0;

	while (!q.empty()){
		auto xy = q.front();
		q.pop();
		int cost = here[xy.first][xy.second];
		for (int i = 0; i < 4; i++){
			int x = xy.first + dx[i];
			int y = xy.second + dy[i];
			if (0 <= x&&x < 8 && 0 <= y&&y < 8){
				if (here[x][y] == -1){
					here[x][y] = cost + 1;
					q.emplace(x, y);
				}
			}
		}
	}
}

heuristic_engine::heuristic_engine(const state& s){
	state v = s.get_vanilla();

	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			update_dp(i, j);
		}
	}
}

inline int heuristic_engine::get_distance(
	int from_x, int from_y, int to_x, int to_y){
	return dp[from_x][from_y][to_x][to_y];
}

int heuristic_engine::heuristic(const state& st, const state& ed){
	auto sts = st.get_blocks();
	auto eds = ed.get_blocks();

	MCMF mcmf(sts.size() + eds.size() + 2);
	int source = 0, sink = sts.size() + eds.size() + 1;
	for (int i = 1; i <= sts.size(); i++){
		mcmf.add_edge(source, i, 0, 1);
	}
	for (int i = 1; i <= sts.size(); i++){
		for (int j = 1; j <= eds.size(); j++){
			mcmf.add_edge(
				i,
				sts.size() + j,
				get_distance(sts[i].first, sts[i].second, eds[j].first, eds[j].second),
				1);
		}
	}
	for (int j = 1; j <= eds.size(); j++){
		mcmf.add_edge(
			sts.size() + j,
			sink,
			0,
			1);
	}

	return mcmf.mcmf(source, sink);
}
