#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;

void Delay(long double);
void Move();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Boarder();
void Down();
void Left();
void Up();
void Right();
int Scoreonly();

struct coordinate
{
	int x;
	int y;
	int direction;
};

typedef  struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

void HideCursor(){ // Скрыть функцию курсора
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

void Move()
{
	HideCursor();
	int a,i;
	do
	{
		fflush(stdin);
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
		Move();
	}
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GotoXY(int x, int y)
{
	HANDLE a;
	COORD b;
	fflush(stdout);
	b.X = x;
	b.Y = y;
	a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a,b);
}

void Down()
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
	if(!kbhit())
		head.y++;
}

void Delay(long double k)
{
	long double i;
	for(i=0; i<=(80000000); i++);
}

void Left()
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
	if(!kbhit())
		head.x--;
}

void Right()
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
	if(!kbhit())
		head.x++;
}

void Boarder()
{
	system("cls");
	int i;
	for(i=10; i<71; i++)
	{
		GotoXY(i,10);
		printf(" ");
		GotoXY(i,30);
		printf(" ");
	}
	for(i=10; i<31; i++)
	{
		GotoXY(10,i);
		printf(" ");
		GotoXY(70,i);
		printf(" ");
	}
}

void Up()
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
	if(!kbhit())
		head.y--;
}

int main()
{
	system("cls");
	length=5;
	head.x=25;
	head.y=20;
	head.direction=RIGHT;
	Boarder();
	bend[0]=head;
	Move();   
	return 0;
}
