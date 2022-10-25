#include <iostream>

using namespace std;

int N;
int space[1005][1005];
int num = 0;
int x[] = {1,0,-1,0};
int y[] = {0,1,0,-1};

void tornado() {
	int cnt = N;
	//처음 토네이도
	int direct = 0, dx = 0, dy = 1;
	int last = N / 2 + 1;
	while (cnt > 0) {
		if (cnt == N) {
			for (int i = 0; i < N; i++) {
				dx = dx + x[direct];
				dy = dy + y[direct];
				space[dx][dy] = num;
				num -= 1;
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				direct += 1;
				if (direct == 4) direct = 0;
				for (int j = 0; j < cnt; j++) {
					dx = dx + x[direct];
					dy = dy + y[direct];
					space[dx][dy] = num;
					num -= 1;
				}
			}
		}
		cnt -= 1;
	}

}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	
	int findnum;
	cin >> findnum;

	num = N * N;
	tornado();
	
	int findx = 0, findy = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (space[i][j] == findnum) {
				findx = i;
				findy = j;
			}
			cout << space[i][j] << " ";
		}
		cout << "\n";
	}
	cout << findx << " " << findy;
	return 0;
}


