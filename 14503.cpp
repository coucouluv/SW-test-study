#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
int place[51][51];
int y[] = {-1,0,1,0};
int x[] = {0,1,0,-1};
int result = 0;
int main() {

    cin >> N >> M;

    int startx, starty, d;

    cin >> starty >> startx >> d;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> place[i][j];

    queue <pair< pair <int, int>, int> > robot;
    robot.push({{starty,startx},d});
    place[starty][startx] = 2;
    result += 1;
    while(!robot.empty()) {
        int cury = robot.front().first.first;
        int curx = robot.front().first.second;
        int direc = robot.front().second;
        robot.pop();

        bool clean = false;
        int dy, dx;
        for(int i = 0; i < 4; i++) {
            int curdirec = (direc+3-i)%4;
            dy = y[curdirec] + cury;
            dx = x[curdirec] + curx;
            if(dy < 0 || dy >= N || dx < 0 || dx >= M) continue;
            if(place[dy][dx] == 0) {
                place[dy][dx] = 2;
                result += 1;
                robot.push({{dy,dx},curdirec});
                clean = true;
                break;
            }
        }
        if(clean == false) {
            int backdirec = (direc+2)%4;
            dy = y[backdirec] + cury;
            dx = x[backdirec] + curx;
            if(dy >= 0 && dy < N && dx >= 0 && dx < M) {
                if(place[dy][dx] != 1) {
                    robot.push({{dy,dx},direc});
                }
            }
        }
    }

    cout << result << "\n";
    return 0;
}
