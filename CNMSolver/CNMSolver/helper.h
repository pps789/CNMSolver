#include<algorithm>
#include<map>
#include<vector>
#include<iostream>
#include<queue>
#include<string>
using namespace std;

#ifndef _HELPER_H_
#define _HELPER_H_

enum direction { L, R, D, U, DIR_LAST };
const char WALL = 'W', BLOCK = 'B', EMPTY = '.';
const int ROW_MAX = 6561;
const int ANS_MAX = 30;

class row{
private:
	char c[8];
	static map<row, row> m[2]; // cache of moving
	static map<row, vector<row> > b[2]; // cache of moving; barkwords
	row move_naive(direction d) const; // only L, R.
	
	static int incode(const row& r);
	static row decode(int x);

public:
	static void create_map();
	char get(int x) const;
	void set(int x, char c);
	row move(direction d) const; // only L, R.
	vector<row> move_backward(direction d) const; // only L, R.

	row();
	row(const row& r);
	row(const string& s);

	bool operator<(const row& rhs) const;
	bool operator==(const row& rhs) const;
	bool operator!=(const row& rhs) const;
};

class state{
private:
	row c[8];
	state transpose() const;
public:
	char get(int x, int y);
	state move(direction d) const;
	vector<state> move_backward(direction d) const;

	vector<pair<state, direction> > get_next() const;
	vector<pair<state, direction> > get_prev() const;

	state();
	state(const state& s);
	state(const vector<row>& v);

	bool operator<(const state& rhs) const;
	bool operator==(const state& rhs) const;
	bool operator!=(const state& rhs) const;
};

vector<direction> solve(const state& st, const state& ed);

#endif
