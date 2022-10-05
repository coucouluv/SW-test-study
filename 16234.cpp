#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int N, L, R;
int A[51][51];
int day = 0;
int y[] = {1,-1,0,0};
int x[] = {0,0,1,-1};
queue<pair <int, int> > que;
queue<pair <int, int>> tmp;
int visited[50][50] = { 0, };
int main() {

	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> A[i][j];

	for (int n = 0; n <= 2000; n++) {
		bool move = false;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j]) {  //방문 안한 나라
					visited[i][j] = 1;
					que.push({ i,j });
					tmp.push({ i,j });
					int sum = A[i][j];
					while (!que.empty()) {
						int dy = que.front().first;
						int dx = que.front().second;
						que.pop();
						for (int i = 0; i < 4; i++) { //인접 국가 확인
							int cury = dy + y[i];
							int curx = dx + x[i];
							if (cury < 0 || cury >= N || curx < 0 || curx >= N) continue;
							if (!visited[cury][curx] && abs(A[dy][dx] - A[cury][curx]) >= L && abs(A[dy][dx] - A[cury][curx]) <= R) { //방문 안했고 조건 만족하는 국가
								visited[cury][curx] = 1; 
								sum += A[cury][curx];
								tmp.push({ cury, curx });
								que.push({ cury, curx });
							}
						}
					}
					if (tmp.size() > 1) { //연합했다면
						int num = sum / tmp.size();
						while (!tmp.empty()) {
							int dy = tmp.front().first;
							int dx = tmp.front().second;
							tmp.pop();
							A[dy][dx] = num; //연합 국가 값 변경
						}
						move = true; //연합 여부
					}
					else tmp.pop();
				}
			}
		}
		if (move) day += 1; //연합했다면 
		else break;
	}
	cout << day << "\n";
	return 0;
}