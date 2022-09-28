#include <iostream>

using namespace std;
int K;
int wheel[4][8];
int sum = 0;

int change[4] = {};
bool visited[4];
int twelve[4] = { 0, };

void solution(int num, int direct) {

	change[num] = direct;
	visited[num] = true;
	if (num - 1 >= 0 && !(visited[num - 1])) {
		if (direct == 0)
			solution(num - 1, 0);
		else if (wheel[num][(twelve[num] + 6) % 8] == wheel[num - 1][(twelve[num - 1] + 2) % 8]) {
			solution(num - 1, 0);
		}
		else {
			solution(num - 1, -direct);
		}
	}
	if (num + 1 <= 3 && !(visited[num + 1])) {
		if (direct == 0)
			solution(num + 1, 0);
		else if (wheel[num][(twelve[num] + 2) % 8] == wheel[num + 1][(twelve[num + 1] + 6) % 8]) {
			solution(num + 1, 0);
		}
		else {
			solution(num + 1, -direct);
		}
	}
}

int main() {

	string tmp;
	for (int i = 0; i < 4; i++) {
		cin >> tmp;
		for (int j = 0; j < 8; j++) {
			wheel[i][j] = tmp[j] - '0';

		}
	}
	cin >> K;

	for (int i = 0; i < K; i++) {
		int num, direct;
		cin >> num >> direct;
		
		for (int j = 0; j < 4; j++) {
			change[j] = 0;
			visited[j] = false;
		}
		solution(num-1, direct);
		//함수 안 쓰고 case 나눈 버전
		//if (num == 1) {
		//	if (wheel[0][(twelve[0] + 2) % 8] != wheel[1][(twelve[1] + 6) % 8]) {
		//		change[1] = change[0] * -1;
		//		if (wheel[1][(twelve[1] + 2) % 8] != wheel[2][(twelve[2] + 6) % 8]) {
		//			change[2] = change[1] * -1;
		//			if (wheel[2][(twelve[2] + 2) % 8] != wheel[3][(twelve[3] + 6) % 8]) {
		//				change[3] = change[2] * -1;
		//			}
		//		}
		//	}
		//	
		//}
		//else if (num == 2) {
		//	if (wheel[0][(twelve[0] + 2) % 8] != wheel[1][(twelve[1] + 6) % 8]) {
		//		change[0] = change[1] * -1;
		//	}
		//	if (wheel[1][(twelve[1] + 2) % 8] != wheel[2][(twelve[2] + 6) % 8]) {
		//		change[2] = change[1] * -1;
		//		if (wheel[2][(twelve[2] + 2) % 8] != wheel[3][(twelve[3] + 6) % 8]) {
		//			change[3] = change[2] * -1;
		//		}
		//	}
		//}
		//else if (num == 3) {
		//	if (wheel[2][(twelve[2] + 2) % 8] != wheel[3][(twelve[3] + 6) % 8]) {
		//		change[3] = change[2] * -1;
		//	}
		//	if (wheel[1][(twelve[1] + 2) % 8] != wheel[2][(twelve[2] + 6) % 8]) {
		//		change[1] = change[2] * -1;
		//		if (wheel[0][(twelve[0] + 2) % 8] != wheel[1][(twelve[1] + 6) % 8]) {
		//			change[0] = change[1] * -1;
		//		}
		//	}
		//}
		//else {
		//	if (wheel[3][(twelve[3] + 6) % 8] != wheel[2][(twelve[2] + 2) % 8]) {
		//		change[2] = change[3] * -1;
		//		if (wheel[1][(twelve[1] + 2) % 8] != wheel[2][(twelve[2] + 6) % 8]) {
		//			change[1] = change[2] * -1;
		//			if (wheel[0][(twelve[0] + 2) % 8] != wheel[1][(twelve[1] + 6) % 8]) {
		//				change[0] = change[1] * -1;
		//			}
		//		}
		//	}
		//}
		for (int j = 0; j < 4; j++) {
			if (change[j] == 1) {  //시계
				if (twelve[j] == 0) {
					twelve[j] = 7;
				}
				else {
					twelve[j] = twelve[j] - 1;
				}
			}
			else if (change[j] == -1) { //반시계
				twelve[j] = (twelve[j] + 1) % 8;
			}
		}
	}
	if (wheel[0][twelve[0]]) sum += 1;
	if (wheel[1][twelve[1]]) sum += 2;
	if (wheel[2][twelve[2]]) sum += 4;
	if (wheel[3][twelve[3]]) sum += 8;
	cout << sum << "\n";
	return 0;
}