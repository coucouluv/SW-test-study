#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Passenger {
	int sty; //출발지
	int stx;
	int eny; //도착지
	int enx;
	bool arrive =false;
};

int N, M, gass;
int maps[21][21];
Passenger passenger[401];
int y[] = {0,0,-1,1};
int x[] = {-1,1,0,0}; //상하좌우
int dist[21][21]; //최단경로 저장
int findmaps(int cary, int carx) {

	memset(dist, -1, sizeof(dist));
	queue<pair <int, int> > que;
	que.push(make_pair(cary, carx));
	dist[cary][carx] = 0;

	while (!que.empty()) {
		int dy = que.front().first;
		int dx = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int cy = dy + y[i];
			int cx = dx + x[i];
			if (cy <= 0 || cy > N || cx <= 0 || cx > N) continue;
			if (maps[cy][cx] == 1 || dist[dy][dx] == -1) continue; //벽이거나 이동할 수 없는 곳일때
			if (dist[cy][cx] == -1) {
				dist[cy][cx] = dist[dy][dx] + 1;
				que.push(make_pair(cy, cx));
			}
		}
	}
	int finalpassenger = 0;
	int finaldist = 450;
	//최단 경로 승객 찾기
	for (int i = 1; i <= M; i++) {
		if (passenger[i].arrive == false) { //안 태운 손님 중
			int tmpdist = dist[passenger[i].sty][passenger[i].stx];
			if (tmpdist != -1) {
				if (finaldist > tmpdist) {
					finaldist = tmpdist;
					finalpassenger = i;
				}
				else if (finaldist == tmpdist) {
					if (passenger[finalpassenger].sty > passenger[i].sty) {
						finalpassenger = i;
					}
					else if (passenger[finalpassenger].sty == passenger[i].sty && passenger[finalpassenger].stx > passenger[i].stx) {
						finalpassenger = i;
					}
				}
			}
		}
	}
	return finalpassenger;
}

bool movetaxi(int cary,int carx, int eny, int enx) {
	memset(dist, -1, sizeof(dist));
	queue<pair <int, int> > que;
	que.push(make_pair(cary, carx));
	dist[cary][carx] = 0;
	while (!que.empty()) {
		int dy = que.front().first;
		int dx = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int cy = dy + y[i];
			int cx = dx + x[i];
			if (cy <= 0 || cy > N || cx <= 0 || cx > N) continue;
			if (maps[cy][cx] == 1 || dist[dy][dx] == -1) continue;
			if (dist[cy][cx] == -1) {
				dist[cy][cx] = dist[dy][dx] + 1;
				que.push(make_pair(cy, cx));
			}
		}
		if (dist[eny][enx] != -1)
			break;
	}
	if (dist[eny][enx] != -1) {
		if (gass >= dist[eny][enx]) {
			gass += dist[eny][enx];
			return true;
		}
	}
	return false;
}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> gass;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> maps[i][j];
		}
	}
	int cary, carx;
	cin >> cary >> carx; //처음 택시 위치

	int a, b, c, d; //승객 위치
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> c >> d;
		passenger[i].sty = a;
		passenger[i].stx = b;
		passenger[i].eny = c;
		passenger[i].enx = d;
	}
	bool finalgass = true;
	for (int i = 1; i <= M; i++) {
		//최단경로 찾기
		int pass = findmaps(cary,carx);
		//cout << "total gass : " << gass << "\n";
		//cout << "short distance passenger is " << pass <<"\n";
		//태울 수 있는 승객 없음
		if (pass == 0) {
			finalgass = false;
			break;
		}
		//택시가 승객까지 이동
		if (gass > dist[passenger[pass].sty][passenger[pass].stx]) {
			gass -= dist[passenger[pass].sty][passenger[pass].stx];
			cary = passenger[pass].sty; //택시 이동
			carx = passenger[pass].stx;
		}
		else { //이동 불가
			finalgass = false;
			break;
		}

		//도착지까지 이동 -> 연료 충전
		if (!movetaxi(cary, carx, passenger[pass].eny, passenger[pass].enx)) {
			finalgass = false;
			break;
		}
		//택시 위치 갱신 
		cary = passenger[pass].eny;
		carx = passenger[pass].enx;
		//승객 갱신 true
		passenger[pass].arrive = true;
	}
	if (!finalgass)
		cout << "-1";
	else
		cout << gass;
	return 0;
}