#include <iostream>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

int N, M, K;
int A[11][11];
int zone[11][11];
int y[] = {0,0,1,-1,1,-1,1,-1};
int x[] = {1,-1,0,0,1,1,-1,-1};
deque<int> tree[11][11]; //나무
queue <pair< pair<int, int>, int> > dead, live;
int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			zone[i][j] = 5;
		}
	}
	//나무 정보
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		tree[a][b].push_back(c);
	}

	for (int n = 0; n < K; n++) {
		//봄
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				int cnt = tree[i][j].size();
				if (cnt == 0) continue;
				if (cnt > 1)
					sort(tree[i][j].begin(), tree[i][j].end());
				for (int k = 0; k < cnt; k++) {
					int num = tree[i][j].front();
					tree[i][j].pop_front();
					if (zone[i][j] >= num) {
						zone[i][j] -= num;
						tree[i][j].push_back(num + 1);
						if((num+1)%5 == 0)
							live.push({ {i,j},num + 1 });
					}
					else {
						dead.push({ {i,j},num});

					}
				}
			}
		}

		//여름
		while (!dead.empty()) {
			int dy = dead.front().first.first;
			int dx = dead.front().first.second;
			int num = dead.front().second;
			dead.pop();
			zone[dy][dx] += num / 2;
		}

		//가을
		while (!live.empty()) {
			int dy = live.front().first.first;
			int dx = live.front().first.second;
			int num = live.front().second;
			live.pop();

			//나무 번식
			for (int i = 0; i < 8; i++) {
				int cury = dy + y[i];
				int curx = dx + x[i];
				if (cury <= 0 || cury > N || curx <= 0 || curx > N) continue;
				tree[cury][curx].push_back(1);
			}
			
		}


		//겨울
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				zone[i][j] += A[i][j];
			}
		}
	}

	int finaltree = 0;
	//최종 나무 개수
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			finaltree += tree[i][j].size();
		}
	}
	cout << finaltree << "\n";
	return 0;
}