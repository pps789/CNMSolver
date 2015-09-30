#include"helper.h"

state state::transpose() const{
	state ret;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			ret.c[j].set(i, this->c[i].get(j));
		}
	}
	return ret;
}

state state::move(direction d) const{
	if (d == L || d == R){
		state ret;
		for (int i = 0; i < 8; i++){
			ret.c[i] = this->c[i].move(d);
		}
		return ret;
	}
	else{
		state t = this->transpose();
		if (d == U) return t.move(L);
		else return t.move(R);
	}
}

state::state(){
	for (int i = 0; i < 8; i++) c[i] = row();
}

state::state(const state& s){
	for (int i = 0; i < 8; i++) c[i] = s.c[i];
}