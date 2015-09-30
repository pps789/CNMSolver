#include"helper.h"

row row::move(direction d) const{
	if (d == R){
		row r = *this;
		reverse(r.c, r.c + 8);
		return r.move(L);
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