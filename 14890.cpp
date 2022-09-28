#include <iostream>
#include <cstdlib>
using namespace std;

int N, L;
int maps[101][101];
int maps2[101][101];
int load = 0;

void solution_row(int i) {

    bool possible = true;
    int visited[101] = {0,};
    for(int j = 0; j < N-1; j++) {
        if( abs(maps[i][j]-maps[i][j+1]) > 1) {
            possible = false;
            break;
        }
        if(maps[i][j] > maps[i][j+1]) { //if down
            int tmp = maps[i][j+1];
            for(int n = j+2; n < L+j+1; n++) {
                if(n >= N || tmp != maps[i][n]) {
                    possible = false;
                    break;
                }
            }
            if(possible) { // i'm possible to create slope!
                for(int n = j+1; n < L+j+1; n++)
                    visited[n] = 1; //
            }
            else {
                break;
            }
        }
        if(maps[i][j] < maps[i][j+1]) { //if up
            int tmp = maps[i][j];
            for(int n = j; n > j-L; n--) {
                if(n < 0 || tmp != maps[i][n] || visited[n]) {
                    possible = false;
                    break;
                }
            }
            if(!possible) {
                break;
            }
        }

    }
    if(possible)
        load += 1;
    return;
}

void solution_col(int i) {

    bool possible = true;
    int visited[101] = {0,};
    for(int j = 0; j < N-1; j++) {
        if( abs(maps2[i][j]-maps2[i][j+1]) > 1) {
            possible = false;
            break;
        }
        if(maps2[i][j] > maps2[i][j+1]) { //if down
            int tmp = maps2[i][j+1];
            for(int n = j+2; n < L+j+1; n++) {
                if(n >= N || tmp != maps2[i][n]) {
                    possible = false;
                    break;
                }
            }
            if(possible) { // i'm possible to create slope!
                for(int n = j+1; n < L+j+1; n++)
                    visited[n] = 1; //
            }
            else {
                break;
            }
        }
        if(maps2[i][j] < maps2[i][j+1]) { //if up
            int tmp = maps2[i][j];
            for(int n = j; n > j-L; n--) {
                if(n < 0 || tmp != maps2[i][n] || visited[n]) {
                    possible = false;
                    break;
                }
            }
            if(possible == false) {
                break;
            }
        }

    }
    if(possible)
        load += 1;
    return;
}

int main() {

    cin >> N >> L;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> maps[i][j];
            maps2[j][i] = maps[i][j];
        }
    }

    for(int i = 0; i < N; i++) {
        solution_row(i);
        solution_col(i);
    }
    cout << load << "\n";
    return 0;
}
