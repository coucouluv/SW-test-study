#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int space[21][21];
int N;
int y[] = {-1,0,0,1};
int x[] = {0,-1,1,0};
int sharktime = 0;
int sharky, sharkx, shark =2; //아기상어 정보
int cnt = 0;
queue<pair< pair<int, int>, int>> que;

bool move_possible() {
	vector<pair< int, pair<int, int>>> final;
	int visited[20][20] = { 0, };
	que.push({ {sharky,sharkx}, 0});
	visited[sharky][sharkx] = 1;
	while (!que.empty()) {
		int dy = que.front().first.first;
		int dx = que.front().first.second;
		int distance = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int cury = dy + y[i];
			int curx = dx + x[i];
			if (cury < 0 || cury >= N || curx < 0 || curx >= N) continue;
			if (visited[cury][curx]) continue;
			if (space[cury][curx] > 0 && shark > space[cury][curx]) {
				visited[cury][curx] = 1;
				final.push_back({distance + 1,{cury,curx }});
			}
			else if (space[cury][curx] == 0 || space[cury][curx] == shark) {
				visited[cury][curx] = 1;
				que.push({ {cury,curx}, distance+1});
			}
		}
	}
	if(final.size() == 0) //갈 수 있는 곳이 없음
		return false;
	else {
		sort(final.begin(), final.end()); //가장 가깝고 조건 만족하는 곳
		sharky = final.front().second.first;
		sharkx = final.front().second.second;
		sharktime += final.front().first;
		space[sharky][sharkx] = 0;
		cnt += 1;
		return true;
	}
}


int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> space[i][j];
			if (space[i][j] == 9) {
				sharky = i;
				sharkx = j;
				space[i][j] = 0;
			}

		}
	}
	bool move = true;
	while (move) {

		move = false;
		if (cnt == shark) { //아기 상어 성장
			shark += 1;
			cnt = 0;
		}
		move = move_possible(); //갈 수 있는 곳이 있는지
	}
	cout << sharktime << "\n";
	return 0;
}