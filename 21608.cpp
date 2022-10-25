#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
	int y;
	int x;
	int love[4];
};

using namespace std;
int classroom[22][22]; //교실
Student student[401]; //n번째 학생 정보
int N;
int happy = 0;
int happynum[5] = { 0,1,10,100,1000 };
int y[] = {0,0,-1,1};
int x[] = {-1,1,0,0};
int cnt; //전체 학생 수
bool compare(pair<pair <int, int>, pair <int,int> > a, pair<pair <int, int>, pair <int, int> > b) {
	if (a.first.first == b.first.first) { //친한 친구 인접 칸 동일
		if (a.first.second == b.first.second) { // 빈칸 동일
			if (a.second.first == b.second.first)
				return a.second.second < b.second.second;
			return a.second.first < b.second.first;
		}
		return a.first.second > b.first.second;
	}
	return a.first.first > b.first.first;
}

void movestudent(int me) {
	
	//친한 친구 수, 좌표
	vector <pair<pair <int,int>, pair <int, int>> > tmpseat;
	int close = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int closeseat = 0, emptyseat = 0;
			if (classroom[i][j] == 0) {
				for (int n = 0; n < 4; n++) {
					int dy = i + y[n];
					int dx = j + x[n];
					if (dy <= 0 || dy > N || dx <= 0 || dx > N) continue;
					int who = classroom[dy][dx];
					if (who > 0) {
						if (who == student[me].love[0] || who == student[me].love[1] || who == student[me].love[2] || who == student[me].love[3])
							closeseat += 1;
					}
					else
						emptyseat += 1;
				}
				if(close <= closeseat)
					tmpseat.push_back({ {closeseat, emptyseat}, {i, j} });
			}
			close = max(close, closeseat);
		}
	}
	sort(tmpseat.begin(), tmpseat.end(), compare); //정렬 후
	//cout << "best seat : " << tmpseat[0].second.first << ", " << tmpseat[0].second.second << "\n";
	classroom[tmpseat[0].second.first][tmpseat[0].second.second]= me;
	student[me].y = tmpseat[0].second.first;
	student[me].x = tmpseat[0].second.second;
}

void sumhappy() {
	for (int i = 1; i <= cnt; i++) {
		int close = 0;
		for (int n = 0; n < 4; n++) {
			int dy = student[i].y + y[n];
			int dx = student[i].x + x[n];
			if (dy <= 0 || dy > N || dx <= 0 || dx > N) continue;
			int who = classroom[dy][dx];
			if (who > 0) {
				if (who == student[i].love[0] || who == student[i].love[1] || who == student[i].love[2] || who == student[i].love[3])
					close += 1;
			}
		}
		happy += happynum[close];
	}
	cout << happy;
}
int main() {

	cin >> N;
	
	cnt = N * N;
	for (int i = 1; i <= cnt; i++) {
		int num;
		cin >> num;
		for (int j = 0; j < 4; j++) {
			cin >> student[num].love[j];
		}
		movestudent(num);
	}
	
	sumhappy();

	return 0;
}