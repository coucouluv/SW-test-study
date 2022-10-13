#include <iostream>

using namespace std;

int y[] = { 0,1,0,-1 }; //완 : 0, 아래 : 1, 오: 2, 위: 3
int x[] = { -1,0,1,0 }; //토네이도 이동 방향
int A[500][500];
int N;
int outsand = 0;

//(py, px) -> (ny, nx) , 방향
void movesand(int py, int px, int ny, int nx, int direct) {
	int sum = A[ny][nx]; //y의 모래
	A[ny][nx] = 0;
	double per[] = { 0.01,0.07,0.1 };
	int total = 0, tmp = 0;
	int move1, move2;
	if (direct == 1 || direct == 3) {
		move1 = 0, move2 = 2;
	}
	else {
		move1 = 1, move2 = 3;
	}
	int ay = py, ax = px; //x, y, a 위 아래
	int ty, tx;
	for (int i = 0; i < 3; i++) {
		ty = ay + y[move1];
		tx = ax + x[move1];
		tmp = sum * per[i];
		total += tmp*2;
		if (ty <= 0 || ty > N || tx <= 0 || tx > N) {
			outsand += tmp;
		}
		else {
			A[ty][tx] += tmp;
		}
		ty = ay + y[move2];
		tx = ax + x[move2];
		if (ty <= 0 || ty > N || tx <= 0 || tx > N) {
			outsand += tmp;
		}
		else {
			A[ty][tx] += tmp;
		}
		ay = ay + y[direct];
		ax = ax + x[direct];
	}

	//y 위위 아래아래
	ty = ny + y[move1] * 2;
	tx = nx + x[move1] * 2;
	tmp = sum * 0.02;
	total += tmp * 2;
	if (ty <= 0 || ty > N || tx <= 0 || tx > N) {
		outsand += tmp;
	}
	else {
		A[ty][tx] += tmp;
	}
	ty = ny + y[move2] * 2;
	tx = nx + x[move2] * 2;
	if (ty <= 0 || ty > N || tx <= 0 || tx > N) {
		outsand += tmp;
	}
	else {
		A[ty][tx] += tmp;
	}

	//a의 옆
	ty = ny + y[direct] * 2;
	tx = nx + x[direct] * 2;
	tmp = sum * 0.05;
	total += tmp;
	if (ty <= 0 || ty > N || tx <= 0 || tx > N) {
		outsand += tmp;
	}
	else {
		A[ty][tx] += tmp;
	}

	//마지막 a
	ay = ny + y[direct];
	ax = nx + x[direct];
	tmp = sum - total;
	if (ay <= 0 || ay > N || ax <= 0 || ax > N) {
		outsand += tmp;
	}
	else {
		A[ay][ax] += tmp;
	}
	//cout << "move out total: " << outsand << "\n";
}

void print() {
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void movetonado(int start) {

	int dy = start, dx = start;
	int cnt = 1;
	int direct = 0;
	while (1) {
		//cout << "cnt is " << cnt << "\n";
		for (int i = 0; i < 2; i++) {
			//cout << "direct: " << direct << "\n";
			for (int j = 0; j < cnt; j++) {
				int ny = dy + y[direct];
				int nx = dx + x[direct];
				//이동 가능한 위치
				if (ny >= 1 && ny <= N && nx >= 1 && nx <= N) {
					if(A[ny][nx] > 0)
						movesand(dy, dx, ny, nx, direct);
					dy = ny;
					dx = nx; //현재 위치 바꾸기
					//cout << "tonado arrive: " << dy << ", " << dx << "\n";
					//print();
				}
				if (dy == 1 && dx == 1) return;
			}
			direct += 1;
			if (direct == 4) direct = 0;
		}
		cnt += 1;
	}
}
int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;

	//처음 모래 세팅
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	int start = N / 2 + 1;
	movetonado(start);
	//격자 밖으로 나간 모래
	cout << outsand;
	return 0;
}