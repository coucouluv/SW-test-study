#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N;
int zone[21][21];
int result = 40000;
int seperate[21][21];
int zonepeople[6] = { 0, };
vector <pair <int, int>> r;
vector <pair <int, int>> d;

void findmin() {
	//구역 인원 reset
	for (int i = 1; i <= 5; i++)
		zonepeople[i] = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			zonepeople[seperate[i][j]] += zone[i][j];
		}
	}
	int maxnum = 0, minnum = 40000;
	for (int i = 1; i <= 5; i++) {
		maxnum = max(zonepeople[i], maxnum);
		minnum = min(zonepeople[i], minnum);
	}
	result = min(result, maxnum - minnum);
}

void checkzone(int x, int y, int d1, int d2) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (seperate[i][j] != 5) {
				if (x + d1 > i && y >= j) { //1번
					seperate[i][j] = 1;
				}
				else if (x + d2 >= i && j > y && j <= N) { //2번
					seperate[i][j] = 2;
				}
				else if (i >= x + d1 && j < y - d1 + d2) { //3번
					seperate[i][j] = 3;
				}
				else if (i > x + d2 && j >= y - d1 + d2) { //4번
					seperate[i][j] = 4;
				}
			}
			
		}
	}

}
void print() {
	cout << "\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << seperate[i][j] << " ";
		}
		cout << "\n";
	}
	
}
int main() {
	
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> zone[i][j];
		}
	}
	// x,y d1,d2 정하기
	
	for (int i = 1; i < N; i++) { //x
		for (int j = 1; j < N; j++) { //y
			for (int k = 1; k < N; k++) { //d1
				if (j - k < 1)
					break;
				for (int z = 1; z < N; z++) { //d2
					if (i + k + z > N)
						break;
					if (j + z > N)
						break;
					r.push_back(make_pair(i, j));
					d.push_back(make_pair(k, z));
				}
			}
		}
	}
	int x, y, d1, d2;
	for (int n = 0; n < r.size(); n++) {
		memset(seperate, -1, sizeof(seperate));
		x = r[n].first;
		y = r[n].second;
		d1 = d[n].first;
		d2 = d[n].second;
		//경계표시하기
		int i = x, j = y;
		while (i <= x + d1 && j >= y - d1) {
			seperate[i][j] = 5;
			i++;
			j--;
		}
		i = x, j = y;
		while (i <= x + d2 && j <= y + d2) {
			seperate[i][j] = 5;
			i++;
			j++;
		}
		i = x + d1, j = y - d1;
		while (i <= x + d1 + d2 && j <= y - d1 + d2) {
			seperate[i][j] = 5;
			i++;
			j++;
		}
		i = x + d2, j = y + d2;
		while (i <= x + d1 + d2 && j >= y + d2 - d1) {
			seperate[i][j] = 5;
			i++;
			j--;
		}
		for (i = x + 1; i < x + d1 + d2; i++) {
			int start = 0;
			for (j = 1; j <= N; j++) {
				if (seperate[i][j] == 5) {
					if (!start) start = j;
					else start = 0;
				}
				if (start > 0 && j >= start)
					seperate[i][j] = 5;
			}
		}
		//print();
		//1~4구역 표시하기
		checkzone(x,y,d1,d2);
		//print();
		// 인구 차이 구하기
		findmin();
	}
	cout << result << "\n";
	return 0;
}