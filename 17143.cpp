#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
struct Sharkinfo{
	int s;
	int d;
	int z;
};
int pool[101][101];
int R, C, M;
vector<Sharkinfo> shark[101][101];
vector<Sharkinfo> tmp[101][101];
int resultsum = 0;
int y[] = {0,-1,1,0,0};
int x[] = {0,0,0,1,-1};
void catch_shark(int index) {

	for (int i = 1; i <= R; i++) {
		if (pool[i][index] == 1) {
			resultsum += shark[i][index].front().z;
			pool[i][index] = 0;
			shark[i][index].pop_back();
			break;
		}
	}

}

void move_shark() {
	int num = 0;
	memset(pool, 0, sizeof(pool));
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int size = shark[i][j].size();
			int dy = i;
			int dx = j;
			for (int n = 0; n < size; n++) {
				//상어 이동 후 tmp에 저장
				//좌표 계산
				int direct = shark[i][j][n].d;
				int sharksize = shark[i][j][n].z;
				int fast = shark[i][j][n].s;
				num++;
				while (fast > 0) {
					int test;
					if (direct == 1) { //위
						test = abs(dy - 1);
						if (fast >= test) {
							fast -= test;
							dy = 1;
							direct = 2; //아래
						}
						else {
							dy = dy - fast;
							fast = 0;
						}
					}
					else if(direct == 2) { //아래
						test = abs(R - dy);
						if (fast >= test) {
							fast -= test;
							dy = R;
							direct = 1; //위
						}
						else {
							dy = dy + fast;
							fast = 0;
						}
					}
					else if (direct == 4) { //왼쪽
						test = abs(dx - 1);
						if (fast >= test) {
							fast -= test;
							dx = 1;
							direct = 3; //오른쪽
						}
						else {
							dx = dx - fast;
							fast = 0;
						}
					}
					else { //오른쪽
						test = abs(C - dx);
						if (fast >= test) {
							fast -= test;
							dx = C;
							direct = 4; //왼쪽
						}
						else {
							dx= dx + fast;
							fast = 0;
						}
					}
				}
				//cout << dy << ", " << dx << "\n";
				// pool에 표시
				//만약 해당 좌표에 상어 정보 있을 때
				//비교해서 크기 큰걸로 교체
				if(pool[dy][dx]) {
					if (tmp[dy][dx][0].z < sharksize) {
						tmp[dy][dx][0].z = sharksize;
						tmp[dy][dx][0].d = direct;
						tmp[dy][dx][0].s = shark[i][j][n].s;
					}
				}
				else {
					pool[dy][dx] = 1;
					Sharkinfo newshark;
					newshark.z = sharksize;
					newshark.d = direct;
					newshark.s = shark[i][j][n].s;
					tmp[dy][dx].push_back(newshark);
				}
			}
		}
	}
	//복사하기
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int size = tmp[i][j].size();
			shark[i][j].clear();
			if (size > 0) {
				shark[i][j] = tmp[i][j];
				tmp[i][j].clear();
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> R >> C >> M;
	int r, c, s, d, z;
	
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		pool[r][c] = 1;
		Sharkinfo tmp;
		tmp.s = s;
		tmp.d = d;
		tmp.z = z;
		shark[r][c].push_back(tmp);
	}

	//낚시왕 이동
	for (int i = 1; i <= C; i++) {
		//낚시왕의 상어잡기
		catch_shark(i);

		move_shark();
		//상어 이동
	}
	cout << resultsum << "\n";
	return 0;
}