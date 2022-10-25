#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N, K;
vector <int> vec[101];
int tmp[101][101] = { 0, }; //임시로 저장

void findsmall() {
	int minnum = 10000;
	for (int i = 0; i < N; i++) {
		minnum = min(minnum, vec[i][0]);
	}
	for (int i = 0; i < N; i++) {
		if (minnum == vec[i][0])
			vec[i][0] += 1;
	}
}


void halfrotation() {
	int first = N / 2; //4
	int index = first;
	//첫번째
	for (int i = first -1; i >= 0; i--) {
		vec[index++].push_back(vec[i][0]);
		vec[i].pop_back();
	}
	//두번째
	int second = first / 2;
	index = first + second;
	//cout << second << ", " << index << "\n";
	int final = index - second;
	for (int i = index-1; i >= final; i--) {
		//cout << "index : " << i << "\n";
		for (int j = vec[i].size() - 1; j >= 0; j--) {
			vec[index].push_back(vec[i][j]);
		}
		vec[i].clear();
		index++;
	}
	//print();
}

void onedimand() {
	vector<int> one;
	for (int i = 0; i < N; i++) {
		if (vec[i].size() > 0) {
			for (int j = 0; j < vec[i].size(); j++) {
				one.push_back(vec[i][j]);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		vec[i].clear();
		vec[i].push_back(one[i]);
	}
	
}

void movefish() {
	memset(tmp, 0, sizeof(tmp));
	int index = 0;
	for (int i = 0; i < N; i++) {
		if (vec[i].size() > 0) {
			for (int j = 0; j < vec[i].size(); j++) {
				//좌
				if (i < N-1 && vec[i + 1].size() > j) {
					int num = abs(vec[i + 1][j] - vec[i][j])/5;
					if (vec[i][j] > vec[i + 1][j]) {
						tmp[i][j] -= num;
						tmp[i+1][j] += num;
					}
					else if (vec[i][j] < vec[i + 1][j]) {
						tmp[i][j] += num;
						tmp[i + 1][j] -= num;
					}
				}
				//우
				if (vec[i].size() > 1 && j < vec[i].size() - 1) {
					int num = abs(vec[i][j] - vec[i][j+1]) / 5;
					if (vec[i][j] > vec[i][j+1]) {
						tmp[i][j] -= num;
						tmp[i][j+1] += num;
					}
					else if (vec[i][j] < vec[i][j+1]) {
						tmp[i][j] += num;
						tmp[i][j+1] -= num;
					}
				}
			}
		}
	}
	//물고기 이동
	for (int i = 0; i < N; i++) {
		if (vec[i].size() > 0) {
			for (int j = 0; j < vec[i].size(); j++) {
				vec[i][j] += tmp[i][j];
			}
		}
	}
	//print();
}

void block() {
	//초기 설정
	int tmp = vec[0][0];
	vec[0].pop_back();
	vec[1].push_back(tmp);
	int sum = N - 1;
	bool possible = true;
	while (1) {
		//possible = false;
		for (int i = sum; i >= 0; i--) {
			if (vec[i].size() >= 2) {
				int index = i + 1, cnt = 0;
				while (index <= sum) {
					if (vec[index].size() >= 1)
						cnt += 1;
					if (cnt == vec[i].size())
						break;
					index += 1;
				}
				if (cnt == vec[i].size()) {
					for (int j = vec[i].size() - 1; j >= 0; j--) {
						vec[index--].push_back(vec[i][j]);
					}
					vec[i].clear();
					//possible = true;
				}
				else
					return;
			}
		}
		//print();
	}
}
bool difference() {
	int maxfish = 0, minfish = 10000;
	for (int i = 0; i < N; i++) {
		maxfish = max(maxfish, vec[i][0]);
		minfish = min(minfish, vec[i][0]);
	}
	int diff = maxfish - minfish;
	return diff <= K;
}
int main() {
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		vec[i].push_back(tmp);
	}
	int ret = 0;
	while (!difference()) {
		findsmall();
		block();
		movefish();
		onedimand();
		halfrotation();
		movefish();
		onedimand();
		ret += 1;
	}
	cout << ret;
	return 0;
}


