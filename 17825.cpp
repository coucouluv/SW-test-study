#include <iostream>
//#include <stdio.h> //freopen 함수
using namespace std;
const int END = 41;
int boardred[42][1];
int boardblue[42][1];
int number[10]; //주사위 수
int horse[4] = {0,}; 
bool horseblue[4] = {false, }; //말이 빨강인지 파랑인지
int result = 0;
int arrive = 0; //도착한 점수판 값
void setting() {
	//시작시점 0
	//빨간 화살표 여기 30은 30임
	for (int i = 0; i < 40; i += 2) {
		boardred[i][0] = i + 2;
	}	
	//도착지점 41
	boardred[40][0] = END;
	
	//파란 화살표
	//30이 두번 존재 0 -> 25다음인 거는 29러, 1-> 28다음인거는 30으로
	for (int i = 10; i < 19; i += 3) {
		boardblue[i][0] = i + 3;
	}
	boardblue[19][0] = 25;

	for (int i = 20; i < 24; i += 2) {
		boardblue[i][0] = i + 2;
	}
	boardblue[24][0] = 25;

	boardblue[30][0] = 28;
	for (int i = 28; i >= 26; i--) {
		boardblue[i][0] = i - 1;
	}

	boardblue[25][0] = 29;
	boardblue[29][0] = 35;
	boardblue[35][0] = 40;
	boardblue[40][0] = END;
}
bool move(int num, int cnt) {
	if (horse[num] == END)
		return false;
	int tmp = horse[num]; //이동하기 전 위치
	 
	//파란화살표
	if (horseblue[num]) {
		for (int i = 0; i < cnt; i++) {
			if (tmp == END) break;
			tmp = boardblue[tmp][0];
		}
	}
	else { //빨간화살표
		for (int i = 0; i < cnt; i++) {
			if (tmp == END) break;
			tmp = boardred[tmp][0];
		}
	}
	for (int i = 0; i < 4; i++) {
		if (num != i) {
			if (tmp != END && tmp == horse[i]) {
				if (tmp == 40 || tmp == 10 || tmp == 20 || tmp == 30)
					return false;
				if (horseblue[num] == horseblue[i]) //같은 판에 존재
					return false;
			}				
		}
	}
	horse[num] = tmp;
	// 10, 20, 30은 파란 화살표 판으로 설정
	if (tmp == 10 || tmp == 20 || tmp == 30) {
		horseblue[num] = true;
	}
	//도착 장소 값 저장
	arrive = tmp;
	if (arrive == END) arrive = 0;
	return true;
}

void solution(int cnt, int sum, int resetnum, bool resetblue) {
	if (cnt == 10) {
		result = max(result, sum);
		return;
	}
	for (int i = 0; i < 4; i++) {
		resetnum = horse[i];
		resetblue = horseblue[i];
		if (move(i, number[cnt])) { //이동 가능한지 여부 확인
			if(arrive == 29)
				solution(cnt + 1, sum + arrive+1, resetnum, resetblue);
			else
				solution(cnt + 1, sum + arrive, resetnum, resetblue);
			//이전값으로 돌려놓기
			horse[i] = resetnum;
			horseblue[i] = resetblue;
		}
	}
}
void print() {
	cout << "red" << "\n";
	for (int i = 0; i < 42; i++) {
		cout << i << ": " << boardred[i][0] << "\n";
	}
	cout << "blue" << "\n";
	for (int i = 0; i < 42; i++) {
		cout << i << ": " << boardblue[i][0] << "\n";
	}
}

int main() {

	//시작 전 윷놀이 판 세팅
	setting();
	//print();

	for (int i = 0; i < 10; i++)
		cin >> number[i];
	solution(0, 0,0,0);
	cout << result << "\n";
	return 0;
}