#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
struct Fish {
	int x;
	int y;
	int d;
	bool dead;
};
const int MAX = 1000001;
int space[5][5]; //물고기 개수
int smell[5][5]; //냄새칸
int M;
int dictionary[] = { 0,3,1,7,5};
int x[] = {0,0,-1,-1,-1,0,1,1,1};  
int y[] = {0,-1,-1,0,1,1,1,0,-1};
vector <Fish> fishes; //물고기
Fish  copyfishes[MAX];
int sharkx, sharky;
int copynum = 0; //복사한물고기 수
int eat = -1; //최대
int route[3] = { 0,0,0 }; //경로
void copyfish() {
	

	int index = 0;
	for (int i = 0; i < fishes.size(); i++) {
		if (fishes[i].dead == false) {
			copyfishes[index++] = fishes[i];
		}
	}
	copynum = index;
}

void addfish() {
	for (int i = 0; i < copynum; i++) {
		fishes.push_back(copyfishes[i]);

	}
}

void print() {
	cout << "-----space ----------\n";
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			cout << space[i][j] << " ";
		}
		cout << "\n";
	}
}
void movefish(int index) {
	//space 초기화
	memset(space, 0, sizeof(space));
	for (int i = 0; i < fishes.size(); i++) {
		if (fishes[i].dead == false) { //이동 완료
			int cx = fishes[i].x;
			int cy = fishes[i].y;
			int direc = fishes[i].d+1;
			//cout << "before : " << cx << ", " << cy << "\n";
			for (int j = 0; j < 8; j++) {
				direc -= 1;
				if (direc == 0) direc = 8;
				int dx = cx + x[direc];
				int dy = cy + y[direc];
				if (dx == sharkx && dy == sharky) continue;
				if (dx <= 0 || dx > 4 || dy <= 0 || dy > 4) continue;
				if (smell[dx][dy] != 0 && index - smell[dx][dy] <= 2) continue;
				fishes[i].x = dx;
				fishes[i].y = dy;
				fishes[i].d = direc;
				break;
			}
			//cout << "after : " << fishes[i].x << ", " << fishes[i].y << "\n";
			space[fishes[i].x][fishes[i].y] += 1;
		}
	}
	//print();
}

int eatfish(int tmp[]) {
	int visited[5][5] = {0,};
	int dx = sharkx, dy = sharky;
	//visited[sharkx][sharky] = 1;
	int ret = 0;
	for (int i = 0; i < 3; i++) {
		dx = dx + x[dictionary[tmp[i]]];
		dy = dy + y[dictionary[tmp[i]]];
		if (dx <= 0 || dx > 4 || dy <= 0 || dy > 4) return -1;
		if (visited[dx][dy] == 0) {
			visited[dx][dy] = 1;
			ret += space[dx][dy];
		}
	}
	return ret;
}
void moveshark(int cnt,int tmp[]) {
	if (cnt == 3) {
		//이동하면서 먹을 수 있는 물고기 출력
		int sum = eatfish(tmp);
		if (sum > eat) {
			eat = sum;
			//이동경로 저장
			for (int i = 0; i < 3; i++) {
				route[i] = tmp[i];
			}
		}
		return; 
	}
	for (int i = 1; i <= 4; i++) {
		tmp[cnt] = i;
		moveshark(cnt + 1, tmp);
	}
}

void deadfish(int index) {
	int tmp[3];
	eat = -1; //초기화 해주기
	moveshark(0, tmp);
	//1:상, 2:좌, 하:3, 우:4
	int dx = sharkx, dy = sharky;
	for (int i = 0; i < 3; i++) {
		//여기서 물고기 죽는거 처리해야하는디
		dx = dx + x[dictionary[route[i]]];
		dy = dy + y[dictionary[route[i]]];
		for (int i = 0; i < fishes.size(); i++) {
			if (fishes[i].dead == false) {
				if (fishes[i].x == dx && fishes[i].y == dy) { //물고기 죽음 그리고 냄새 남기
					fishes[i].dead = true;
					smell[dx][dy] = index;
				}
			}
		}

	}
	sharkx = dx, sharky = dy; //상어 위치 변경
}

int main() {
	int S;
	cin >> M >> S;

	for (int i = 0; i < M; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		fishes.push_back({ x,y,d,false });

	}
	
	cin >> sharkx >> sharky;
	for (int i = 1; i <= S; i++) {
		//복제 마법
		copyfish();
		//물고기 이동
		movefish(i);
		//상어 이동
		deadfish(i);
		//냄새 사라짐
		//복제 완료
		addfish();
	}
	//최종 물고기 수
	int ret = 0;
	for (int i = 0; i < fishes.size(); i++) {
		if (fishes[i].dead == false)
			ret += 1;
	}
	cout << ret;
	return 0;
}

