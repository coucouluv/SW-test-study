#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int visited[10][10][10][10] = {0, };
int result = -1;
char board[11][11];

struct BALL {
    int ry,rx,by,bx,count;

};

int main() {


    int N, M;

    cin >> N >> M;



    BALL start;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'R') {
                start.ry = i;
                start.rx = j;
            }
            if(board[i][j] == 'B') {
                start.by = i;
                start.bx = j;
            }
        }
    }
    start.count = 0;
    visited[start.ry][start.rx][start.by][start.bx] = 1;

    queue <BALL> que;
    que.push(start);

    while(!que.empty()){
        BALL cur = que.front();
        que.pop();
        if(cur.count>10) break;
        if(board[cur.ry][cur.rx]=='O' && board[cur.by][cur.bx]!='O') {//최적값찾은경우
            result = cur.count;
            break;
        }

        for(int dir=0; dir<4; dir++){
            int next_ry = cur.ry;
            int next_rx = cur.rx;
            int next_by = cur.by;
            int next_bx = cur.bx;

            while (1) {
                if (board[next_ry][next_rx] != '#' && board[next_ry][next_rx] != 'O') {
                    next_ry += dy[dir], next_rx += dx[dir];
                }
                else {
                    if (board[next_ry][next_rx] == '#') {
                        next_ry -= dy[dir], next_rx -= dx[dir];
                    }
                    break;
                }
            }

            while (1) {
                if (board[next_by][next_bx] != '#' && board[next_by][next_bx] != 'O') {
                    next_by += dy[dir], next_bx += dx[dir];
                }
                else {
                    if (board[next_by][next_bx] == '#') {
                        next_by -= dy[dir], next_bx -= dx[dir];
                    }
                    break;
                }
            }


            if(next_rx==next_bx && next_ry==next_by){
                if(board[next_ry][next_rx]!='O'){
                    int red_dist = abs(next_ry - cur.ry)+abs(next_rx-cur.rx);
                    int blue_dist = abs(next_by - cur.by)+abs(next_bx-cur.bx);
                    if(red_dist>blue_dist){
                            next_ry-=dy[dir];
                            next_rx-=dx[dir];
                    }
                    else{
                            next_by-=dy[dir];
                            next_bx-=dx[dir];
                    }
                }
            }
            if(visited[next_ry][next_rx][next_by][next_bx]==0){
                visited[next_ry][next_rx][next_by][next_bx]=1;
                BALL next;
                next.ry = next_ry;
                next.rx = next_rx;
                next.by = next_by;
                next.bx = next_bx;
                next.count = cur.count+1;
                que.push(next);
            }
        }

    }
    cout << result << "\n";
    return 0;
}
