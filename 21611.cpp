#include <iostream>
#include <cstring>
using namespace std;
int N, M;
int miro[51][51];
int bead[2601]; //구슬 목록
int shark;
int y[] = {0, -1,1,0,0 };
int x[] = {0, 0,0,-1,1 };
int rule[] = { 3,2,4,1 };
int totalboom[4]; //총 폭발 구슬 저장

void print() {
	//cout << "\n";
	//for (int i = 0; i < N * N; i++)
	//	cout << bead[i] << " ";
	//cout << "\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << miro[i][j] << " ";
		}
		cout << "\n";
	}
}

void storemiro() {
	
	int cnt = 1, index = 0;
	int dy = shark, dx = shark;
	int indbead = 0;
	memset(bead, 0, sizeof(bead)); //초기화
	//구슬저장
	while (1) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < cnt; j++) {
				dy = dy + y[rule[index]];
				dx = dx + x[rule[index]];
				if (dy == 1 && dx == 0) {
					return;
				}
				if(miro[dy][dx] > 0)
					bead[indbead++] = miro[dy][dx];
			}
			index += 1;
			if (index == 4) index = 0;
		}
		cnt++;
	}

}

void setmiro(int tmp[]) {
	int cnt = 1, index = 0;
	int dy = shark, dx = shark;
	int indbead = 0;
	memset(miro, 0, sizeof(miro)); //초기화
	//구슬저장
	while (1) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < cnt; j++) {
				dy = dy + y[rule[index]];
				dx = dx + x[rule[index]];
				if (dy == 1 && dx == 0) {
					return;
				}
				if (tmp[indbead] == 0) return; //끝에 도달했을 때
				miro[dy][dx] = tmp[indbead++];
			}
			index += 1;
			if (index == 4) index = 0;
		}
		cnt++;
	}
}

void boom() {

	//현재 미로 땡겨서 저장 
	storemiro();
	//폭발
	bool occur = true;
	
	while (occur) {
		occur = false;
		int index = 0;
		int tmp[2501] = { 0, };
		for (int i = 0; i < N * N - 3; i++) {
			if (bead[i] > 0) {
				int num = bead[i];
				if (bead[i + 1] == num && bead[i + 2] == num && bead[i + 3] == num) {
					bead[i] = 0;
					totalboom[num] += 1; //폭발 구슬 저장
					occur = true; //폭발 발생
					for (int j = i + 1; j < N * N; j++) {
						if (bead[j] == num) {
							bead[j] = 0;
							totalboom[num] += 1;
						}
						else break;
					}
				}
				else { tmp[index++] = bead[i];}
			}
		}
		//tmp에 있는거 넣기
		if (occur) {
			memset(bead, 0, sizeof(bead)); //초기화
			for (int i = 0; i < index; i++)
				bead[i] = tmp[i];
		}
		
	}
	//현재
	

}

void group() {

	int tmp[2501] = { 0, }; //구슬 넣을 배열
	int visited[2501] = { 0, }; //방문표시
	// A : 구슬 개수, B : 구슬번호
	int index = 0;
	for (int i = 0; i < N * N -1; i++) {
		if (bead[i] == 0) break; // 끝에 도달
		if (visited[i] == 0) {
			int num = bead[i], cnt = 1;
			visited[i] = 1;
			if (bead[i] == bead[i + 1]) { //연속함
				for (int j = i + 1; j < N * N; j++) {
					if (bead[j] == num) {
						cnt += 1;
						visited[j] = 1;
					}
					else break;
				}
			}
			//tmp에 넣기
			tmp[index++] = cnt;
			tmp[index++] = num;
		}
	}
	//미로에 넣기
	setmiro(tmp);
	
}

void throwice(int d, int s) {

	int dy = shark, dx = shark;
	for (int i = 0; i < s; i++) {
		dy = dy + y[d];
		dx = dx + x[d];
		if (dy <= 0 || dy > N || dx <= 0 || dx > N) continue;
		//구슬파괴
		miro[dy][dx] = 0;
	}

}
int main() {
	
	cin >> N >> M;
	shark = (N + 1) / 2; // 상어 위치 칸

	//세팅
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> miro[i][j];
		}
	}
	int d, s;
	for (int i = 0; i < M; i++) {
		cin >> d >> s;
		//블리자드
		//얼음던지기 후 빈칸 채움
		throwice(d,s);
		boom(); //폭발
		group(); //그룹 만들어서 구슬 넣고 난 후 미로에 반영
		//print();
	}
	int sum = 0;
	for (int i = 1; i <= 3; i++) {
		sum += totalboom[i] * i;
	}
	cout << sum;
	return 0;
}