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
		if (d == U) return t.move(L).transpose();
		else return t.move(R).transpose();
	}
}

state::state(){
	for (int i = 0; i < 8; i++) c[i] = row();
}

state::state(const state& s){
	for (int i = 0; i < 8; i++) c[i] = s.c[i];
}

state::state(const vector<row>& v){
	for (int i = 0; i < 8; i++) c[i] = v[i];
}

bool state::operator<(const state& rhs) const{
	for (int i = 0; i < 8; i++){
		if (this->c[i] < rhs.c[i]) return true;
		else if (rhs.c[i] < this->c[i]) return false;
	}
	return false;
}

bool state::operator!=(const state& rhs) const{
	for (int i = 0; i < 8; i++)
		if (c[i] != rhs.c[i])
			return true;
	return false;
}

bool state::operator==(const state& rhs) const{
	return !(this->operator!=(rhs));
}

vector<state> state::move_backward(direction d) const{
	if (d == U || d == D){
		state t = this->transpose();
		vector<state> tr_back;
		if (d == U) tr_back = t.move_backward(L);
		else tr_back = t.move_backward(R);
		vector<state> ret;
		for (const auto& tb : tr_back)
			ret.push_back(tb.transpose());
		return ret;
	}
	else{
		vector<vector<row> > row_back(8);
		for (int i = 0; i < 8; i++)
			row_back[i] = c[i].move_backward(d);
		vector<vector<row> > cart;
		cart.push_back(row_back[0]);
		for (int i = 1; i < 8; i++){
			vector<vector<row> > tmp;
			for (const auto& target : cart){
				for (const auto& frag : row_back[i]){
					tmp.push_back(target);
					tmp.back().push_back(frag);
				}
			}
			cart = tmp;
		}
		vector<state> ret;
		for (const auto& v : cart) ret.push_back(state(v));
		return ret;
	}
}

vector<pair<state, direction> > state::get_next() const{
	vector<pair<state, direction> > ret;
	for (int i = 0; i < 4; i++){
		direction d = (direction)i;
		state s = move(d);
		ret.push_back(pair<state, direction>(s, d));
	}
	return ret;
}

vector<pair<state, direction> > state::get_prev() const{
	vector<pair<state, direction> > ret;
	for (int i = 0; i < 4; i++){
		direction d = (direction)i;
		vector<state> vs = move_backward(d);
		for (const state& s : vs)
			ret.push_back(pair<state, direction>(s, d));
	}
	return ret;
}
