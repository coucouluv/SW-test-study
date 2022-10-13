#include <iostream>
#include <deque>
//#include <stdio.h> //freopen 함수
using namespace std;

deque <int> circle[51];
int N, M, T;

void movecircle(int x, int d, int k) {

	int tmp;
	for (int i = 1; i <= N; i++) {
		//배수라면
		if (i % x == 0) {
			//시계
			if (d == 0) {
				for (int j = 0; j < k; j++) {
					tmp = circle[i].back();
					circle[i].push_front(tmp);
					circle[i].pop_back();
				}
			}
			//반시계
			else {
				for (int j = 0; j < k; j++) {
					tmp = circle[i].front();
					circle[i].push_back(tmp);
					circle[i].pop_front();
				}
			}
		}
	}

}

void print() {

	for (int i = 1; i <= N; i++) {
		cout << i << " circle ";
		for (int j = 0; j < M; j++) {
			cout << circle[i][j] << " ";
		}
		cout << "\n";
	}
}
void result() {
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (circle[i][j] > 0)
				ret += circle[i][j];
		}
	}
	cout << ret << "\n";
}
void findsame() {
	bool same = false;
	int cnt = 0;
	double sum = 0;
	deque <int> tmp[51];
	for (int i = 1; i <= N; i++) {
		tmp[i].resize(M);
	}

	for (int i = 1; i <= N; i++) {
		//같은 원판에서 같은 수 찾기
		int index = 0;
		while (index < M) {
			if (index == 0) {
				if (circle[i][index] == circle[i][M - 1] || circle[i][index] == circle[i][index + 1])
					tmp[i][index] = 0;
				else
					tmp[i][index] = circle[i][index];
			}
			else if (index == M - 1) {
				if (circle[i][0] == circle[i][M - 1] || circle[i][index] == circle[i][index - 1])
					tmp[i][index] = 0;
				else
					tmp[i][index] = circle[i][index];
			}
			else {
				if (circle[i][index] == circle[i][index + 1] || circle[i][index] == circle[i][index - 1])
					tmp[i][index] = 0;
				else
					tmp[i][index] = circle[i][index];
			}
			index += 1;
		}
	}
	//같은 위치 같은 수
	for (int i = 0; i < M; i++) {
		int index = 1;
		while (index <= N) {
			if (index == 1) {
				if (circle[index][i] == circle[index + 1][i])
					tmp[index][i] = 0;
			}
			else if (index == N) {
				if (circle[index][i] == circle[index - 1][i])
					tmp[index][i] = 0;
			}
			else {
				if (circle[index][i] == circle[index + 1][i] || circle[index][i] == circle[index - 1][i])
					tmp[index][i] = 0;
			}
			index += 1;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmp[i][j] != circle[i][j]){
				same = true;
				circle[i][j] = 0;
			}
			else{
				if (circle[i][j] > 0) {
					sum += circle[i][j];
					cnt += 1;
				}
			}
		}
	}
	//평균구하고 더하고 빼고
	if (!same) {
		if (sum == 0) return;
		double number = (double)sum / cnt;
		//cout << number << "\n";
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (circle[i][j] > 0) {
					if (circle[i][j] > number)
						circle[i][j] -= 1;
					else if (circle[i][j] < number)
						circle[i][j] += 1;
				}
			}
		}
	}
}

int main() {
	//freopen함수
	//freopen("test.txt", "r", stdin);
	//freopen("test2.txt", "w", stdout);
	//scanf("%d %d %d", &N, &M, &T);

	cin >> N >> M >> T;

	////원판 셋팅
	for (int i = 1; i <= N; i++) {
		int a;
		for (int j = 0; j < M; j++) {
			cin >> a;
			//scanf("%d", &a);
			circle[i].push_back(a);
		}
	}
	//x - 원판 배수, d - 방향, k - k만큼 회전
	int x, d, k;
	for (int i = 0; i < T; i++) {
		cin >> x >> d >> k;
		//scanf("%d %d %d", &x, &d, &k);
		movecircle(x, d, k);
		//print();
		findsame();
		//print();
	}
	result();
	return 0;
}