#include <iostream>
#include <vector>
//#include <stdio.h> //freopen �Լ�
using namespace std;

struct Fish {
	int curx;
	int cury;
	int direct;
	bool live;
};

int y[] = {0,-1,-1,0,1,1,1,0,-1}; //�ݽð� +1
int x[] = {0,0,-1,-1,-1,0,1,1,1};
Fish fishes[17]; //����� ����
vector <vector <int>> space(4, vector<int>(4)); //����
int maxnum = 0;

void print() {

	cout << "\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << space[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void movefish() {
	for (int i = 1; i <= 16; i++) {
		//������� ����
		int dy = fishes[i].cury; // ���� ��ġ
		int dx = fishes[i].curx; 
		int direct = fishes[i].direct; // ���� ����
		if (fishes[i].live == false) continue;
		while (1) {  
			int cy = dy + y[fishes[i].direct];
			int cx = dx + x[fishes[i].direct];
			if (cy < 0 || cy >= 4 || cx < 0 || cx >= 4) { //���
				if (fishes[i].direct == 8)
					fishes[i].direct = 1;
				else
					fishes[i].direct = fishes[i].direct + 1;
			}
			else if (space[cy][cx] == -1) { //��� ��ġ��
				if (fishes[i].direct == 8)
					fishes[i].direct = 1;
				else
					fishes[i].direct = fishes[i].direct + 1;
			}
			else {	//�̵��� �� ���� 
				int swapfish = space[cy][cx];
				fishes[swapfish].cury = dy;
				fishes[swapfish].curx = dx;
				fishes[i].cury = cy;
				fishes[i].curx = cx;
				space[cy][cx] = i;
				space[dy][dx] = swapfish;
				break;
			}
			if (direct == fishes[i].direct) break;
		}
	}
}

void copyfish(struct Fish copy[], struct Fish original[]) {
	for (int i = 1; i <= 16; i++) {
		copy[i].cury = original[i].cury;
		copy[i].curx = original[i].curx;
		copy[i].direct = original[i].direct;
		copy[i].live = original[i].live;
	}
}

void moveshark(int sum, int dy, int dx , int direct) {
	
	maxnum = max(maxnum, sum);

	//�̵��ϱ� �� ���� �����ؾ��� �ֳĸ� ����� ����ü, �迭 �� �ٲ�,,,
	vector <vector <int>> tmp(4, vector<int>(4));
	Fish tmpfish[17];
	tmp = space;
	copyfish(tmpfish, fishes);

	//����� �̵�
	movefish();

	for (int i = 1; i <= 3; i++) {
		int cy = dy + y[direct] * i;
		int cx = dx + x[direct] * i;
		if (cy < 0 || cy >= 4 || cx < 0 || cx >= 4) continue;
		if (space[cy][cx] > 0) {
			//����� �Ա�
			int deadfish = space[cy][cx];
			space[cy][cx] = -1;
			space[dy][dx] = 0;
			fishes[deadfish].live = false;
			moveshark(sum + deadfish,cy,cx,fishes[deadfish].direct);

			//������� �ǵ�����
			space[dy][dx] = -1;
			space[cy][cx] = deadfish;
			fishes[deadfish].live = true;
		}
		
	}
	//����� ����ü, �迭 �ǵ�����
	space = tmp;
	copyfish(fishes,tmpfish);
	return;
}

int main() {

	int a, b; //a : ����� ��ȣ, b : ����
	int tmpdirect;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a >> b;
			if (i == 0 && j == 0) {
				tmpdirect = b;
				maxnum = a;
				fishes[a].live = false;
				space[i][j] = -1; //��� ��ġ
				continue;
			}
			space[i][j] = a;
			fishes[a].cury = i;
			fishes[a].curx = j;
			fishes[a].direct = b;
			fishes[a].live = true;
		}
	}

	moveshark(maxnum, 0,0,tmpdirect);

	cout << maxnum << "\n";
	return 0;
}