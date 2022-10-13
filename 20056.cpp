#include <iostream>
#include <vector>
using namespace std;

struct Ball {
	int y;
	int x;
	int m; //질량
	int s; //속력
	int d; //방향
};
int N, M, K; //M - 볼 개수, K - 명령 개수
int y[] = {-1,-1,0,1,1,1,0,-1};
int x[] = {0,1,1,1,0,-1,-1,-1};
vector <Ball>space[51][51];
vector <Ball> fireball;
void addanddivide() {
	vector <Ball> tmp;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int size = space[i][j].size();
			if (size == 0) continue;
			else if (size == 1) tmp.push_back(space[i][j][0]);
			else { //들어있움
				int m = 0, s = 0;
				bool odd = true; //모두 홀수
				bool even = true; //모두 짝수
				for (int n = 0; n < size; n++) {
					m += space[i][j][n].m;
					s += space[i][j][n].s;
					if (space[i][j][n].d % 2 == 0) odd = false;
					else even = false;
					//cnt += 1;
				}
				m = m / 5;
				s = s / size;
				if (m == 0) continue;
				else {
					//파이어볼 나눠서 넣기!
					for (int n = 0; n < 4; n++) {
						int d;
						if (odd || even)
							d = n * 2;
						else
							d = n * 2 + 1;
						tmp.push_back({ i,j,m,s,d});
					}
				}
			}
		}
	}
	fireball = tmp;
}

void moveball() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			space[i][j].clear();
		}
	}

	for (int n = 0; n < fireball.size(); n++) {
		if (fireball[n].m == 0) continue;
		Ball cur = fireball[n];
		int cy = cur.y + y[cur.d] * cur.s;
		int cx = cur.x + x[cur.d] * cur.s;
		int cnt = 1;
		while (cy <= 0) {
			cy = cy + N * cnt;
			cnt++;
		}
		cnt = 1;
		while (cx <= 0) {
			cx = cx + N * cnt;
			cnt++;
		}
		cy = cy % N;
		cx = cx % N;
		if (cy == 0) cy = N;
		if (cx == 0) cx = N;
		space[cy][cx].push_back({cy,cx,cur.m,cur.s,cur.d});
	}

}
void sumfireball() {
	int sum = 0;
	for (int i = 0; i < fireball.size(); i++) {
		sum += fireball[i].m;
	}
	cout << sum;
}
int main() {
	
	cin >> N >> M >> K;

	int r, c, m, s, d;
	
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;
		fireball.push_back({ r,c,m,s,d});
	}
	//cout << -1 / N << "\n";
	for (int i = 0; i < K; i++) {
		//cout << i + 1 << "order \n";
		moveball(); //파이어볼 이동
		addanddivide(); //합치고 나누고
	}
	sumfireball(); //남아있는 질량 합
	return 0;
}