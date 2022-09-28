#include <iostream>
using namespace std;

int result = -1;
int N, M, H;
int game[31][11];

bool check() {
	//만족하는 지 돌리는 부분....
	for (int j = 1; j <= N; j++) {
		int ladder = j;
		for (int i= 1; i <= H; i++) {
			if (game[i][ladder]) ladder += 1;
			else if (game[i][ladder-1]) ladder -= 1;
		}
		if (ladder != j)
			return false;
	}
	return true;
}

void solution(int num) {
	if (num > 3) return;
	if (check()) {       //사다리 만족하는지
		if (result == -1) result = num;
		else result = min(result, num);
		return;
	} 
	//여기가 이제 가로선 추가 부분
	for (int j = 1; j < N; j++) {
		for (int i = 1; i <= H; i++) {
			//양 옆에 가로선 없는지 확인
			if (game[i][j - 1] || game[i][j + 1] || game[i][j]) continue;
			game[i][j] = 1;
			solution(num + 1);
			game[i][j] = 0;
			//시간 절약
			while (!game[i][j-1] && !game[i][j+1]) i++;
		}
	}

}
int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M >> H;
	
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		game[a][b] = 1;
	}
	solution(0);
	cout << result << "\n";
	return 0;
}