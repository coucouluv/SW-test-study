#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M ,K;
int maps[22][22];
int y[] = {0,1,0,-1}; //동, 남, 서, 북
int x[] = {1,0,-1,0};
int dice[] = { 0,1,2,3,4,5,6 }; // 1:위, 2: 앞, 3: 동, 4: 서, 5:뒤, 6: 아래
int direct = 0; //초기 동쪽
int dicey = 1, dicex = 1; //주사위 초기 위치
int score = 0; //최종 점수
void diceright() {

	int up = dice[1];
	int right = dice[3];
	int left = dice[4];
	int down = dice[6];

	dice[1] = left;
	dice[3] = up;
	dice[4] = down;
	dice[6] = right;

}

void diceleft() {

	int up = dice[1];
	int right = dice[3];
	int left = dice[4];
	int down = dice[6];

	dice[1] = right;
	dice[3] = down;
	dice[4] = up;
	dice[6] = left;

}

void dicedown() {

	int up = dice[1];
	int front = dice[2];
	int back = dice[5];
	int down = dice[6];

	dice[1] = front;
	dice[2] = down;
	dice[5] = up;
	dice[6] = back;

}
void diceup() {

	int up = dice[1];
	int front = dice[2];
	int back = dice[5];
	int down = dice[6];

	dice[1] = back;
	dice[2] = up;
	dice[5] = down;
	dice[6] = front;

}

void addscore(int dy, int dx) {
	int visited[21][21] = { 0, };
	int mapscore = maps[dy][dx], cnt = 1;
	queue <pair <int, int> > que;
	que.push(make_pair(dy, dx));
	visited[dy][dx] = 1;
	while (!que.empty()) {
		int cy = que.front().first;
		int cx = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + y[i];
			int nx = cx + x[i];
			if (ny <= 0 || ny > N || nx <= 0 || nx > M) continue;
			if (visited[ny][nx] == 0 && maps[ny][nx] == mapscore) {
				visited[ny][nx] = 1;
				cnt += 1;
				que.push(make_pair(ny, nx));
			}
		}
	}
	//점수 갱신
	score += mapscore * cnt;
}

void move() {
	
	int dy = dicey + y[direct];
	int dx = dicex + x[direct];

	if (dy <= 0 || dy > N || dx <= 0 || dx > M) {
		direct = (direct + 2) % 4;
		dy = dicey + y[direct];
		dx = dicex + x[direct];
	}
	if (direct == 0) //동
		diceright();
	else if (direct == 1) //남
		dicedown();
	else if (direct == 2) // 서
		diceleft();
	else
		diceup();
	//cout << "bottom : " << dice[6] << "\n";
	//주사위 이동
	dicey = dy;
	dicex = dx;

	//점수 획득
	addscore(dy, dx);

	//이동방향 변경
	if (dice[6] > maps[dy][dx]) { //90도 시계
		direct = (direct + 1) % 4;
	}
	else if (dice[6] < maps[dy][dx]) { //90도 반시계
		if (direct == 0) direct = 3;
		else direct -= 1;
	}
}

int main() {
	
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> maps[i][j];
		}
	}
	
	//이동횟수
	for (int i = 0; i < K; i++) {
		//주사위 구르기
	//direct = 3;
		//cout << "dice : " << dicey << ", " << dicex << "\n";
 		move();
		//cout << "dice " << "\n";
		//for (int j = 1; j <= 6; j++)
		//	cout << dice[j] << " ";
		//cout << "\n";
	}
	cout << score;
	return 0;
}