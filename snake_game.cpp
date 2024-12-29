#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>

using namespace std;

int length = 2;
int lengthmax = 2; // Controls snake's length

int x1 = 30;
int y1 = 170; // Snake's location

char direc = '-';
char last = '-'; // Direction

bool playing = true; // Player status

int fruitx;
int fruity;
bool eaten = false; // Fruit status

vector<int> snakex;
vector<int> snakey; // Snake's tail coordinates

int i = 1;
int imax = 0; // Loop control

char score[50];
int score1 = 0; // Player's score

void fruit();
void graphic();
void move();
void start();
void update(); // Function declarations

int main() {
    start();

    while (playing) {
        update();

        if (x1 >= 340 || x1 < 0 || y1 >= 340 || y1 < 0) {
            playing = false; // Check collision with walls
        }

        for (i = lengthmax; i > 0; i--) {
            if (x1 == snakex[i] && y1 == snakey[i]) {
                playing = false; // Check collision with itself
            }
        }
    }

    if (!playing) {
        cleardevice();
        outtextxy(70, 170, "YOU LOST, YOUR ");
        outtextxy(188, 170, score);
        getch();
        return 0; // End game
    }
}

void start() {
    sprintf(score, "SCORE : %d ", score1);

    srand(time(NULL));
    initwindow(350, 354, "SnakeGame");

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(0, 0, 340, 10);
    floodfill(5, 5, GREEN);

    setcolor(WHITE);
    outtextxy(10, 0, score);

    fruitx = (rand() % 34) * 10;
    fruity = (rand() % 34) * 10;

    if (fruity == 0) {
        fruity += 10;
    }

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    rectangle(fruitx, fruity, fruitx + 10, fruity + 10);
    floodfill(fruitx + 5, fruity + 5, RED);
}

void update() {
    sprintf(score, "SCORE : %d ", score1);

    delay(150);

    snakex.push_back(x1);
    snakey.push_back(y1); // Update tail positions

    fruit();
    move();
    graphic();
}

void move() {
    if (kbhit()) {
        direc = getch();
    }

    if ((direc == 'w' && last == 's') || (direc == 's' && last == 'w') ||
        (direc == 'a' && last == 'd') || (direc == 'd' && last == 'a')) {
        direc = last;
    }

    last = direc;

    if (direc == 's') {
        y1 += 10;
    } else if (direc == 'a') {
        x1 -= 10;
    } else if (direc == 'w') {
        y1 -= 10;
    } else if (direc == 'd') {
        x1 += 10;
    }
}

void graphic() {
    cleardevice();

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(0, 0, 350, 10);
    floodfill(5, 5, GREEN);

    setcolor(WHITE);
    outtextxy(10, 0, score);

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    rectangle(fruitx, fruity, fruitx + 10, fruity + 10);
    floodfill(fruitx + 5, fruity + 5, RED);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(x1, y1, x1 + 10, y1 + 10);
    floodfill(x1 + 5, y1 + 5, WHITE);

    for (int i = lengthmax; i > 0; i--) {
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        rectangle(snakex[i], snakey[i], snakex[i] + 10, snakey[i] + 10);
        floodfill(snakex[i] + 5, snakey[i] + 5, WHITE);
    }

    imax++;
    i = imax;
}

void fruit() {
    if (x1 == fruitx && y1 == fruity) {
        eaten = true;
    }

    if (eaten) {
        eaten = false;
        lengthmax++;
        score1++;
        fruitx = (rand() % 34) * 10;
        fruity = (rand() % 34) * 10;

        for (int i = lengthmax; i > 0; i--) {
            if (fruitx == snakex[i] && fruity == snakey[i]) {
                fruitx = (rand() % 34) * 10;
                fruity = (rand() % 34) * 10;
            }
        }

        if (fruity == 0) {
            fruity = 10;
        }

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        rectangle(fruitx, fruity, fruitx + 10, fruity + 10);
        floodfill(fruitx + 5, fruity + 5, RED);
    }
}
