#include"helper.h"

int main(){
	row::create_map();

	cout << "Start: " << endl;
	vector<row> v;
	for (int i = 0; i < 8; i++){
		string str;
		cin >> str;
		v.push_back(row(str));
	}
	state st(v);

	cout << "End: " << endl;
	v.clear();
	for (int i = 0; i < 8; i++){
		string str;
		cin >> str;
		v.push_back(row(str));
	}
	state ed(v);

	auto ans = solve(st, ed);
	string ans_str = "LRDU";
	for (direction d : ans)
		cout << ans_str[(int)d];
}