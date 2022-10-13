#include <iostream>
#include <vector>
using namespace std;

int chess[13][13];
int N, K;
int y[] = {0,0,0,-1,1};
int x[] = {0,1,-1,0,0};
vector<pair <pair<int, int>, int > > horse;
vector<int> chesshorse[13][13];

vector<int> findposition(int dy, int dx, int num) {
	vector <int> tmp;
	int index = 0;

	for (int j = 0; j < chesshorse[dy][dx].size(); j++) {
		if (num == chesshorse[dy][dx][j]) {
			index = j;
			break;
		}
	}
	for (int j = index; j < chesshorse[dy][dx].size(); j++) {
		tmp.push_back(chesshorse[dy][dx][j]);
	}
	return tmp;
}

bool moving() {

	for (int i = 0; i < K; i++) {
		int dy = horse[i].first.first;
		int dx = horse[i].first.second;
		vector <int> tmp;
		tmp = findposition(dy,dx,i);
		int ny = dy + y[horse[i].second];
		int nx = dx + x[horse[i].second];
		if (ny <= 0 || ny > N || nx <= 0 || nx > N || chess[ny][nx] == 2) {
			//방향바꿈
			if (horse[i].second % 2 == 0)
				horse[i].second -= 1;
			else
				horse[i].second += 1;
			ny = dy + y[horse[i].second];
			nx = dx + x[horse[i].second];
			if (ny <= 0 || ny > N || nx <= 0 || nx > N || chess[ny][nx] == 2) {
				ny = dy;
				nx = dx;
			}
		}
		//이제 이동하자
		//흰색
		if (chess[ny][nx] == 0) {
			for (int j = 0; j < tmp.size(); j++) {
				chesshorse[ny][nx].push_back(tmp[j]);
				horse[tmp[j]].first.first = ny;
				horse[tmp[j]].first.second = nx;
			}
			for (int j = 0; j < tmp.size(); j++) {
				chesshorse[dy][dx].pop_back();
			}
		}
		//빨간색
		else if (chess[ny][nx] == 1) {
			for (int j = tmp.size()-1; j >= 0; j--) {
				chesshorse[ny][nx].push_back(tmp[j]);
				horse[tmp[j]].first.first = ny;
				horse[tmp[j]].first.second = nx;

			}
			for (int j = 0; j < tmp.size(); j++) {
				chesshorse[dy][dx].pop_back();
			}
		}
		if (chesshorse[ny][nx].size() >= 4) return false;
	}
	return true;
}

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> chess[i][j];
		}
	}
	//말 정보
	int a, b, c;
	for (int i = 0; i < K; i++) {
		cin >> a >> b >> c;
		horse.push_back(make_pair(make_pair(a, b), c));
		chesshorse[a][b].push_back(i);
	}

	int endtime = 1;
	//말 이동  
	while (endtime <= 1000) {
		if (!moving()) {
			break;
		}
		//print();
		endtime += 1;
	}
	if (endtime > 1000)
		cout << "-1";
	else
		cout << endtime << "\n";
	return 0;
}