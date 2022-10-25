#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAX = 4001;
struct Ball {
	int cury; //지금 있는곳
	int curx;
	int d; //방향
	int k; //에너지
	bool dead;
};
int N;
int y[] = {1,-1,0,0};//상 하 좌 우
int x[] = {0,0,-1,1};
int result = 0;
vector <Ball> ball;
int maps[MAX][MAX];

void input() {
	result = 0; //결과 리셋
	ball.clear(); //볼 리셋
	memset(maps, 0, sizeof(maps)); //맵 리셋
	cin >> N; //원자 개수
	int tx, ty, d, k;
	for (int i = 0; i < N; i++) {
		cin >> tx >> ty >> d >> k;
		tx = (tx + 1000) * 2;
		ty = (ty + 1000) * 2;
		struct Ball b;
		b.curx = tx;
		b.cury = ty;
		b.d = d;
		b.k = k;
		b.dead = false;
		ball.push_back(b);
		maps[tx][ty] = 1;
	}

}
bool all_dead() {
	for (int i = 0; i < ball.size(); i++) {
		if (ball[i].dead == false)
			return false;
	}
	return true;
}
void move() {
	
	while (1) {
		if (all_dead()) break;
		for (int i = 0; i < ball.size(); i++) {
			if (ball[i].dead == true) continue;
			//원자 움직임
			int dy = ball[i].cury + y[ball[i].d];
			int dx = ball[i].curx + x[ball[i].d];
			int direct = ball[i].d;
			if(dy >= 0 && dx >= 0 && dx < MAX && dy < MAX) {
				maps[ball[i].curx][ball[i].cury] = 0;
				ball[i].cury = dy;
				ball[i].curx = dx;
				maps[dx][dy] += 1;
				
			}
			else {
				maps[ball[i].curx][ball[i].cury] = 0;
				ball[i].dead = true;
			}
		}
		for (int i = 0; i < ball.size(); i++) {
			if (ball[i].dead == true) continue;
			//원자 움직임
			int dy = ball[i].cury;
			int dx = ball[i].curx;
			if (maps[dx][dy] >= 2) {
				for (int j = 0; j < ball.size(); j++) {
					if (ball[j].dead == true) continue;
					if (ball[j].cury == dy && ball[j].curx == dx) {
						ball[j].dead = true;
						result += ball[j].k;
					}
				}
				maps[dx][dy] = 0;
			}
		}
	}

 }

void solve() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		if (ball.size() == 0 || ball.size() == 1) {
			result = 0;
		}
		else
			move();
		cout << "#" << tc << " " << result << "\n";
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();

	return 0;
}