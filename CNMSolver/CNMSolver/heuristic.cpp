#include"helper.h"
#include"mcmf.h"

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
