#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int N, M;
int game[21][21];
int visited[21][21];
int y[] = { 0,0,-1,1 };
int x[] = { -1,1,0,0 };
int score = 0; //최종 스코어

void print() {
	cout << "\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << "\t" << game[i][j];
		}
		cout << "\n";
	}
}

void gravity() {
	for (int i = 1; i <= N; i++) {
		for (int j = N-1; j >= 1; j--) {
			if (game[j][i] >= 0) {
				int tmp = game[j][i];
				game[j][i] = -2;
				int n = j;
				for (; n <= N; n++) {
					if (game[n][i] == -1 || game[n][i] >= 0)
						break;
				}
				game[n-1][i] = tmp;
			}
		}

	}
}

//반시계 90도
void rotation() {

	int tmp[21][21];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			tmp[i][j] = game[j][N-i+1];
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			game[i][j] = tmp[i][j];
		}
	}
}

//큰 그룹 제거, 기준 블록부터
void erasegroup(int leady,int leadx) {
	memset(visited, 0, sizeof(visited));
	queue < pair<int, int> > group;
	int totalcnt = 1, color = game[leady][leadx];
	group.push({ leady,leadx});
	visited[leady][leadx] = 1;
	game[leady][leadx] = -2;
	while (!group.empty()) {
		int dy = group.front().first;
		int dx = group.front().second;
		group.pop();
		for (int n = 0; n < 4; n++) {
			int cy = dy + y[n];
			int cx = dx + x[n];
			if (cy <= 0 || cy > N || cx <= 0 || cx > N) continue;
			if (game[cy][cx] == -1) continue;
			if (game[cy][cx] == -2) continue;
			if (game[cy][cx] > 0 && color != game[cy][cx]) continue;
			if (visited[cy][cx] == 0) {
				visited[cy][cx] = 1;
				game[cy][cx] = -2; //제거
				group.push({ cy,cx });
				totalcnt += 1;
			}
		}
	}
	score += totalcnt * totalcnt;
}
void recoverzero() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (game[i][j] == 0) visited[i][j] = 0;
		}
	}
}
//가장 크기가 큰 블록 그룹 찾기
// 일반 블록 적어도 하나 색 동일
// 검은 블록 x, 기준 블록 일반 블록 중 행 작고 열 작고..
//여러개 ~~ 무지개 많은순, 기준 블록 행 큰순 ~~~ 열 큰 순
bool findgroup() {

	queue < pair<int, int> > group;
	int totalrainbow = 0, totaly = 0, totalx = 0, totalcnt = 2;
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int leadx = 0, leady = 0; //기준 블록  좌표
			int blocknum = 0; //일반 블록 색저장 
			int rainbow = 0; //무지개 개수 세기
			int cnt = 0; // 그룹 크기
			if (visited[i][j] == 0 && game[i][j] > 0) {
				visited[i][j] = 1;
				cnt += 1;
				group.push({i,j});
				leady = i, leadx = j;
				blocknum = game[i][j];
				while (!group.empty()) {
					int dy = group.front().first;
					int dx = group.front().second;
					group.pop();
					for (int n = 0; n < 4; n++) {
						int cy = dy + y[n];
						int cx = dx + x[n];
						if (cy <= 0 || cy > N || cx <= 0 || cx > N) continue;
						if (game[cy][cx] == -1) continue; //검정
						if (game[cy][cx] == -2) continue; //존재하지 않는
						if (game[cy][cx] > 0 && blocknum != game[cy][cx]) continue;
						if (visited[cy][cx] == 0) {
							visited[cy][cx] = 1;
							if (game[cy][cx] == 0) { //무지개
								rainbow += 1;
							}
							else {
								if (leady > cy) {
									leady = cy;
									leadx = cx;
								}
								else if (leady == cy && leadx > cx) {
									leady = cy;
									leadx = cx;
								}
							}
							group.push({ cy,cx });
							cnt += 1;
						}
					}
				}
				//여기서 이제 새로 갱신 이거 함수로 넣었으면 좋았을 듯
				if (totalcnt < cnt) { //지금까지 최고 큰 그룹
					totalcnt = cnt;
					totaly = leady;
					totalx = leadx;
					totalrainbow = rainbow;
				}
				else if (totalcnt == cnt) { //크기가 같음
					if (totalrainbow < rainbow) {//레인보우 개수
						totalcnt = cnt;
						totaly = leady;
						totalx = leadx;
						totalrainbow = rainbow;
					}
					else if (totalrainbow == rainbow) {
						if (totaly < leady) {//행
							totalcnt = cnt;
							totaly = leady;
							totalx = leadx;
							totalrainbow = rainbow;
						}
						else if (totaly == leady && totalx < leadx) { //열
							totalcnt = cnt;
							totaly = leady;
							totalx = leadx;
							totalrainbow = rainbow;
						}
					}
				}
				//여기서 0만 다시 원상태로..
				recoverzero();
			}
		}
	}
	if (totaly == 0 || totalx == 0)
		return false;

	erasegroup(totaly, totalx); //큰 그룹 제거

	return true;
}

int main() {
	cin >> N >> M;

	// -1: 검정, 0: 무지개, 그 외: 일반, -2: empty로 명시
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> game[i][j];
		}
	}
	
	while (1) {
		if (!findgroup()) {//가장 큰 블록 그룹 찾기, 제거
			break;
		}
		gravity(); // 중력 작용
		rotation(); //90도 반시계
		gravity(); //중력작용
		
	}
	cout << score;
	return 0;
}

