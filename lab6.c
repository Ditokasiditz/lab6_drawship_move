#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

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
	gotoxy(x,y);
	setcolor(2,4);
	printf(" <-0-> ");   //length = 7
}

void erase_ship(int x,int y){
	gotoxy(x,y);
	setcolor(0,0);
	printf("       ");
}

void draw_bullet(int x,int y){
	gotoxy(x,y);
    setcolor(2,3);
	printf("o");
}

void erase_bullet(int x,int y){
	gotoxy(x,y);
	setcolor(0,0);
	printf(" ");
}

int main()
{
	char ch='.';
	int x=38,y=20,direction=0,bullet_status=0,xb=0,yb=0;   
	//direction=0(stop) =1(left) =2(right) =3(up) =4(down)
	//bull_status=0(off) =1(on)
	setcursor(0);
	
	draw_ship(x,y);
	do {
		if (_kbhit()){
			ch=_getch();
			if(ch=='a') {direction=1;}
			if(ch=='d') {direction=2;}
			if(ch=='s') { direction=0;draw_ship(x,y);}
			if(ch=='j') {
				bullet_status=1; 
				xb=x;yb=y;
				}
			fflush(stdin);
		}
		
		
		if(direction==1) {if (x>0) {erase_ship(x,y); draw_ship(--x,y);}}
		else if(direction==2) {if (x<79) {erase_ship(x,y); draw_ship(++x,y);}}
	
		if(bullet_status==1){
			erase_bullet(xb,yb);
			if(yb>0){ draw_bullet(xb,--yb);}
			else{bullet_status=0;}	
		}
		
		
		Sleep(100);
	}while (ch!='x');
return 0;
}