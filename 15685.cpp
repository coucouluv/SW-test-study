#include <iostream>
#include <stack>
using namespace std;

int zone[101][101];
int N;
int y[] = { 0, -1, 0, 1 };
int x[] = { 1, 0, -1, 0 };

int find_square() {
	int ret = 0;
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			if (i == 100 || j == 100) continue;
			if (zone[i][j] == 1) {
				if (zone[i][j + 1] && zone[i + 1][j + 1] && zone[i + 1][j]) ret += 1;
			}
		}
	}
	return ret;
}

int main() {

	cin >> N;

	int a, b, c, d;
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> c >> d;
		stack <int> dragon;
		stack <int> tmp;
		zone[b][a] = 1;
		zone[b + y[c]][a + x[c]] = 1; //0세대
		tmp.push(c);
		int cury = b + y[c], curx = a + x[c];

		for (int j = 0; j < d; j++) {  //1~~10세대
			dragon = tmp;
			while (!dragon.empty()) {
				int direct = dragon.top();
				dragon.pop();
				direct = (direct + 1) % 4;
				cury = cury + y[direct];
				curx = curx + x[direct];
				zone[cury][curx] = 1;
				tmp.push(direct);
			}
		}
	}
	cout << find_square() << "\n";

	return 0;
}

