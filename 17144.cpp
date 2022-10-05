#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int room[51][51];
int R, C;
int aircondition[2];
int y[] = {0, -1, 0, 1}; //시계로 세팅
int x[] = {1, 0, -1, 0};
vector <pair <int, int> > dust;
int tmp[51][51];
void print() {
	int sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] == -1) continue;
			sum += room[i][j];
		}
	}
	cout << sum << "\n";
}
void dust_spread() {
	memset(tmp, 0, sizeof(tmp));
	tmp[aircondition[0]][0] = -1;
	tmp[aircondition[1]][0] = -1;
	for (int i = 0; i < dust.size(); i++) {
		int dy = dust[i].first;
		int dx = dust[i].second;
		int sum = 0, num = room[dy][dx] / 5;
		for (int j = 0; j < 4; j++) {
			int cury = dy + y[j];
			int curx = dx + x[j];
			if (cury < 0 || cury >= R || curx < 0 || curx >= C) continue;
			if (tmp[cury][curx] == -1) continue;
			tmp[cury][curx] += num;
			sum += 1;
		}
		num = room[dy][dx] - (num * sum);
		tmp[dy][dx] += num;
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			room[i][j] = tmp[i][j];
		}
	}
}

void aircondition_work() {
	memset(tmp, 0, sizeof(tmp));
	//위쪽 반시계방향
	int dy = aircondition[0];
	int dx = 1;
	int direct = 0;

	while(!(dx == 0 && dy == aircondition[0])) {
		int num = room[dy][dx];
		if (dy + y[direct] < 0 || dy + y[direct] >= R || dx + x[direct] < 0 || dx + x[direct] >= C)
			direct += 1;
		if (num > 0) {
			tmp[dy + y[direct]][dx + x[direct]] = num;
		}
		dy = dy + y[direct];
		dx = dx + x[direct];
	}
	
	//아래쪽 시계방향
	dy = aircondition[1];
	dx = 1;
	direct = 0;
	while (!(dx == 0 && dy == aircondition[1])) {
		int num = room[dy][dx];
		if (dy + y[direct] < 0 || dy + y[direct] >= R || dx + x[direct] < 0 || dx + x[direct] >= C) {
			if (direct == 0) direct = 3;
			else direct -= 1;
		}
		if (num > 0) {
			//room[dy][dx] = 0;
			tmp[dy + y[direct]][dx + x[direct]] = num;
		}
		dy = dy + y[direct];
		dx = dx + x[direct];
	}
	//room에 그대로 복사
	dy = aircondition[0];
	dx = 1;
	direct = 0;
	while (!(dx == 0 && dy == aircondition[0])) {
		room[dy][dx] = tmp[dy][dx];
		if (dy + y[direct] < 0 || dy + y[direct] >= R || dx + x[direct] < 0 || dx + x[direct] >= C)
			direct += 1;
		dy = dy + y[direct];
		dx = dx + x[direct];
	}
	dy = aircondition[1];
	dx = 1;
	direct = 0;
	while (!(dx == 0 && dy == aircondition[1])) {
		room[dy][dx] = tmp[dy][dx];
		if (dy + y[direct] < 0 || dy + y[direct] >= R || dx + x[direct] < 0 || dx + x[direct] >= C) {
			if (direct == 0) direct = 3;
			else direct -= 1;
		}
		dy = dy + y[direct];
		dx = dx + x[direct];
	}
}


int main() {

	int T;
	cin >> R >> C >> T;

	int index = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1) {
				aircondition[index++] = i;
			}
			else if (room[i][j] > 0)
				dust.push_back({ i,j });
		}
	}

	for (int i = 0; i < T; i++) {
		// 미세먼지 확산
		dust_spread();
		//middle_print();
		//공기청정기 작동
		aircondition_work();

		//새로운 미세먼지 위치
		dust.clear();
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (room[i][j] > 0)
					dust.push_back({ i,j });
			}
		}
	}

	//남아있는 미세먼지 양 출력
	print();

	return 0;
}