
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include <errno.h> 


void hideCursor(){
    printf("\e[?25l");
}

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

#define ROWS 10 // 2-9
#define COLS 30 // 2-29
#define WALL '#'

typedef struct{
    int X;
    int Y;
}Snake;


#define clrscr() printf("\e[1;1H\e[2J")
void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}



void drawBoundaries(){
    for(int row = 0; row < ROWS+2;row++){
        for(int col = 0; col < COLS+2; col++){
            if(row == 0 || row == ROWS+1 || col == 0 || col == COLS+1){
                printf("%c",WALL);         
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
        
    }
}


void drawSnake(Snake snake){
    gotoxy(snake.X,snake.Y);
    printf("O");
}

void clearSnake(Snake snake){
    gotoxy(snake.X,snake.Y);
    printf(" ");
}


typedef enum {
    KeyboardDir_Left,    
    KeyboardDir_Right,
    KeyboardDir_Up,
    KeyboardDir_Down,
}KeyboardDir;


int kbhit2()
{
    return _kbhit();
}

int getNextKeyboardAction(){
    if(kbhit2()){
        //gotoxy(0,ROWS+3);
        //printf("Ange vad den ska göra:");
        char ch = getch();
        //printf("%d",ch);
        return ch;
    }
    return 0;
}



void moveSnake(Snake *snake,KeyboardDir direction){
    if(direction == KeyboardDir_Up){
        if(snake->Y == 2) snake->Y = ROWS+1;
        else snake->Y--;
    }
    if(direction == KeyboardDir_Down){
        if(snake->Y == ROWS+1) snake->Y = 2;
        else snake->Y++;
    }
    if(direction == KeyboardDir_Left){
        if(snake->X == 2) snake->X = COLS+1;
        else snake->X--;
    }
    if(direction == KeyboardDir_Right){
        if(snake->X == COLS+1) snake->X = 2;
        else snake->X++;
    }


}

void food(Snake *snake){

srand(time(NULL));
int randy = rand() % 27;
int y = randy + 2;

srand(time(NULL));
int randx = rand() % 7;
int x = randx + 2;
gotoxy(y,x);
printf("*");

if( x == snake -> X) {return;}
if( y == snake -> Y) {return;}
}

int main(){
    Snake snake;
    snake.X = 5; 
    snake.Y = 5;
    clrscr();
    hideCursor();
    drawBoundaries();
    food(&snake);
    while(1){
        //clrscr();
        //drawBoundaries(1);
        clearSnake(snake);
        gotoxy(0,0);
        char ch = getNextKeyboardAction();
        if(ch == 'w') moveSnake(&snake,KeyboardDir_Up);
        else if(ch == 's') moveSnake(&snake,KeyboardDir_Down);
        else if(ch == 'a') moveSnake(&snake,KeyboardDir_Left);
        else if(ch == 'd') moveSnake(&snake,KeyboardDir_Right);
        drawSnake(snake);
        msleep(250);
    }
    return 1;
}

