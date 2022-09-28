#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int result = 0;
int N, M;
int y[] = {-1, 1, 0, 0};
int x[] = {0, 0, -1, 1};
//int board[8][8];
queue <pair <int, int>> q;

int findsafe(vector<vector<int>> board) {
    queue <pair <int, int>> que;
    que = q;
    while(!que.empty()) {
        int dy = que.front().first;
        int dx = que.front().second;
        que.pop();
        for(int i = 0; i < 4; i++) {
            int cy = dy + y[i];
            int cx = dx + x[i];
            if(cy < 0 || cy >= N || cx < 0 || cx >= M) continue;
            if(board[cy][cx] == 0) {
               board[cy][cx] = 2;
               que.push(make_pair(cy, cx));
            }

        }
    }
    int ret = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(board[i][j] == 0)
                ret += 1;
        }
    }
    return ret;

}

void resolution(int cnt, vector<vector<int>> board) {
    if(cnt == 3) {
        int tmp = findsafe(board);
        //cout << tmp << endl;
        if(result < tmp)
            result = tmp;
        return;
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(board[i][j] == 0) {
                board[i][j] = 1;
                resolution(cnt+1,board);
                board[i][j] = 0;
            }
        }
    }

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    vector<vector<int>> board(8, vector<int>(8));
    //vector<pair <int, int>> p;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
            if(board[i][j] == 2) {
                q.push(make_pair(i,j));
            }
        }
    }
    resolution(0, board);

    cout << result << "\n";
    return 0;
}
