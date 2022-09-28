#include <iostream>

using namespace std;

int N, M;
int paper[501][501];
int result = 0;
int x[] = {0,0,1,-1};
int y[] = {1,-1,0,0};
int visited[501][501];

void solution(int i, int j, int cnt, int sum) {
    if(cnt == 4) {
        result = max(result, sum);
        return;
    }

    for(int n = 0; n < 4; n++) {
        int dy = i + y[n];
        int dx = j + x[n];
        if(dy < 0 || dy >= N || dx < 0 || dx >= M) continue;
        if(visited[dy][dx] == 0) {
            visited[dy][dx] = 1;
            solution(dy, dx, cnt+1, sum+paper[dy][dx]);
            visited[dy][dx] = 0;
        }
    }

}
void solution_except(int i, int j, int sum) {

    int minv = 1001;
    for(int n = 0; n < 4; n++) {
        int dy = i + y[n];
        int dx = j + x[n];
        if(dy < 0 || dy >= N || dx < 0 || dx >= M) continue;
        minv = min(minv, paper[dy][dx]);
        sum += paper[dy][dx];
    }
    if(i > 0 && i < N-1 && j > 0 && j < M-1)
        sum -= minv;
    result = max(result, sum);
    return ;
}

int main() {

    cin >> N >> M;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> paper[i][j];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(visited[i][j] == 0) {
               visited[i][j] = 1;
               solution(i, j, 1, paper[i][j]);
               solution_except(i, j, paper[i][j]);
               visited[i][j] = 0;
            }
        }
    }

    cout << result << "\n";
    return 0;
}
