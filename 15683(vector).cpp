#include <iostream>
#include <vector>
using namespace std;
int N, M;
int result = 64;
int sum = 0;
vector<pair<pair <int, int>, int> > cctv;

int count_zero(vector<vector<int>> place) {

	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (place[i][j] == 0)
				ret += 1;
		}
	}
	return ret;
}

vector<vector<int>> count_all(int dy, int dx, vector<vector<int>> place) {

	for (int i = dx+1; i < M; i++) {
		if (place[dy][i] == 6)
			break;
		else if (place[dy][i] == 0) {
			place[dy][i] = 7;
		}
		else
			continue;
	}
	for (int i = dx - 1; i >= 0; i--) {
		if (place[dy][i] == 6)
			break;
		else if (place[dy][i] == 0) {
			place[dy][i] = 7;
		}
		else
			continue;
	}
	for (int i = dy + 1; i < N; i++) {
		if (place[i][dx] == 6)
			break;
		else if (place[i][dx] == 0) {
			place[i][dx] = 7;
		}
		else
			continue;
	}
	for (int i = dy - 1; i >= 0; i--) {
		if (place[i][dx] == 6)
			break;
		else if (place[i][dx] == 0) {
			place[i][dx] = 7;
		}
		else
			continue;
	}
	return place;
}

vector<vector<int>> count_right(int dy, int dx, vector<vector<int>>  place) {
	for (int i = dx + 1; i < M; i++) {
		if (place[dy][i] == 6)
			break;
		else if (place[dy][i] == 0) {
			place[dy][i] = 7;
		}
		else
			continue;
	}
	return place;
}
vector<vector<int>> count_left(int dy, int dx, vector<vector<int>> place) {
	for (int i = dx - 1; i >= 0; i--) {
		if (place[dy][i] == 6)
			break;
		else if (place[dy][i] == 0) {
			place[dy][i] = 7;
		}
		else
			continue;
	}
	return place;
}
vector<vector<int>> count_up(int dy, int dx, vector<vector<int>>  place) {
	for (int i = dy - 1; i >= 0; i--) {
		if (place[i][dx] == 6)
			break;
		else if (place[i][dx] == 0) {
			place[i][dx] = 7;
		}
		else
			continue;
	}
	return place;
}
vector<vector<int>> count_down(int dy, int dx, vector<vector<int>> place) {
	for (int i = dy + 1; i < N; i++) {
		if (place[i][dx] == 6)
			break;
		else if (place[i][dx] == 0) {
			place[i][dx] = 7;
		}
		else
			continue;
	}
	return place;
}
void resolution(int index, vector<vector<int>> place) {
	if (index == sum) {
		int num = count_zero(place);
		result = min(result, num);
		return;
	}

	int dy = cctv[index].first.first;
	int dx = cctv[index].first.second;
	int cctvnum = cctv[index].second;
	vector<vector<int>>  tmp;

	if (cctvnum == 2) {
		tmp = count_left(dy,dx, place);
		tmp = count_right(dy,dx, tmp);
		resolution(index + 1, tmp);

		tmp = count_up(dy, dx, place);
		tmp =count_down(dy, dx, tmp);
		resolution(index + 1, tmp);
	}
	else if (cctvnum == 5) {
		tmp = count_all(dy, dx, place);
		resolution(index + 1, tmp);
	}
	else if(cctvnum == 1) {
		tmp =count_left(dy, dx, place);
		resolution(index + 1, tmp);
		//count_left(dy, dx, 7, 0);

		tmp =count_right(dy, dx, place);
		resolution(index + 1, tmp);
		//count_right(dy, dx, 7, 0);

		tmp =count_up(dy, dx, place);
		resolution(index + 1, tmp);
		//count_up(dy, dx, 7, 0);

		tmp =count_down(dy, dx, place);
		resolution(index + 1, tmp);
	}
	else if (cctvnum == 3) {
		tmp =count_right(dy, dx, place);
		tmp =count_up(dy, dx, tmp);
		resolution(index + 1, tmp);

		tmp=count_right(dy, dx, place);
		tmp=count_down(dy, dx, tmp);
		resolution(index + 1, tmp);


		tmp = count_left(dy, dx, place);
		tmp = count_up(dy, dx, tmp);
		resolution(index + 1, tmp);


		tmp =count_left(dy, dx, place);
		tmp =count_down(dy, dx, tmp);
		resolution(index + 1, tmp);
	}
	else {
		tmp =count_right(dy, dx, place);
		tmp =count_left(dy, dx, tmp);
		tmp = count_up(dy, dx, tmp);
		resolution(index + 1, tmp);

		tmp = count_right(dy, dx, place);
		tmp = count_left(dy, dx, tmp);
		tmp = count_down(dy, dx, tmp);
		resolution(index + 1, tmp);

		tmp = count_left(dy, dx, place);
		tmp =count_up(dy, dx, tmp);
		tmp =count_down(dy, dx, tmp);
		resolution(index + 1, tmp);


		tmp = count_right(dy, dx, place);
		tmp = count_down(dy, dx, tmp);
		tmp = count_up(dy, dx, tmp);
		resolution(index + 1, tmp);
	}
}


int main() {

	cin >> N >> M;
	vector<vector<int>> office(8,vector<int>(8)); //2Â÷¿ø º¤ÅÍ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> office[i][j];
			if (office[i][j] > 0 && office[i][j] < 6) {
				cctv.push_back({ {i,j}, office[i][j] });
				sum += 1;
			}
		}
	}
	resolution(0, office);
	cout << result << "\n";
	return 0;
}