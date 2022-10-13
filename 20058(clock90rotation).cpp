#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int y[] = { 0,0,-1,1 };
int x[] = { -1,1,0,0 };
int A[65][65];
int tmp[65][65];
int visited[65][65];
int N, Q;
int total = 0; //남아있는 얼음
int cnt;

void move(int ey, int ex, int index) {

	int indy, indx = ex;
	for (int i = ey - index + 1; i <= ey; i++) {
		indy = ey - index + 1;
		for(int j = ex - index + 1; j <= ex; j++) {
			tmp[indy++][indx] = A[i][j];
		}
		indx--;
	}
	for (int i = ey - index + 1; i <= ey; i++) {
		for (int j = ex - index + 1; j <= ex; j++) {
			A[i][j] = tmp[i][j];
		}
	}
	//for (int i = 0; i < L; i++) {
	//	for (int j = 0; j < L; j++) {
	//		tmp[j][L-i-1] = A[i+ey][j+ex];
	//	}
	//}
	//for (int i = 0; i < L; i++) {
	//	for (int j = 0; j < L; j++) {
	//		 A[i+ey][j+ex] = tmp[i][j];
	//	}
	//}
}

void rotation(int L) {
	L = (1 << L);
	int num = cnt / L ;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			move(L+i*L,L+j*L,L); //끝자리
			
		}
	}
	//이 rotaion index = 0부터
	//for (int i = 0; i < cnt; i += L) {
	//	for (int j = 0; j < cnt; j += L) {
	//		move(i, j , L); 

	//	}
	//}
}
void lose() {
	vector <pair <int, int>> block;
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			if (A[i][j] > 0) { //얼음 있음
				if (i == 1 && (j == 1 || j == cnt)) //가장 끝에 있는 친구들
					block.push_back({ i,j });
				else if (i == cnt && (j == 1 || j == cnt))
					block.push_back({ i,j });
				else {
					int sum = 0;
					for (int n = 0; n < 4; n++) {
						int cy = i + y[n];
						int cx = j + x[n];
						if (cy <= 0 || cy > cnt || cx <= 0 || cx > cnt) continue;
						if (A[cy][cx] > 0) //주변 얼음 조사
							sum += 1;
					}
					if (sum < 3) block.push_back({ i,j });
				}
			}
		}
	}
	//조건 만족 못하는 애들 -1
	for (int n = 0; n < block.size(); n++)
		A[block[n].first][block[n].second] -= 1;
}

void print() {
	cout << "\n";
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			cout <<  A[i][j] << " ";
		}
		cout << "\n";
	}
}
void output() {
	queue <pair <int, int>> que;
	memset(visited, 0, sizeof(visited));
	int finalsum = 0, finalblock = 0;
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			if (visited[i][j] == 0 && A[i][j] > 0) { //방문 안했고 얼음 잇음
				visited[i][j] = 1;
				que.push({ i,j });
				int tmpblock = 1;
				finalsum += A[i][j];
				//cout << tmpblock << " is " << A[i][j] << "water " << ", total : " << finalsum << "\n";
				while (!que.empty()) {
					int dy = que.front().first;
					int dx = que.front().second;
					que.pop();
					for (int n = 0; n < 4; n++) {
						int cy = dy + y[n];
						int cx = dx + x[n];
						if (cy <= 0 || cy > cnt || cx <= 0 || cx > cnt) continue;
						if (visited[cy][cx] == 0 && A[cy][cx] > 0) {
							visited[cy][cx] = 1;
							tmpblock += 1;
							finalsum += A[cy][cx];
							//cout << tmpblock << " is " << A[cy][cx] << "water " << ", total : " << finalsum << "\n";
							que.push({ cy,cx });
						}
					}
				}
				if (tmpblock > finalblock) finalblock = tmpblock;
			}
		}
	}
	cout << finalsum << "\n";
	cout << finalblock ;
}

int main() {

	cin >> N >> Q;
	cnt = (1 << N);
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			cin >> A[i][j];
		}
	}
	int L;
	for (int i = 0; i < Q; i++) {
		cin >> L;
		rotation(L); //회전하기
		//print();
		lose();
		//print();
	}
	//print();
	output();
	return 0;
}