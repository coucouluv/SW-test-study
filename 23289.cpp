#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int zone[25][25];
int wall[25][25][5]; //내 기준 벽이 오, 윈, 위, 아래순으로 있다.
int R, C, K, W; //K : 온도, W: 벽의 개수
vector <pair <int, int> > searchtemp;
vector <pair <pair <int, int>, int> > warm; //히터기 x, y, 방향
//1:오, 2:왼, 3:위, 4:아래
int x[] = {0,0,0,-1,1};
int y[] = {0,1,-1,0,0};
int chocolate = 0;
//1:오, 2:왼, 3:위, 4:아래
//히터기 퍼지는 방향
int warmdx[5][3] = { {0,0,0}, {-1,0,1},{-1,0,1},{-1,-1,-1},{1,1,1}};
int warmdy[5][3] = { {0,0,0}, {1,1,1},{-1,-1,-1},{-1,0,1},{-1,0,1} };
void curprint() {

	cout << "\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << zone[i][j] << " ";
		}
		cout << "\n";
	}
}
bool endsearch() { //조사 여부
 	for (int i = 0; i < searchtemp.size(); i++) {
		int dx = searchtemp[i].first;
		int dy = searchtemp[i].second;
		if (zone[dx][dy] < K)
			return false;
	}
	return true;
}
void mix() {

	int tmp[25][25] = { 0, };
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			for (int n = 1; n <= 4; n += 3) {
				int cx = i + x[n];
				int cy = j + y[n];
				if (cx <= 0 || cx > R || cy <= 0 || cy > C) continue;
				if (wall[i][j][n] == 1) continue;
				if (zone[i][j] > zone[cx][cy]) {
					int num = (zone[i][j] - zone[cx][cy]) / 4;
					tmp[cx][cy] += num;
					tmp[i][j] -= num;
				}
				else if (zone[i][j] < zone[cx][cy]) {
					int num = (zone[cx][cy] - zone[i][j]) / 4;
					tmp[cx][cy] -= num;
					tmp[i][j] += num;
				}
			}

	
		}
		
	}
	//다시 원상복구
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			zone[i][j] +=tmp[i][j];
		}
	}

}
void sidetemp() {
	for (int x = 1; x < R; ++x) if (zone[x][1] > 0) zone[x][1]--;
	for (int y = 1; y < C; ++y) if (zone[R][y] > 0) zone[R][y]--;
	for (int x = R; x > 1; --x) if (zone[x][C] > 0) zone[x][C]--;
	for (int y = C; y > 1; --y) if (zone[1][y] > 0) zone[1][y]--;
}
bool checkwall(int dx, int dy, int nx, int ny, int direct, int index) {
	if (index == 1) {
		if (wall[dx][dy][direct] == 1) return false;
	}
	else if (index == 0) {
		if (direct == 1) { //오
			if (wall[dx][dy][3] == 1 || wall[nx][ny][2] == 1)
				return false;
		}
		else if (direct == 2) { //왼
			if (wall[dx][dy][3] == 1 || wall[nx][ny][1] == 1)
				return false;
		}
		else if (direct == 3) { //위
			if (wall[dx][dy][2] == 1 || wall[nx][ny][4] == 1)
				return false;
		}
		else { //아래
			if (wall[dx][dy][2] == 1 || wall[nx][ny][3] == 1)
				return false;
		}
	}
	else {
		if (direct == 1) { //오
			if (wall[dx][dy][4] == 1 || wall[nx][ny][2] == 1)
				return false;
		}
		else if (direct == 2) { //왼
			if (wall[dx][dy][4] == 1 || wall[nx][ny][1] == 1)
				return false;
		}
		else if (direct == 3) { //위
			if (wall[dx][dy][1] == 1 || wall[nx][ny][4] == 1)
				return false;
		}
		else { //아래
			if (wall[dx][dy][1] == 1 || wall[nx][ny][3] == 1)
				return false;
		}
	}
	return true;
}

void warmwind(int dx, int dy, int direct) {
	int visited[25][25] = { 0, };
	queue <pair<pair <int, int>, int> > que;
	dx = dx + x[direct];
	dy = dy + y[direct];
	if (dx <= 0 || dx > R || dy <= 0 || dy > C) return;
	zone[dx][dy] += 5;
	visited[dx][dy] = 1;
	que.push({ {dx,dy},5 });
	while (!que.empty()) {
		int cx = que.front().first.first;
		int cy = que.front().first.second;
		int score = que.front().second;
		que.pop();
		if (score == 1) continue;
		for (int i = 0; i < 3; i++) {
			int nx = cx + warmdx[direct][i];
			int ny = cy + warmdy[direct][i];
			if (nx <= 0 || nx > R || ny <= 0 || ny > C) continue;
			if (visited[nx][ny] == 0 && checkwall(cx,cy,nx,ny,direct,i)) {
				visited[nx][ny] = 1;
				zone[nx][ny] += score - 1;
				que.push({ {nx,ny},score - 1 });
			}
		}
	}

}

void blow() {
	for (int i = 0; i < warm.size(); i++) {
		warmwind(warm[i].first.first, warm[i].first.second, warm[i].second);
	}
	mix();
}

int main() {
	
	cin >> R >> C >> K;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int tmp;
			cin >> tmp;
			if (tmp == 5)
				searchtemp.push_back({ i,j });
			else if (tmp > 0) {
				warm.push_back({ {i,j},tmp });
			}
		}
	}

	cin >> W; //벽 정보
	for (int i = 0; i < W; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		if (t == 0) {
			wall[x][y][3] = 1;
			wall[x-1][y][4] = 1;
		}
		else {
			wall[x][y][1] = 1;
			wall[x][y+1][2] = 1;
		}
	}

	while (chocolate <= 100) {
		blow(); //온풍기
		//온도 조절
		//바깥 감소
		sidetemp();
		chocolate += 1;
		if (endsearch())
			break;
	}
	//curprint();
	if (chocolate > 100)
		cout << "101";
	else
		cout << chocolate;
	return 0;
}

