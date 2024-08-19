#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;
int life;
void Delay();
//void Move();
void Food();
int Score();
//void gotoxy(int x, int y);
//void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
unsigned int speed;
void delSnake();

struct coordinate
{
	int x;
	int y;
	int direction;
};

typedef  struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = 1;
	coord.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GotoXY(int x, int y)
{
	HANDLE a;
	COORD b;
	b.X = x;
	b.Y = y;
	a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a,b);
}

void HideCursor() // Скрыть функцию курсора
{ 
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

void Move()
{
	int a,i;
	do
	{
		Food();
		len=0;
		for(i=0; i<30; i++)
		{
			body[i].x=0;
			body[i].y=0;
			if(i==length)
				break;
		}
		Delay(length);
		Boarder();
		if(head.direction==RIGHT)
			Right();
		else if(head.direction==LEFT)
			Left();
		else if(head.direction==DOWN)
			Down();
		else if(head.direction==UP)
			Up();
		ExitGame();
	}
	while(!kbhit());
	a=getch();
	if(a==27)
	{
		system("cls");
		exit(0);
	}
	key=getch();
	if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||
	(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||
	(key==UP&&head.direction!=DOWN&&head.direction!=UP)||
	(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
	{
		bend_no++;
		bend[bend_no]=head;
		head.direction=key;
		if(key==UP)
			head.y--;
		if(key==DOWN)
			head.y++;
		if(key==RIGHT)
			head.x++;
		if(key==LEFT)
			head.x--;
		Move();
	}
	else if(key==27)
	{
		system("cls");
		exit(0);
	}
	else
	{
		printf("\a");
		Move();
	}
}

void Down() //движение в низ
{
	int i;
	for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
	{
		GotoXY(head.x,head.y-i);
		{
			if(len==0)
				printf("v");
			else
				printf("*");
		}
		body[len].x=head.x;
		body[len].y=head.y-i;
		len++;
	}
	Bend();
	if(!kbhit())
		head.y++;
}

void Up() //движение вверх
{
	int i;
	for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
	{
		GotoXY(head.x,head.y+i);
		{
			if(len==0)
				printf("^");
			else
				printf("*");
		}
		body[len].x=head.x;
		body[len].y=head.y+i;
		len++;
	}
	Bend();
	if(!kbhit())
		head.y--;
}

void Left() //движение налево
{
	int i;
	for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
	{
		GotoXY((head.x+i),head.y);
		{
			if(len==0)
				printf("<");
			else
				printf("*");
		}
		body[len].x=head.x+i;
		body[len].y=head.y;
		len++;
	}
	Bend();
	if(!kbhit())
		head.x--;
}

void Right() //движение направо
{
	int i;
	for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
	{
		body[len].x=head.x-i;
		body[len].y=head.y;
		GotoXY(body[len].x,body[len].y);
		{
			if(len==0)
				printf(">");
			else
				printf("*");
		}
		len++;
	}
	Bend();
	if(!kbhit())
		head.x++;
}

void Bend() //при повороте происходит поворот змейки
{
	int i,j,diff;
	for(i=bend_no; i>=0&&len<length; i--)
	{
		if(bend[i].x==bend[i-1].x)
		{
			diff=bend[i].y-bend[i-1].y;
			if(diff<0)
				for(j=1; j<=(-diff); j++)
				{
					body[len].x=bend[i].x;
					body[len].y=bend[i].y+j;
					GotoXY(body[len].x,body[len].y);
					printf("*");
					len++;
					if(len==length)
						break;
				}
			else if(diff>0)
				for(j=1; j<=diff; j++)
				{
					body[len].x=bend[i].x;
					body[len].y=bend[i].y-j;
					GotoXY(body[len].x,body[len].y);
					printf("*");
					len++;
					if(len==length)
						break;
				}
		}
		else if(bend[i].y==bend[i-1].y)
		{
			diff=bend[i].x-bend[i-1].x;
			if(diff<0)
				for(j=1; j<=(-diff)&&len<length; j++)
				{
					body[len].x=bend[i].x+j;
					body[len].y=bend[i].y;
					GotoXY(body[len].x,body[len].y);
					printf("*");
					len++;
					if(len==length)
						break;
			}
			else if(diff>0)
				for(j=1; j<=diff&&len<length; j++)
				{
					body[len].x=bend[i].x-j;
					body[len].y=bend[i].y;
					GotoXY(body[len].x,body[len].y);
					printf("*");
					len++;
					if(len==length)
						break;
				}
		}
	}
}

void Delay()
{
	int speed = 125;
	Score();
	Sleep(speed);
}

void ExitGame() // условие окончания игры
{
	int i,check=0;
	for(i=4; i<length; i++) //нужно минимум 4 элемента, чтобы прикоснуться к собственному телу
	{
		if(body[0].x==body[i].x&&body[0].y==body[i].y)
		{
			check++;    //значение проверки увеличивается по мере того, как координаты головы совпадают с координатами любого другого тела
		}
		if(i==length||check!=0)
			break;
	}
	if(head.x<=0||head.x>=60||head.y<=0||head.y>=25||check!=0)
	{
		life--;
		if(life>=0)
		{
			head.x=25;
			head.y=20;
			bend_no=0;
			head.direction=RIGHT;
			Move();
		}
		else
		{
			system("cls");
			printf("SCORE : %d",(length-3));
			exit(0);
		}
	}
}

void Food()
{
	if(head.x==food.x&&head.y==food.y)
	{
		length++;
		speed -= 1; //увеличивать скорость с каждым увеличением змейки
		time_t a;
		a=time(0);
		srand(a);
		food.x=rand()%60;
		if(food.x<=0)
			food.x+=4;
		food.y=rand()%25;
		if(food.y<=0)
			food.y+=4;
	}
	else if(food.x==0) //для создания еды, глобальная переменная инициализируется нулевым значением
	{
		food.x=rand()%60;
		if(food.x<=0)
			food.x+=4;
		food.y=rand()%25;
		if(food.y<=0)
			food.y+=4;
	}
}

void Boarder()
{
	system("cls");
	int i;
	GotoXY(food.x,food.y);   //отображение еды
	printf("@");
	for(i=0; i<61; i++)
	{
		GotoXY(i,0);
		printf("#");
		GotoXY(i,25);
		printf("#");
	}
	for(i=0; i<26; i++)
	{
		GotoXY(0,i);
		printf("#");
		GotoXY(60,i);
		printf("#");
	}
}

int Score()
{
	int score;
	GotoXY(5,27);
	score=length-3;
	printf("SCORE : %d",(length-3));
	score=length-3;
	GotoXY(25,27);
	printf("Speed: %d", -speed);
	GotoXY(45,27);
	printf("Life : %d",life);
	return score;
}

int main()
{
	system("cls");
	HideCursor();
	length=3;
	head.x=20;
	head.y=20;
	head.direction=RIGHT;
	life=3; //количество жизней
	Move();   //инициализация исходные движения
	return 0;
}
