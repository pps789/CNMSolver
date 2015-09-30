#include<algorithm>
#include<map>
#include<vector>
using namespace std;

#ifndef _HELPER_H_
#define _HELPER_H_

enum direction { L, R, D, U };
const char WALL = 'W', BLOCK = 'B', EMPTY = '.';

class row{
private:
	char c[8];
	static map<row, row> m[2]; // cache of moving
	static map<row, vector<row> > b[2]; // cache of moving; barkwords
	row move(direction d) const; // only L, R.
	
	static int incode(const row& r);
	static row decode(int x);

public:
	static void create_map();
	char get(int x) const;
};

class state{
private:
	row c[8];
	state transpose() const;
public:
	char get(int x, int y);
	state move(direction d) const;
};

#endif