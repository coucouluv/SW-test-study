#include <iostream>
#include <vector>
//#include <stdio.h> //freopen 함수
using namespace std;

struct Fish {
	int curx;
	int cury;
	int direct;
	bool live;
};

int y[] = {0,-1,-1,0,1,1,1,0,-1}; //반시계 +1
int x[] = {0,0,-1,-1,-1,0,1,1,1};
Fish fishes[17]; //물고기 정보
vector <vector <int>> space(4, vector<int>(4)); //공간
int maxnum = 0;

void print() {

	cout << "\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << space[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void movefish() {
	for (int i = 1; i <= 16; i++) {
		//상어한테 먹힘
		int dy = fishes[i].cury; // 원래 위치
		int dx = fishes[i].curx; 
		int direct = fishes[i].direct; // 원래 방향
		if (fishes[i].live == false) continue;
		while (1) {  
			int cy = dy + y[fishes[i].direct];
			int cx = dx + x[fishes[i].direct];
			if (cy < 0 || cy >= 4 || cx < 0 || cx >= 4) { //경계
				if (fishes[i].direct == 8)
					fishes[i].direct = 1;
				else
					fishes[i].direct = fishes[i].direct + 1;
			}
			else if (space[cy][cx] == -1) { //상어 위치임
				if (fishes[i].direct == 8)
					fishes[i].direct = 1;
				else
					fishes[i].direct = fishes[i].direct + 1;
			}
			else {	//이동할 수 있음 
				int swapfish = space[cy][cx];
				fishes[swapfish].cury = dy;
				fishes[swapfish].curx = dx;
				fishes[i].cury = cy;
				fishes[i].curx = cx;
				space[cy][cx] = i;
				space[dy][dx] = swapfish;
				break;
			}
			if (direct == fishes[i].direct) break;
		}
	}
}

void copyfish(struct Fish copy[], struct Fish original[]) {
	for (int i = 1; i <= 16; i++) {
		copy[i].cury = original[i].cury;
		copy[i].curx = original[i].curx;
		copy[i].direct = original[i].direct;
		copy[i].live = original[i].live;
	}
}

void moveshark(int sum, int dy, int dx , int direct) {
	
	maxnum = max(maxnum, sum);

	//이동하기 전 상태 저장해야함 왜냐면 물고기 구조체, 배열 다 바뀌어서,,,
	vector <vector <int>> tmp(4, vector<int>(4));
	Fish tmpfish[17];
	tmp = space;
	copyfish(tmpfish, fishes);

	//물고기 이동
	movefish();

	for (int i = 1; i <= 3; i++) {
		int cy = dy + y[direct] * i;
		int cx = dx + x[direct] * i;
		if (cy < 0 || cy >= 4 || cx < 0 || cx >= 4) continue;
		if (space[cy][cx] > 0) {
			//물고기 먹기
			int deadfish = space[cy][cx];
			space[cy][cx] = -1;
			space[dy][dx] = 0;
			fishes[deadfish].live = false;
			moveshark(sum + deadfish,cy,cx,fishes[deadfish].direct);

			//원래대로 되돌리기
			space[dy][dx] = -1;
			space[cy][cx] = deadfish;
			fishes[deadfish].live = true;
		}
		
	}
	//물고기 구조체, 배열 되돌리기
	space = tmp;
	copyfish(fishes,tmpfish);
	return;
}

int main() {

	int a, b; //a : 물고기 번호, b : 방향
	int tmpdirect;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a >> b;
			if (i == 0 && j == 0) {
				tmpdirect = b;
				maxnum = a;
				fishes[a].live = false;
				space[i][j] = -1; //상어 위치
				continue;
			}
			space[i][j] = a;
			fishes[a].cury = i;
			fishes[a].curx = j;
			fishes[a].direct = b;
			fishes[a].live = true;
		}
	}

	moveshark(maxnum, 0,0,tmpdirect);

	cout << maxnum << "\n";
	return 0;
}