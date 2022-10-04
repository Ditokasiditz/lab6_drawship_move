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
	printf("^");
}

void erase_bullet(int x,int y){
	gotoxy(x,y);
	setcolor(0,0);
	printf(" ");
}

int main()
{
	char ch='.';
	int x=38,y=25,direction=0,i=0,bullet_status[4],xb[4],yb[4];
	//direction=0(stop) =1(left) =2(right)
	//bull_status=0(off) =1(on)
	setcursor(0);
	draw_ship(x,y);
	for(int j=0;j<5;j++){
		bullet_status[j]=0;
	}
		
	do {
		if (_kbhit()){
			ch=_getch();
			if(ch=='a') {direction=1;}
			if(ch=='d') {direction=2;}
			if(ch=='s') { direction=0;draw_ship(x,y);}
			if(ch=='j') {
				bullet_status[i]=1; 
				xb[i]=x+3;
				yb[i]=y-1;
				i++;
				}
			fflush(stdin);
		}
			
		if(direction==1) {if (x>0) {erase_ship(x,y); draw_ship(--x,y);}}
		else if(direction==2) {if (x<79) {erase_ship(x,y); draw_ship(++x,y);}}
		
	
		if(bullet_status[0]==1){
			erase_bullet(xb[0],yb[0]);
			if(yb[0]==2){bullet_status[0]=0;}
			else{draw_bullet(xb[0],--yb[0]);}
		}
		
		if(bullet_status[1]==1){
			erase_bullet(xb[1],yb[1]);
			if(yb[1]==2){bullet_status[1]=0;}
			else{draw_bullet(xb[1],--yb[1]);}
		}
		
		if(bullet_status[2]==1){
			erase_bullet(xb[2],yb[2]);
			if(yb[2]==2){bullet_status[2]=0;}
			else{ draw_bullet(xb[2],--yb[2]);}
		}
		
		if(bullet_status[3]==1){
			erase_bullet(xb[3],yb[3]);
			if(yb[3]==2){bullet_status[3]=0;}	
			else{ draw_bullet(xb[3],--yb[3]);}
		}
		
		if(bullet_status[4]==1){
			erase_bullet(xb[4],yb[4]);
			if(yb[4]==2){bullet_status[4]=0;}	
			else{ draw_bullet(xb[4],--yb[4]);}
		}
			
		
		Sleep(100);
	}while (ch!='x');
return 0;
}