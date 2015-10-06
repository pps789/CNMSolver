#include"helper.h"

vector<direction> solve(
	const state& st,
	const state& ed){
	struct path{
		int c;
		direction d;
		state s;
	};
	map<state, path> dp;
	heuristic_engine HE(st);

	path p;
	p.c = 1;
	p.d = DIR_LAST;
	p.s = st;
	dp[st] = p;
	p.c = -1;
	p.s = ed;
	dp[ed] = p;

	queue<state> q;
	q.push(st);
	q.push(ed);
	state pos, neg;

	int max_cost = 0;
	int min_cost = 0;

	while (!q.empty()){
		state here = q.front();
		q.pop();
		int cost = dp[here].c;
		if (cost > 0){
			auto cond_next = here.get_next();
			for (auto sd : cond_next){
				if (!HE.heuristic(sd.first, ed, ANS_MAX - cost)) continue;
				if (!dp.count(sd.first)){
					p.c = cost + 1;
					p.d = sd.second;
					p.s = here;
					dp[sd.first] = p;
					q.push(sd.first);
				}
				else if (dp[sd.first].c < 0){
					q = queue<state>();
					pos = here;
					neg = sd.first;
					break;
				}
			}
		}
		else if (cost < 0){
			if (2 * (-cost) > max_cost){
				q.push(here);
				continue;
			}
			auto cond_prev = here.get_prev();
			for (auto sd : cond_prev){
				if (!HE.heuristic(st, sd.first, ANS_MAX - cost)) continue;
				if (!dp.count(sd.first)){
					p.c = cost - 1;
					p.d = sd.second;
					p.s = here;
					dp[sd.first] = p;
					q.push(sd.first);
				}
				else if (dp[sd.first].c > 0){
					q = queue<state>();
					pos = sd.first;
					neg = here;
					break;
				}
			}
		}
		if (dp.size() % 100000 == 0)cout << "SIZE: " << dp.size() << endl;
		if (cost > max_cost){
			cout << "STEP: " << cost << endl;
			max_cost = cost;
		}
		else if (cost < min_cost){
			cout << "STEP: " << cost << endl;
			min_cost = cost;
		}
	}

	cout << "Search done!" << endl;

	vector<direction> ret;
	for (state it = pos; it != st; it = dp[it].s)
		ret.push_back(dp[it].d);
	reverse(ret.begin(), ret.end());

	for (int i = 0; i < 4; i++){
		direction d = (direction)i;
		if (pos.move(d) == neg){
			ret.push_back(d);
			break;
		}
	}

	for (state it = neg; it != ed; it = dp[it].s)
		ret.push_back(dp[it].d);

	return ret;
}