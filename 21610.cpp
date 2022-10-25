#include <iostream>
#include <cstring>
using namespace std;
int N, M;
int A[51][51]; //물의 양
int cloud[51][51]; //구름
int y[] = {0,0,-1,-1,-1,0,1,1,1};
int x[] = {0,-1,-1,0,1,1,1,0,-1}; //8방향

void movecloud(int d, int s) {
	int newcloud[51][51] = { 0, }; //이동한 구름
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (cloud[i][j] == 1) { //구름 칸
				cloud[i][j] = 0;
				int dy = i + y[d]*s;
				int dx = j + x[d]*s;
				while (dy <= 0) dy += N;
				while(dx <= 0) dx += N;
				while(dy > N) dy -= N;
				while (dx > N) dx -= N;
				//물의 양 증가
				A[dy][dx] += 1;
				newcloud[dy][dx] = 1; //이동 완료
			}
		}
	}
	//물복사버그마법
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//물복사버그마법
			if (newcloud[i][j] == 1) {
				int cnt = 0; //개수 세기
				for (int n = 2; n <= 8; n += 2) {
					int ny = i + y[n];
					int nx = j + x[n];
					if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
					if (A[ny][nx] > 0) cnt += 1;
				}
				//물 양 증가
				A[i][j] += cnt;
			}
		}
	}
	//새로운 구름 생성
	//memset(cloud, 0, sizeof(cloud));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (A[i][j] >= 2 && newcloud[i][j] == 0) {
				A[i][j] -= 2;
				cloud[i][j] = 1;
			}
		}
	}
}

void sumwater() {
	int totalwater = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (A[i][j] > 0) {
				totalwater += A[i][j];
			}
		}
	}
	cout << totalwater;
}
void print() {
	cout << "------cloud----------\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << cloud[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "---------water-----\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}

}
int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	//초기구름
	for (int i = N - 1; i <= N; i++) {
		cloud[i][1] = 1;
		cloud[i][2] = 1;
	}

	//이동명령
	for (int i = 1; i <= M; i++) {
		int d, s; //방향, 속력
		cin >> d >> s;
		movecloud(d, s);
		//print();
	}
	//명령 후 총 물의 양
	sumwater();
	return 0;
}