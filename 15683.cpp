#include <iostream>
#include <vector>
using namespace std;
int N, M;
int result = 64;
int sum = 0;
vector<pair<pair <int, int>, int> > cctv;
int office[8][8];

int count_zero() {

	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (office[i][j] == 0)
				ret += 1;
		}
	}
	return ret;
}


void count_right(int dy, int dx) {
	for (int i = dx + 1; i < M; i++) {
		if (office[dy][i] == 6)
			break;
		else if (office[dy][i] == 0) {
			office[dy][i] = 7;
		}
		else
			continue;
	}
}
void count_left(int dy, int dx) {
	for (int i = dx - 1; i >= 0; i--) {
		if (office[dy][i] == 6)
			break;
		else if (office[dy][i] == 0) {
			office[dy][i] = 7;
		}
		else
			continue;
	}
}
void count_up(int dy, int dx) {
	for (int i = dy - 1; i >= 0; i--) {
		if (office[i][dx] == 6)
			break;
		else if (office[i][dx] == 0) {
			office[i][dx] = 7;
		}
		else
			continue;
	}
}
void count_down(int dy, int dx) {
	for (int i = dy + 1; i < N; i++) {
		if (office[i][dx] == 6)
			break;
		else if (office[i][dx] == 0) {
			office[i][dx] = 7;
		}
		else
			continue;
	}
}
void reset(int tmp[8][8]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = office[i][j];
		}
	}
}
void set(int tmp[8][8]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			office[i][j] = tmp[i][j];
		}
	}
}
void resolution(int index) {
	if (index == sum) {
		int num = count_zero();
		result = min(result, num);
		return;
	}

	int dy = cctv[index].first.first;
	int dx = cctv[index].first.second;
	int cctvnum = cctv[index].second;
	
	int tmp[8][8]; //이거 지역변수여야한다.
	reset(tmp);

	if (cctvnum == 2) {
		count_left(dy,dx);
		count_right(dy,dx);
		resolution(index + 1);
		set(tmp);

		count_up(dy, dx);
		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);
	}
	else if (cctvnum == 5) {
		count_left(dy, dx);
		count_right(dy, dx);
		count_up(dy, dx);
		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);
	}
	else if(cctvnum == 1) {
		count_left(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_right(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_up(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);
	}
	else if (cctvnum == 3) {
		count_right(dy, dx);
		count_up(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_right(dy, dx);
		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_left(dy, dx);
		count_up(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_left(dy, dx);
		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);
	}
	else {
		count_right(dy, dx);
		count_left(dy, dx);
		count_up(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_right(dy, dx);
		count_left(dy, dx);
		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_left(dy, dx);
		count_up(dy, dx);
		count_down(dy, dx);
		resolution(index + 1);
		set(tmp);

		count_right(dy, dx);
		count_down(dy, dx);
		count_up(dy, dx);
		resolution(index + 1);
		set(tmp);
	}
	
}


int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> office[i][j];
			if (office[i][j] > 0 && office[i][j] < 6) {
				cctv.push_back({ {i,j}, office[i][j] });
				sum += 1;
			}
		}
	}
	resolution(0);
	cout << result << "\n";
	return 0;
}