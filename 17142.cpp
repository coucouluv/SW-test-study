#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int zone[51][51];
int N, M;
vector <pair<int, int> > virus;
queue <pair <int, int> > que;
int y[] = { 0,0,-1,1 };
int x[] = { -1,1,0,0 };
int checkvirus[10];
int dist[51][51];
int result = 987654321;

void spread() {

	while (!que.empty()) {
		int dy = que.front().first;
		int dx = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int cury = dy + y[i];
			int curx = dx + x[i];
			if (cury < 0 || cury >= N || curx < 0 || curx >= N) continue;
			if (zone[cury][curx] == 1) continue;
			if (dist[cury][curx] == -1) {
				dist[cury][curx] = dist[dy][dx] + 1;
				que.push({cury, curx});
			}
		}
	}
}

void solution() {

	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			dist[i][j] = -1;
		
	for (int i = 0; i < 10; i++) {
		if (checkvirus[i]) {
			que.push({ virus[i].first,virus[i].second });
			dist[virus[i].first][virus[i].second] = 0;
		}
	}
	spread();
	int tmpmax = -1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (zone[i][j] == 0 && dist[i][j] == -1) {
				return;
			}
			if(zone[i][j] == 0 && dist[i][j] != -1)
				tmpmax = max(tmpmax, dist[i][j]);
		}
	}
	result = min(result, tmpmax);
}

void select(int cnt,int index) {
	if (cnt == M) {
		solution();
		return;
	}
	for (int i = index; i < virus.size(); i++) {
		if (!checkvirus[i]) {
			checkvirus[i] = 1;
			select(cnt + 1, i + 1);
			checkvirus[i] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	bool room = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> zone[i][j];
			if (zone[i][j] == 2) {
				virus.push_back({ i,j });
			}
			if (zone[i][j] == 0)
				room = true;
		}
	}
	if (!room) {
		cout << 0;
		return 0;
	}
	select(0,0);

	if (result == 987654321)
		cout << "-1\n";
	else
		cout << result << "\n";
	return 0;
}