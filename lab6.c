#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console,&lpCursor);
}

void setcolor(int fg,int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16+fg);
}

void draw_ship(int x,int y){
	COORD c = { x, y };
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE) , c);
	setcolor(2,4);
	printf(" <-0-> ");   //length = 7
}

void erase_ship(int x,int y){
	COORD c = { x, y };
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE) , c);
	setcolor(0,0);
	printf("       ");
}

int main()
{
	char ch=' ';
	int x=38,y=20;
	setcursor(0);
	
	draw_ship(x,y);
	do {
		if (_kbhit()){
			ch=_getch();
			if(ch=='a') {if (x>0) {erase_ship(x,y); draw_ship(--x,y);}}	
			if(ch=='d') {if (x<79) {erase_ship(x,y); draw_ship(++x,y);}}
			if(ch=='w') {if (y>0 ) {erase_ship(x,y); draw_ship(x,--y);}}	
			if(ch=='s') {if (y<80) {erase_ship(x,y); draw_ship(x,++y);}}   
			fflush(stdin);
		}
		Sleep(100);
	} while (ch!='x');
return 0;
}