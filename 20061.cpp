#include <iostream>
//#include <stdio.h> //freopen 함수
using namespace std;

int board[10][10]; //보드판
int point = 0; // 획득 점수

void print() {
	cout << "\n";
	cout << "0 1 2 3 4 5 6 7 8 9" << "\n";
	cout << "----------------------" << "\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void deleteblue(int j) {
	for (int n = j; n >= 4; n--) {
		for (int i = 0; i < 4; i++) {
			board[i][n] = board[i][n - 1];
		}
	}
}


void moveblue(int t, int x, int y) {
	int j;
	if (t == 1) {
		for (j = 4; j < 10; j++) {
			if (board[x][j] == 1)
				break;
		}
		board[x][j - 1] = 1;
	}
	else if (t == 2) {
		for (j = 4; j < 10; j++) {
			if (board[x][j] == 1)
				break;
		}
		board[x][j - 1] = 1;
		board[x][j - 2] = 1;
	}
	else {
		for (j = 4; j < 10; j++) {
			if (board[x][j] == 1 || board[x + 1][j] == 1)
				break;
		}
		board[x][j - 1] = 1;
		board[x + 1][j - 1] = 1;
	}

	// 열 가득 찼는지 확인
	bool full = true;
	for (int i = 0; i < 4; i++) {
		if (board[i][j - 1] == 0)
			full = false;
	}
	if (full) {
		point += 1;
		deleteblue(j - 1);
		j = j+1; //*주의* 두줄일때 두번째 줄 인덱스 변경해야함 -> 아래로 한줄 내려갔으니까
	}
	if (t == 2) {
		full = true;
		for (int i = 0; i < 4; i++) {
			if (board[i][j-2] == 0)
				full = false;
		}
		if (full) {
			point += 1;
			deleteblue(j-2);
		}
	}	
	//연한 파란색 확인
	bool blue;
	for (int j = 4; j <= 5; j++) {
		blue = false;
		for (int i = 0; i < 4; i++) {
			if (board[i][j] == 1)
				blue = true;
		}
		if (blue) deleteblue(9);
	}

}

void deletegreen(int i) {
	for (int n = i; n >= 4; n--) {
		for (int j = 0; j < 4; j++) {
			board[n][j] = board[n-1][j];
		}
	}
}

void movegreen(int t, int x, int y) {
	int i;
	if (t == 1) {
		for (i = 4; i < 10; i++) {
			if (board[i][y] == 1)
				break;
		}
		board[i-1][y] = 1;
	}
	else if (t == 2) {
		for (i = 4; i < 10; i++) {
			if (board[i][y] == 1 || board[i][y+1] == 1)
				break;
		}
		board[i-1][y] = 1;
		board[i-1][y+1] = 1;
	}
	else{
		for (i = 4; i < 10; i++) {
			if (board[i][y] == 1)
				break;
		}
		board[i - 1][y] = 1;
		board[i - 2][y] = 1;
	}
	// 행 가득 찼는지 확인
	bool full = true;
	for (int j = 0; j < 4; j++) {
		if (board[i-1][j] == 0)
			full = false;
	}
	if (full) {
		point += 1;
		deletegreen(i-1);
		i = i + 1; //*주의* 두줄일때 두번째 줄 인덱스 변경해야함 -> 아래로 한줄 내려갔으니까
	}
	if (t == 3) {
		full = true;
		for (int j = 0; j < 4; j++) {
			if (board[i-2][j] == 0)
				full = false;
		}
		if (full) {
			point += 1;
			deletegreen(i-2);
		}
	}

	//연한 초록색 확인
	bool green;
	for (int i = 4; i <= 5; i++) {
		green = false;
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 1)
				green = true;
		}
		if (green) deletegreen(9);
	}
}

void counttile() {
	int ret = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i < 4 && j >= 4) {
				ret += board[i][j];
			}
			if (i >= 4 && j < 4) {
				ret += board[i][j];
			}
		}
	}
	cout << ret << "\n";
}

int main() {
	int N;
	cin >> N;

	int t, x, y;

	for (int i = 0; i < N; i++) {
		cin >> t >> x >> y;
		moveblue(t, x, y);
		movegreen(t, x, y);
		//print();
	}
	//print();
	//획득점수
	cout << point << "\n";

	//타일 칸 세기
	counttile();
	return 0;
}