#include"helper.h"

row row::move_naive(direction d) const{
	if (d == R){
		row r = *this;
		reverse(r.c, r.c + 8);
		return r.move_naive(L);
	}
	else{
		row ret;
		ret.c[0] = this->c[0];
		for (int i = 1; i < 8; i++){
			if (this->c[i] == WALL) ret.c[i] = WALL;
			else if (this->c[i] == BLOCK && ret.c[i - 1] == EMPTY) ret.c[i - 1] = BLOCK;
		}
		return ret;
	}
}

int row::incode(const row& r){
	int ret = 0;
	for (int i = 0; i < 8; i++){
		ret *= 3;
		switch (r.c[i]){
		case WALL: ret++;
		case BLOCK: ret++;
		}
	}
	return ret;
}

row row::decode(int x){
	row ret;
	for (int i = 7; i >= 0; i--){
		switch (x % 3){
		case 1: ret.c[i] = BLOCK; break;
		case 2: ret.c[i] = WALL; break;
		}
		x /= 3;
	}
	return ret;
}

void row::create_map(){
	for (int i = 0; i < ROW_MAX; i++){
		row r = row::decode(i);
		row ll = r.move_naive(L),
			rr = r.move_naive(R);
		m[L][r] = ll;
		m[R][r] = rr;
		b[L][ll].push_back(r);
		b[R][rr].push_back(r);
	}
}

char row::get(int x) const{
	return this->c[x];
}

void row::set(int x, char c){
	this->c[x] = c;
}

row row::move(direction d) const{
	return m[d][*this];
}

vector<row> row::move_backward(direction d) const{
	return b[d][*this];
}

row::row(){
	for (int i = 0; i < 8; i++) c[i] = EMPTY;
	if (m[L].size() == 0) create_map();
}

row::row(const row& r){
	for (int i = 0; i < 8; i++) c[i] = r.c[i];
}

bool row::operator<(const row& rhs) const{
	for (int i = 0; i < 8; i++){
		if (this->c[i] < rhs.c[i]) return true;
		else if (this->c[i] > rhs.c[i]) return false;
	}
	return false;
}

map<row, row> row::m[2];
map<row, vector<row> > row::b[2];