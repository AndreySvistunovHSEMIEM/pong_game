#include <stdio.h>

void show_score(int score_first, int score_second) {
    int row = 1;
    while (row <= 6) {
        int col = 0;
        while (col <= 79) {
            if (row == 1 || row == 5) {
                if (col == 0) {
                    printf("|");
                } else if (col == 79) {
                    printf("|\n");
                } else {
                    printf("-");
                }
            } else if (row == 3 && (col == 15 || col == 55)) {
                (col == 15) ? printf("User 1: %d", score_first) : printf("User 2: %d", score_second);
                col = (col == 15) ? ((score_first > 9) ? col + 9 : col + 8)
                                  : ((score_second > 9) ? col + 9 : col + 8);
            } else if (row == 3 && col == 55) {
                printf("User 2: %d", score_second);
                col += 8;
                col = (score_first > 9) ? col + 1 : col;
            } else if (col == 0 || col == 39 || col == 79) {
                (col == 79) ? printf("|\n") : printf("|");
            } else {
                printf(" ");
            }
            col += 1;
        }
        row += 1;
    }
}

void show_screen(int rocket_r, int rocket_l, int x_ball, int y_ball, int score_first, int score_second) {
    show_score(score_first, score_second);
    for (int row = 1; row <= 25; row += 1) {
        for (int col_ = 1; col_ <= 80; col_ += 1) {
            if (row == y_ball && col_ == x_ball) {
                printf("o");
            } else if (col_ == 79 && (row == rocket_r + 1 || row == rocket_r || row == rocket_r - 1)) {
                printf("|");
            } else if (col_ == 2 && (row == rocket_l + 1 || row == rocket_l || row == rocket_l - 1)) {
                printf("|");
            } else if (row == 1 || row == 25) {
                if (col_ == 80) {
                    printf("|\n");
                } else if (col_ == 1) {
                    printf("|");
                } else {
                    printf("-");
                }
            } else {
                if (col_ == 1 || col_ == 40) {
                    printf("|");
                } else if (col_ == 80) {
                    printf("|\n");
                } else {
                    printf(" ");
                }
            }
        }
    }
}

int move_ball_x(int x_ball, int flag_x) { return (flag_x) ? x_ball - 1 : x_ball + 1; }

int move_ball_y(int y_ball, int flag_y) {
    return (flag_y) ? (y_ball - 1 > 1 ? y_ball - 1 : y_ball + 1)
                    : (y_ball + 1 < 25 ? y_ball + 1 : y_ball - 1);
}

int score(int rocket_l, int rocket_r, int x_ball, int y_ball) {
    if ((x_ball == 3 && (y_ball == rocket_l - 1 || y_ball == rocket_l || y_ball == rocket_l + 1)) ||
        (x_ball == 78 && (y_ball == rocket_r - 1 || y_ball == rocket_r || y_ball == rocket_r + 1))) {
        return -2;
    } else {
        if (x_ball == 2) {
            return 0;
        } else if (x_ball == 79) {
            return 1;
        } else {
            return -1;
        }
    }
}

int change(int left_or_right_rocket, char left_or_right_symbol) {
    if (left_or_right_symbol == 'z' || left_or_right_symbol == 'm') {
        return left_or_right_rocket < 23 ? left_or_right_rocket + 1 : left_or_right_rocket;
    } else {
        return left_or_right_rocket > 3 ? left_or_right_rocket - 1 : left_or_right_rocket;
    }
}

void clearing() { printf("\033[2J\033[H"); }

void congratulations(int c) {
    if (c == 1) {
        printf("*****************************************\n");
        printf("*                                       *\n");
        printf("*       Congratulations User 1!         *\n");
        printf("*                                       *\n");
        printf("*****************************************\n");
    } else {
        printf("*****************************************\n");
        printf("*                                       *\n");
        printf("*       Congratulations User 2!         *\n");
        printf("*                                       *\n");
        printf("*****************************************\n");
    }
}
int main() {
    int rocket_r = 13, rocket_l = 13, x_ball = 40, y_ball = 13, flag_x = 1, flag_y = 1, score_first = 0,
        score_second = 0;
    while (score_first < 21 && score_second < 21) {
        show_screen(rocket_r, rocket_l, x_ball, y_ball, score_first, score_second);
        char input_char = getchar();
        while (getchar() != '\n');
        rocket_r = (input_char == 'k' || input_char == 'm') ? change(rocket_r, input_char) : rocket_r;
        rocket_l = (input_char == 'a' || input_char == 'z') ? change(rocket_l, input_char) : rocket_l;
        x_ball = move_ball_x(x_ball, flag_x);
        int prev_y_ball = y_ball;
        y_ball = move_ball_y(y_ball, flag_y);
        flag_y = (flag_y == 1 && prev_y_ball < y_ball) || (flag_y == 0 && prev_y_ball > y_ball)
                     ? ((flag_y) ? 0 : 1)
                     : flag_y;
        if (x_ball == 2 && (y_ball == rocket_l || y_ball == rocket_l - 1 || y_ball == rocket_l + 1)) {
            x_ball += 1;
        }
        if (x_ball == 79 && (y_ball == rocket_r || y_ball == rocket_r - 1 || y_ball == rocket_r + 1)) {
            x_ball -= 1;
        }
        int check_score = score(rocket_l, rocket_r, x_ball, y_ball);
        if (check_score == -2) {
            flag_x = (flag_x) ? 0 : 1;
        } else if (check_score == 1 || check_score == 0) {
            score_first = (check_score == 1) ? score_first + 1 : score_first;
            score_second = (check_score == 0) ? score_second + 1 : score_second;
            rocket_r = 13;
            rocket_l = 13;
            x_ball = 40;
            y_ball = 13;
            flag_x = (flag_x) ? 0 : 1;
            flag_y = (flag_y) ? 0 : 1;
        }
        if (((x_ball == 3 && flag_x == 1) &&
             (y_ball == rocket_l - 1 || y_ball == rocket_l || y_ball == rocket_l + 1)) ||
            (x_ball == 2 && flag_x == 1)) {
            flag_x = 0;
        } else if ((x_ball == 78 && flag_x == 0 &&
                    (y_ball == rocket_r - 1 || y_ball == rocket_r || y_ball == rocket_r + 1)) ||
                   (x_ball == 79 && flag_x == 0)) {
            flag_x = 1;
        }
        clearing();
    }
    (score_first == 21) ? congratulations(1) : congratulations(2);
    return 0;
}
// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
