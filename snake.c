/**
 * 贪吃蛇
 *
 * 1.数据设计
 * 2.模块化设计
 * 3.实现过程
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  //光标设置API
#include <time.h>     //食物随机
#include <conio.h>    //键盘监控

//数据设计
/////////////////////////////////////
//    辅助定义

#define MAPHEIGHT 25//地图的高度
#define MAPWEIGHT 100//地图的宽度
#define SNAKESIZE 80

//食物的结构体
struct
{
    int x;
    int y;
} food;

//蛇的结构体
struct
{
    int x[SNAKESIZE];
    int y[SNAKESIZE];
    int len;        //蛇的长度
    int speed;      //蛇的速度
} snake;

//全局变量
int key = 'w';  //初始化移动方向
int changeFlag = 0;//蛇的变化的标记

//画地图
void drawMap()
{
    //1,确定范围
    for(int i = 0; i <= MAPHEIGHT; i++)
    {
        gotoxy(0,i);
        printf("#");
        gotoxy(MAPWEIGHT,i);
        printf("#");
    }

    for(int i = 0; i <= MAPWEIGHT; i+=2)
    {
        gotoxy(i,0);
        printf("#");
        gotoxy(i,MAPHEIGHT);
        printf("#");
    }


    //2,画出蛇的形状
    snake.len = 3;
    snake.speed = 200;
    //2.1,画出蛇头
    snake.x[0] = MAPWEIGHT / 2;
    snake.y[0] = MAPHEIGHT / 2;
    gotoxy(snake.x[0],snake.y[0]);
    printf("@");
    //2.2,画蛇的身体
    for(int k = 1; k < snake.len; k ++)
    {
        snake.x[k] = (MAPWEIGHT / 2) + k;
        snake.y[k] = (MAPHEIGHT / 2);
        gotoxy(snake.x[k],snake.y[k]);
        printf("@");
    }

    createFood();

    return;
}

//食物的产生
void createFood()
{
    srand((unsigned int)time(NULL));
    food.x = rand() % (MAPWEIGHT - 4) + 2;
    food.y = rand() % (MAPHEIGHT - 2) + 1;

    gotoxy(food.x,food.y);
    printf("?");
    gotoxy(MAPHEIGHT + 2, 0);

    return;
}

//按键的操作
void keyDown()
{
    if (_kbhit())
    {
        fflush(stdin);
        key = _getch();
    }

    if (!changeFlag)
    {
        gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
        printf(" ");
    }

    for(int i = snake.len - 1; i > 0; i--)
    {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
    }

    //移动方向
    switch(key)
    {
    case 'w':
    case 'W':
        snake.y[0] --;
        break;
    case 's':
    case 'S':
        snake.y[0] ++;
        break;
    case 'a':
    case 'A':
        snake.x[0] --;
        break;
    case 'd':
    case 'D':
        snake.x[0] ++;
        break;
    default :
        break;
    }


    gotoxy(snake.x[0], snake.y[0]);
    printf("@");

    //是否吃食物
    if (snake.x[0] == food.x && snake.y[0] == food.y)
    {
        snake.len ++;
        createFood();
    }

    changeFlag = 0;
    gotoxy(MAPHEIGHT + 2, 0);
    printf("");
    return;
}

//蛇的状态
int snakeStatus()
{
    if (snake.x[0] == 0 || snake.x[0] > MAPWEIGHT)
    {
        return 0;
    }

    if (snake.y[0] == 0 || snake.y[0] > MAPHEIGHT)
    {
        return 0;
    }

    for(int i = 1; i < snake.len; i++)
    {
        if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
        {
            return 0;
        }
    }
    return 1;
}

//光标移动
void gotoxy(int x, int y)
{
    //调用win32 API 去设置控制台的光标位置
    //1,找到控制台的窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //2,光标的结构体
    COORD coord;
    //3,设置光标的位置
    coord.X = x;
    coord.Y = y;
    //4,同步到控制台
    SetConsoleCursorPosition(handle, coord);

    return;
}

int main()
{
    drawMap();

    while(1)
    {
        Sleep(snake.speed);
        keyDown();

        if (!snakeStatus())
        {
            break;
        }
    }

    gotoxy(MAPWEIGHT / 2, MAPHEIGHT / 2);
    printf('game over');
    system("pause");

    return 0;
}
