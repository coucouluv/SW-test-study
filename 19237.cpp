#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct Shark {
	int dy;
	int dx;
	int direct;
	bool live;
};

int N, M, k; //k가 냄새
int space[21][21][2]; //0: 상어 1:냄새 카운트
int sharkdirec[401][5][5]; //n번째 상어의 각 방향의 우선순위 저장
Shark shark[401]; //상어 
int y[] = {0,-1,1,0,0};
int x[] = {0,0,0,-1,1};

bool manyshark() {
	for (int i = 2; i <= M; i++) {
		if (shark[i].live == true)
			return true;
	}
	return false;
}

//냄새 정리
void smell() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (space[i][j][0] > 0 && shark[space[i][j][0]].live == true) {
				if (shark[space[i][j][0]].dy == i && shark[space[i][j][0]].dx == j)
					continue;
				if (space[i][j][1] == 1) {
					space[i][j][1] = 0;
					space[i][j][0] = 0;
				}
				else
					space[i][j][1] -= 1;
			}
			if (space[i][j][0] > 0 && shark[space[i][j][0]].live == false) {
				if (space[i][j][1] == 1) {
					space[i][j][1] = 0;
					space[i][j][0] = 0;
				}
				else
					space[i][j][1] -= 1;
			}
		}
	}

}
void moveshark() {
	//이게 부딪힐거 생각해서 임시공간이 필요하네..
	int tmp[21][21][2];
	memset(tmp, 0, sizeof(tmp));

	for (int i = 1; i <= M; i++) {
		if (shark[i].live == false) continue; //죽은 상어
		int cy = shark[i].dy;
		int cx = shark[i].dx;
		int direct = shark[i].direct;
		bool move = false;
		for (int j = 1; j <= 4; j++) {
			int ny = cy + y[sharkdirec[i][direct][j]];
			int nx = cx + x[sharkdirec[i][direct][j]];
			//경계일 때
			if (ny <= 0 || ny > N || nx <= 0 || nx > N) continue;
			//냄새 칸일 때
			if (space[ny][nx][0] > 0) continue;
			//아무 냄새도 없는 칸
			if (space[ny][nx][0] == 0) {
				if (tmp[ny][nx][0] > 0) { //이미 상어 있음
					shark[i].live = false;
				}
				else {
					shark[i].dy = ny;
					shark[i].dx = nx;
					shark[i].direct = sharkdirec[i][direct][j];
					tmp[ny][nx][0] = i;
					tmp[ny][nx][1] = k; //갱신
				}
				move = true;
				break;
			}
		}
		//자기 냄새 칸으로 밖에 못 갈 경우 따로 고려
		if (!move) {
			for (int j = 1; j <= 4; j++) {
				int ny = cy + y[sharkdirec[i][direct][j]];
				int nx = cx + x[sharkdirec[i][direct][j]];
				//경계일 때
				if (ny <= 0 || ny > N || nx <= 0 || nx > N) continue;
				//자기 냄새 칸
				if (space[ny][nx][0] == i) {
					shark[i].dy = ny;
					shark[i].dx = nx;
					shark[i].direct = sharkdirec[i][direct][j];
					tmp[ny][nx][0] = i;
					tmp[ny][nx][1] = k; //갱신
					break;
				}
			}
		}
	}
	//이제 정보를 space에 갱신
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tmp[i][j][0] > 0) {
				space[i][j][0] = tmp[i][j][0];
				space[i][j][1] = tmp[i][j][1];
			}
		}
	}
	//냄새 갱신
	smell();
}

void print() {
	cout << "------shark move-------\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << space[i][j][0] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "---------smell-------\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << space[i][j][1] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {

	cin >> N >> M >> k;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> space[i][j][0];
			if (space[i][j][0] > 0) {
				//상어 처음 위치
				shark[space[i][j][0]].dy = i;
				shark[space[i][j][0]].dx = j;
				shark[space[i][j][0]].live = true;
				space[i][j][1] = k;
			}
		}
	}
	int a;
	for (int i = 1; i <= M; i++) {
		cin >> a;
		//상어 처음 방향
		shark[i].direct = a;
	}
	//우선순위
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int z = 1; z <= 4; z++) {
				cin >> a;
				sharkdirec[i][j][z] = a;
			}
		}
	}

	int result = 0;
	while (result <= 1000) {
		moveshark();
		//print();
		result += 1;
		if (!manyshark()) 
			break;
	}
	if (result > 1000)
		cout << "-1";
	else
		cout << result << "\n";
	return 0;
}