#include <iostream>

using namespace std;

int N, M, R;
int A[102][102];
int tmp[102][102];
void updown() {

	for (int i = N-1; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = A[N - i - 1][j];
		}
	}
}

void leftright() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = A[i][M - j - 1];
		}
	}
}

void right90() {

	// N, M 바꾸기
	int tmpnum = N;
	N = M;
	M = tmpnum;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = A[M- j - 1][i];
		}
	}

}

void left90() {
	// N, M 바꾸기
	int tmpnum = N;
	N = M;
	M = tmpnum;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = A[j][N - i - 1];
		}
	}
}
void move(int originx, int originy, int copyx, int copyy) {

	int endx, endy;
	if (copyx < N / 2)
		endx = N / 2;
	else
		endx = N;

	if (copyy < M / 2)
		endy = M / 2;
	else
		endy = M;

	int indexy = originy;
	for (int i = copyx; i < endx; i++) {
		for (int j = copyy; j < endy; j++) {
			tmp[i][j] = A[originx][indexy++];
		}
		originx += 1;
		indexy = originy;
	}

}
void tmptoA() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			A[i][j] = tmp[i][j];
	}
}

void print() {
	//cout << "\n";
	//cout << "-------------\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << A[i][j] << " ";
		}
		cout << "\n";
	}
}
int main() {

	cin >> N >> M >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < R; i++) {
		int a; 
		cin >> a;
		if (a == 1)
			updown();
		else if (a == 2)
			leftright();
		else if (a == 3)
			right90();
		else if (a == 4)
			left90();
		else if (a == 5) {
			int indexN = N / 2, indexM = M / 2;
			move(0, 0, 0, indexM); //1->2
			move(0, indexM, indexN, indexM); // 2-> 3
			move(indexN, indexM, indexN, 0); //3->4
			move(indexN, 0, 0, 0); //4->1
		}
		else {
			int indexN = N / 2, indexM = M / 2;
			move(0,indexM,0,0); // 2->1
			move(indexN, indexM, 0, indexM); //3->2
			move(indexN, 0, indexN, indexM); // 4->3
			move(0, 0, indexN, 0); // 1->4
		}
		tmptoA();
		//print();
	}
	//출력
	print();
	return 0;
}


