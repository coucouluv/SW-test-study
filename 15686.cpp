#include <iostream>
#include <vector>

using namespace std;

int N, M;
int city[51][51];
vector<pair< pair<int, int>, int> > chicken;
vector<pair<int, int> >home;
int result = 1000000;

int find_distance() {

	int home_size = home.size();
	int chicken_size = chicken.size();
	int ret = 0;
	for (int i = 0; i < home_size; i++) {
		int homey = home[i].first;
		int homex = home[i].second;
		int num = 1000000;
		for (int j = 0; j < chicken_size; j++) {
			if (chicken[j].second == 1) {
				int tmp = abs(homey - chicken[j].first.first) + abs(homex - chicken[j].first.second);
				num = min(num, tmp);
			}
		}
		ret += num;
	}
	return ret;
}


void solution(int cnt, int num) {
	if (cnt == M) {
		result = min(result, find_distance());
		return;
	}
	int size = chicken.size();
	for (int i = num; i < size; i++) {
		chicken[i].second = 1;
		solution(cnt + 1, i + 1);
		chicken[i].second = 0;
	}
}

int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> city[i][j];
			if (city[i][j] == 2) {
				chicken.push_back({ {i,j},0});
			}
			else if (city[i][j] == 1)
				home.push_back({ i, j });
		}
	}
	solution(0, 0);
	cout << result << "\n";
	return 0;
}