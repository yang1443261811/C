/**
 * ̰����
 *
 * 1.�������
 * 2.ģ�黯���
 * 3.ʵ�ֹ���
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  //�������API
#include <time.h>     //ʳ�����
#include <conio.h>    //���̼��

//�������
/////////////////////////////////////
//    ��������

#define MAPHEIGHT 25//��ͼ�ĸ߶�
#define MAPWEIGHT 100//��ͼ�Ŀ��
#define SNAKESIZE 80

//ʳ��Ľṹ��
struct
{
    int x;
    int y;
} food;

//�ߵĽṹ��
struct
{
    int x[SNAKESIZE];
    int y[SNAKESIZE];
    int len;        //�ߵĳ���
    int speed;      //�ߵ��ٶ�
} snake;

//ȫ�ֱ���
int key = 'w';  //��ʼ���ƶ�����
int changeFlag = 0;//�ߵı仯�ı��

//����ͼ
void drawMap()
{
    //1,ȷ����Χ
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


    //2,�����ߵ���״
    snake.len = 3;
    snake.speed = 200;
    //2.1,������ͷ
    snake.x[0] = MAPWEIGHT / 2;
    snake.y[0] = MAPHEIGHT / 2;
    gotoxy(snake.x[0],snake.y[0]);
    printf("@");
    //2.2,���ߵ�����
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

//ʳ��Ĳ���
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

//�����Ĳ���
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

    //�ƶ�����
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

    //�Ƿ��ʳ��
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

//�ߵ�״̬
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

//����ƶ�
void gotoxy(int x, int y)
{
    //����win32 API ȥ���ÿ���̨�Ĺ��λ��
    //1,�ҵ�����̨�Ĵ���
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //2,���Ľṹ��
    COORD coord;
    //3,���ù���λ��
    coord.X = x;
    coord.Y = y;
    //4,ͬ��������̨
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
