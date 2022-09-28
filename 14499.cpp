#include <iostream>

using namespace std;

int map[20][20];
int dice[6];
int x, y, N, M;

void move_dice(int dirx, int diry) {

    x = x + dirx;
    y = y + diry;

    if(map[y][x] == 0) {
        map[y][x] = dice[5];
    }
    else {
        dice[5] = map[y][x];
        map[y][x] = 0;
    }
    cout << dice[0] << "\n";
}

void dice_right() {
    int a, b, c, d;
    a = dice[0];
    b = dice[2];
    c = dice[3];
    d = dice[5];

    dice[0] = c;
    dice[2] = a;
    dice[3] = d;
    dice[5] = b;

}

void dice_left() {
    int a, b, c, d;
    a = dice[0];
    b = dice[2];
    c = dice[3];
    d = dice[5];

    dice[0] = b;
    dice[2] = d;
    dice[3] = a;
    dice[5] = c;
}

void dice_up() {
    int a, b, c, d;
    a = dice[0];
    b = dice[1];
    c = dice[4];
    d = dice[5];

    dice[0] = c;
    dice[1] = a;
    dice[4] = d;
    dice[5] = b;

}

void dice_down() {
    int a, b, c, d;
    a = dice[0];
    b = dice[1];
    c = dice[4];
    d = dice[5];

    dice[0] = b;
    dice[1] = d;
    dice[4] = a;
    dice[5] = c;
}

int main() {

    int K;

    cin >> N >> M >> y >> x >> K;

    for(int i = 0; i < N; i++)  {
        for(int j = 0; j < M; j++)
            cin >> map[i][j];
    }
    int direct;
    for(int i = 0; i < K; i++) {
        cin >> direct;
        switch(direct){
        case 1:
            if(x < M-1) {
                dice_right();
                move_dice(1, 0);
            }
            break;
        case 2:
            if(x > 0) {
                dice_left();
                move_dice(-1, 0);
            }
            break;
        case 3:
            if(y > 0) {
                dice_up();
                move_dice(0, -1);
            }
            break;
        case 4:
            if(y < N-1) {
                dice_down();
                move_dice(0, 1);
            }
            break;
        default:
            break;
        }
    }

    return 0;
}
