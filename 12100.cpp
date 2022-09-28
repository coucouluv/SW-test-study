#include <iostream>
#include <queue>
#include <vector>
using namespace std;


int result = 0;
int N;
typedef int(*Result)[20];

vector<vector<int>> up(vector<vector<int>> tmp) {

    queue <int> que;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(tmp[j][i])
                que.push(tmp[j][i]);
            tmp[j][i] = 0;
        }
        int index = 0;
        while(!que.empty()) {
            int value = que.front();
            que.pop();
            if(tmp[index][i] == value) {
                tmp[index][i] += value;
                index++;
            }
            else if(tmp[index][i] == 0) {
                tmp[index][i] = value;
            }
            else{
                index++;
                tmp[index][i] = value;
            }
        }
    }
    return tmp;
}


vector<vector<int>> down(vector<vector<int>> tmp) {

    queue <int> que;
    for(int i = 0; i < N; i++) {
        for(int j = N-1; j >= 0; j--) {
            if(tmp[j][i])
                que.push(tmp[j][i]);
            tmp[j][i] = 0;
        }
        int index = N-1;
        while(!que.empty()) {
            int value = que.front();
            que.pop();
            if(tmp[index][i] == value) {
                tmp[index][i] += value;
                index--;
            }
            else if(tmp[index][i] == 0) {
                tmp[index][i] = value;
            }
            else{
                index--;
                tmp[index][i] = value;
            }
        }
    }
    return tmp;
}

vector<vector<int>> left(vector<vector<int>> tmp) {

    queue <int> que;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(tmp[i][j])
                que.push(tmp[i][j]);
            tmp[i][j] = 0;
        }
        int index = 0;
        while(!que.empty()) {
            int value = que.front();
            que.pop();
            if(tmp[i][index] == value) {
                tmp[i][index] += value;
                index++;
            }
            else if(tmp[i][index] == 0) {
                tmp[i][index] = value;
            }
            else{
                index++;
                tmp[i][index] = value;
            }
        }
    }
    return tmp;
}

vector<vector<int>> right(vector<vector<int>> tmp) {

    queue <int> que;
    for(int i = 0; i < N; i++) {
        for(int j = N-1; j >= 0; j--) {
            if(tmp[i][j])
                que.push(tmp[i][j]);
            tmp[i][j] = 0;
        }
        int index = N-1;
        while(!que.empty()) {
            int value = que.front();
            que.pop();
            if(tmp[i][index] == value) {
                tmp[i][index] += value;
                index--;
            }
            else if(tmp[i][index] == 0) {
                tmp[i][index] = value;
            }
            else{
                index--;
                tmp[i][index] = value;
            }
        }
    }
    return tmp;
}

int findmax(vector<vector<int>> tmp) {
    int ret = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(tmp[i][j] > ret)
                ret = tmp[i][j];
        }
    }
    return ret;

}
void resolution(int index, vector<vector<int>> tmp) {

    //최대값 갱신하기
    if(index == 5) {
        int maxv = findmax(tmp);
        if(maxv > result)
            result = maxv;
        return;
    }

    resolution(index+1, up(tmp));
    resolution(index+1, down(tmp));
    resolution(index+1, left(tmp));
    resolution(index+1, right(tmp));

}

int main() {

    cin >> N;

    vector<vector<int>> board(20, vector<int>(20));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cin >> board[i][j];
    }

    resolution(0, board);

    cout << result;
    return 0;
}
