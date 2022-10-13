#include <iostream>
#include <vector>
#include <queue> 
using namespace std;

int N, K;

int A[201]; // 각 칸의 내구도
queue <int> robot;
int robotindex[201];
int startline, endline; //1번 위치, N번 위치
int findzero = 0; //내구도 0 개수
bool move() {
	//컨베이어 벨트 이동
	if (startline == 1)
		startline = 2 * N;
	else
		startline -= 1;
	if (endline == 1)
		endline = 2 * N;
	else
		endline -= 1;

	//로봇 이동
	int size = robot.size();
	for (int i = 0; i < size; i++) {
		int preindex = robot.front();
		int curindex = preindex;
		robotindex[preindex] = 0;
		robot.pop();
		//이동 전에 로봇이 N 위치에 있는지 확인
		if (preindex == endline) continue;

		if (curindex == 2 * N)
			curindex = 1;
		else
			curindex += 1;
		//이동 가능
		if (A[curindex] > 0 && robotindex[curindex] == 0) {

			A[curindex] -= 1;
			if (A[curindex] == 0)
				findzero += 1;
			if (curindex == endline) continue;
			robotindex[curindex] = 1;
			robot.push(curindex);
		}
		//이동 못하면 가만히
		else {
			robotindex[preindex] = 1;
			robot.push(preindex);
		}
		
		if (findzero >= K)
			return false;
	}
	//올리는 위치에 로봇 올림
	if (A[startline] > 0 && robotindex[startline] == 0) {
		robot.push(startline);
		A[startline] -= 1;
		robotindex[startline] = 1;
		if (A[startline] == 0)
			findzero += 1;
	}
	return findzero < K;
}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> K;

	for (int i = 1; i <= 2 * N; i++) {
		cin >> A[i];
	}
	//처음 세팅
	startline = 1;
	endline = N;
	int result = 1;
	while (1) {
		if (!move()) {
			break;
		}
		result += 1;
	}
	cout << result << "\n";
	return 0;
}