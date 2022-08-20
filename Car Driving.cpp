#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {  ' ','±','±',' ',
                    '±','±','±','±', 					
					' ','±','±',' ', 
					'±','±','±','±'}; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	} 
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****"; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 

void gameover(){
	system("cls");
	cout<<endl;
	gotoxy(32,4);cout<<"\t\t--------------------------"<<endl;
	gotoxy(32,5);cout<<"\t\t-------- Game Over -------"<<endl;
	gotoxy(32,6);cout<<"\t\t--------------------------"<<endl<<endl<<endl<<endl;
	gotoxy(55,14);cout<<"\t\t*Your Score: "<<score<<endl<<endl<<endl;
	gotoxy(30,18);cout<<"-------------------------";
	gotoxy(30,19);cout<<"|       THANK YOU.      |";
	gotoxy(30,20);cout<<"-------------------------";
	gotoxy(1,23);cout<<"\t\t Press any key to go back to menu.";
	gotoxy(1,24);cout<<"\t\t--------------------------------------";
	getch();
}

void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){
	
	system("cls");
	    gotoxy(35,2);cout<<"------------------";
		gotoxy(35,3);cout<<"|  Instructions  |";
		gotoxy(35,4);cout<<"------------------";
		gotoxy(10,8);cout<<"Avoid Cars by moving left or right. ";
		gotoxy(10,10);cout<<" Press 'a' to move left";
		gotoxy(10,11);cout<<" Press 'd' to move right";
		gotoxy(10,13);cout<<" Press 'escape' to exit";
		gotoxy(2,19);cout<<"Press any key to go back to menu";
		gotoxy(2,20);cout<<"---------------------------------";
	getch();
}

void name(){
		system("cls"); 
    gotoxy(40,10); cout<<"**********************************";	
	gotoxy(40,11); cout<<"|         TARUN KUMAR DEY        |";
	gotoxy(40,12); cout<<"**********************************";	
	gotoxy(10,23); cout<<"**** Press any key to start the game ****";	
	gotoxy(10,24); cout<<"---------------------------------------------";	
	getch();
}

void start(){
		system("cls"); 
    gotoxy(40,13); cout<<"***************************";	
	gotoxy(40,14); cout<<"|         WELCOME         |";
	gotoxy(40,15); cout<<"***************************";	
	gotoxy(10,23); cout<<"****Press any key to enter the main menu****";	
	gotoxy(10,24); cout<<"---------------------------------------------";	
	getch();
	
}

void play(){
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 3, 1);cout<<"***************";
	gotoxy(WIN_WIDTH + 3, 2);cout<<"| Car Driving |";
	gotoxy(WIN_WIDTH + 3, 3);cout<<"***************";
	gotoxy(WIN_WIDTH + 5, 11); cout<<"-------------";
	gotoxy(WIN_WIDTH + 5, 12);cout<<"|  Control  |";
	gotoxy(WIN_WIDTH + 5, 13);cout<<"-------------";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	
	gotoxy(18, 5);cout<<"Press any key to start";
	gotoxy(18, 6);cout<<"----------------------";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	gotoxy(18, 6);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			gameover();
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	name();
	start();
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
	
		system("cls");
		gotoxy(45,1); cout<<"****************************";
		gotoxy(45,2); cout<<"|        CAR DRIVING       |";
		gotoxy(45,3); cout<<"****************************";
		gotoxy(25,7); cout<<"-------------------";
		gotoxy(25,8); cout<<"|  1. Start Game  |";
		gotoxy(25,9); cout<<"-------------------";
		gotoxy(35,11); cout<<"---------------------";
		gotoxy(35,12); cout<<"|  2. Instructions  |";
		gotoxy(35,13); cout<<"---------------------";	
		gotoxy(45,15); cout<<"-------------"; 
		gotoxy(45,16); cout<<"|  3. Quit  |";
		gotoxy(45,17); cout<<"-------------";
		gotoxy(10,19); cout<<"Select option: ";
		gotoxy(10,20); cout<<"--------------";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
