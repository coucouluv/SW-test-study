#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int A[101][101];
int r, c, k;
int row = 3, column = 3;
int tmpA[101][101];
void sortingR() {
	
	int maxvalue;
	maxvalue = column;
	memset(tmpA, 0, sizeof(tmpA));
	//행 정렬
	for (int i = 1; i <= row; i++) {
		int tmp[101] = { 0, };
		vector<pair<int, int>> tmpsort;
		tmpsort.push_back({ 0,0 });
		for (int j = 1; j <= column; j++) {
			tmp[A[i][j]] += 1;
		}
		//페어에 넣기
		for (int n = 1; n <= 100; n++) {
			if (tmp[n] > 0) {
				//cout << i << ", " << n << " : " << tmp[n] << "\n";
				tmpsort.push_back({ tmp[n],n });
			}
		}
		sort(tmpsort.begin(), tmpsort.end());
		int size = tmpsort.size();
		maxvalue = max(2*(size - 1), maxvalue);
		for (int n = 1; n < size; n++) {
			if (n > 50)
				break;
			tmpA[i][2*n-1] = tmpsort[n].second;
			tmpA[i][2*n] = tmpsort[n].first;
		}
	}
	column = maxvalue;

	//A에 복사
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			A[i][j] = tmpA[i][j];
		}
	}
}

void sortingC() {
	int maxvalue;
	maxvalue = row;
	memset(tmpA, 0, sizeof(tmpA));
	//열 정렬
	for (int i = 1; i <= column; i++) {
		int tmp[101] = { 0, };
		vector<pair<int, int>> tmpsort;
		tmpsort.push_back({ 0,0 });
		for (int j = 1; j <= row; j++) {
			tmp[A[j][i]] += 1;
		}
		//페어에 넣기
		for (int n = 1; n <= 100; n++) {
			if (tmp[n] > 0) {
				//cout << i << ", " << n << " : " << tmp[n] << "\n";
				tmpsort.push_back({ tmp[n],n });
			}
		}
		sort(tmpsort.begin(), tmpsort.end());
		int size = tmpsort.size();
		maxvalue = max(2 * (size - 1), maxvalue);
		for (int n = 1; n < size; n++) {
			if (n > 50)
				break;
			tmpA[2 * n - 1][i] = tmpsort[n].second;
			tmpA[2 * n][i] = tmpsort[n].first;
		}
	}
	row = maxvalue;

	//A에 복사
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			A[i][j] = tmpA[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> r >> c >> k;
	
	for (int i = 1; i < 4; i++)
		for (int j = 1; j < 4; j++)
			cin >> A[i][j];

	int resulttime = 0;
	while (resulttime <= 100) {
		if (A[r][c] == k)
			break;
		if(row >= column)
			sortingR();
		else
			sortingC();
		resulttime += 1;
		//for (int i = 1; i <= 10; i++) {
		//	for (int j = 1; j <= 10; j++) {
		//		cout << A[i][j] << " ";
		//	}
		//	cout << "\n";
		//}
	}

	if (resulttime == 101)
		cout << "-1\n";
	else
		cout << resulttime << "\n";
	//for (int i = 1; i <= 10; i++) {
	//	for (int j = 1; j <= 10; j++) {
	//		cout << A[i][j] << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << row << " " << column << "\n";
	return 0;
}