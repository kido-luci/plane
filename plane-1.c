#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>


int choiceMenu = 1, choiceSetting = 2, choiceExit = 1, bullet = 254;
int mapBullet[50][50], mapBoss[50][50];
int cld[7] = {1,0,-1,-2,-1,0,1}, clc[7] = {-10,-9,-8,-7,-6,-5,-4};
int speedBoss = 2, speedBoss2 = 20, speedBoss3 = 30, GOV = 1, score = 0, hp1 = 20, hp2 = 35;
char playerName[15],chr1 = 0;
char nameHard[10][10], nameMedium[10][10], nameEasy[10][10];
int bestScoreHard[10], bestScoreMedium[10], bestScoreEasy[10];


int random(int a, int b){
	return a + rand() % (b - a + 1);
}


void changeColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void gotoxy(int x, int y){
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}


void resizeConsole(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

//**********Intro**********

void intro()
{

clock_t timeS,timeE;
timeS=clock();
do
{
	timeE=clock();
}while (timeE-timeS<=2000);

changeColor(1);
gotoxy(10,20);
printf("::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
gotoxy(10,21);
printf(":########::'##::::::::::'###::::'##::: ##:'########:\n");
gotoxy(10,22);
printf(":##.... ##: ##:::::::::'## ##::: ###:: ##: ##.....::\n");
gotoxy(10,23);
printf(":##:::: ##: ##::::::::'##:. ##:: ####: ##: ##:::::::\n");
gotoxy(10,24);
printf(":########:: ##:::::::'##:::. ##: ## ## ##: ######:::\n");
gotoxy(10,25);
printf(":##.....::: ##::::::: #########: ##. ####: ##...::::\n");
gotoxy(10,26);
printf(":##:::::::: ##::::::: ##.... ##: ##:. ###: ##:::::::\n");
gotoxy(10,27);
printf(":##:::::::: ########: ##:::: ##: ##::. ##: ########:\n");
gotoxy(10,28);
printf(":..:::::::::........::..:::::..::..::::..::........:\n");
timeS=clock();
do
{
	timeE=clock();
}while (timeE-timeS<=3000);
}

//**********Score**********
void readScore(){
	char c;
	FILE* fi;
	
	fi=fopen("scorehard.pl","r");
	for (int i = 0; i < 5; i++){
		fgets(nameHard[i], 10, fi);
		fscanf(fi,"%d%c", &bestScoreHard[i], &c);
	}
	fclose(fi);
	
	fi=fopen("scoremedium.pl","r");
	for (int i = 0; i < 5; i++){
		fgets(nameMedium[i], 10, fi);
		fscanf(fi,"%d%c", &bestScoreMedium[i], &c);
	}
	fclose(fi);
	
	fi=fopen("scoreeasy.pl", "r");
	for (int i = 0; i < 5; i++){
		fgets(nameEasy[i], 10, fi);
		fscanf(fi,"%d%c", &bestScoreEasy[i], &c);
	}
	fclose(fi);
	
}

void changeScore(){
	int i;
	if (choiceSetting == 1)
	{
		if (bestScoreHard[0] < score)
			i = 0;
		else
			for (i = 1; i < 10; i++)
				if (bestScoreHard[i-1] >= score && bestScoreHard[i] <= score)
					break;
		for (int j = 9; j > i; j--)
		{
			bestScoreHard[j] = bestScoreHard[j-1];
			for (int t = 0; t < 10; t++)
				nameHard[j][t] = nameHard[j-1][t];
		}
		bestScoreHard[i]=score;
		for (int j = 0; j < 10; j++)
			nameHard[i][j] = playerName[j]; 
	}
	else if (choiceSetting == 2)
	{
		if (bestScoreMedium[0] < score)
			i = 0;
		else
			for (i = 1; i < 10; i++)
				if (bestScoreMedium[i-1] >= score && bestScoreMedium[i] <= score)
					break;
		for (int j = 9; j > i; j--)
		{
			bestScoreMedium[j] = bestScoreMedium[j-1];
			for (int t = 0; t < 10; t++)
				nameMedium[j][t] = nameMedium[j-1][t];
		}
		bestScoreMedium[i] = score;
		for (int j = 0; j < 10; j++)
			nameMedium[i][j] = playerName[j];
	}
	else
	{
		if (bestScoreEasy[0] < score)
			i = 0;
		else
			for (i = 1; i < 10; i++)
				if (bestScoreEasy[i-1] >= score && bestScoreEasy[i] <= score)
					break;
		for (int j = 9; j > i; j--)
		{
			bestScoreEasy[j] = bestScoreEasy[j-1];
			for (int t = 0; t < 10; t++)
				nameEasy[j][t] = nameEasy[j-1][t];
		}
		bestScoreEasy[i] = score;
		for (int j = 0; j < 10; j++)
			nameEasy[i][j] = playerName[j];
	}
}

void saveScore(){
	FILE* fo;
	fo=fopen("scorehard.pl","w");
	for (int i = 0; i < 10; i++)
		fprintf(fo,"%s\n%d\n", nameHard[i], bestScoreHard[i]);
	fclose(fo);
	fo=fopen("scoremedium.pl","w");
	for (int i = 0; i < 10; i++)
		fprintf(fo,"%s\n%d\n", nameMedium[i], bestScoreMedium[i]);
	fclose(fo);
	fo=fopen("scoreeasy.pl","w");
	for (int i = 0; i < 10; i++)
		fprintf(fo,"%s\n%d\n", nameEasy[i], bestScoreEasy[i]);
	fclose(fo);
}

void printHighScoreLetter(){
	changeColor(4);
	gotoxy(22,8);
	printf("%c %c%c%c%c%c%c %c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",203 ,203,203,201,205,187,203 ,203  ,201,205,187,201,205,187,201,205,187,203,205,187,201,205,187);
	gotoxy(22,9);
	printf("%c%c%c%c%c %c%c%c%c  %c%c%c%c  %c %c%c%c%c%c%c",204,205,185,186,186 ,203,204,205,185  ,200,205,187,186  ,186 ,186,204,203,188,186,185);
	gotoxy(22,10);
	printf("%c %c%c%c%c%c%c %c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",202 ,202,202,200,205,188,202 ,202  ,200,205,188,200,205,188,200,205,188,202,200,205,200,205,188);
	changeColor(15);
}

void printHighScore(){
	drawDisplay();
	printHighScoreLetter();
	int i, x, top;
	x = 15;
	gotoxy(14, x-2);
	changeColor(31);
	printf("Lever          ");
	gotoxy(25, x-2);
	printf("Name           ");
	gotoxy(40, x-2);
	printf("Score          ");
	gotoxy(51, x-2);
	printf("Top  ");
	changeColor(15);
	gotoxy(14, x);
	changeColor(4);
	printf("Hard");
	changeColor(1);
	gotoxy(22, x - 1);
	printf("%c",179);
	gotoxy(37, x - 1);
	printf("%c",179);
	gotoxy(48, x - 1);
	printf("%c",179);
	changeColor(15);
	i = 0; top = 1;
	if (bestScoreHard[i] == 0)
	{
		gotoxy(25, x+i);
		printf("None");
		changeColor(1);
		gotoxy(22, x+i);
		printf("%c",179);
		changeColor(15);
		gotoxy(40, x+i);
		printf("None");
		changeColor(1);
		gotoxy(37, x+i);
		printf("%c",179);
		changeColor(15);
		gotoxy(52, x+i);
		printf("%d", i + 1);
		changeColor(1);
		gotoxy(48, x+i);
		printf("%c",179);
		changeColor(15);
		i++;
	}else
		while (bestScoreHard[i] > 0 && i < 5)
		{
			gotoxy(25, x+i);
			printf("%s", nameHard[i]);
			changeColor(1);
			gotoxy(22, x+i);
			printf("%c",179);
			changeColor(15);
			gotoxy(40, x+i);
			printf("%d", bestScoreHard[i]);
			changeColor(1);
			gotoxy(37, x+i);
			printf("%c",179);
			changeColor(15);
			gotoxy(52, x+i);
			printf("%d", i + 1);
			changeColor(1);
			gotoxy(48, x+i);
			printf("%c",179);
			changeColor(15);
			i++;
		}
	changeColor(1);
	gotoxy(21, x + i);
	printf("%c%c",196, 217);
	gotoxy(22, x + 1 + i);
	printf("%c%c", 218, 196);
	gotoxy(36, x + i);
	printf("%c%c",196, 217);
	gotoxy(37, x + 1 + i);
	printf("%c%c", 218, 196);
	gotoxy(47, x + i);
	printf("%c%c",196, 217);
	gotoxy(48, x + 1 + i);
	printf("%c%c", 218, 196);
	changeColor(15);
	x = x+1+i;
	i = 0;
	gotoxy(14, x+1);
	changeColor(6);
	printf("Medium");
	changeColor(15);
	if (bestScoreMedium[i] == 0)
	{
		gotoxy(25,x+1+i);
		printf("None");
		changeColor(1);
		gotoxy(22, x+1+i);
		printf("%c",179);
		changeColor(15);
		gotoxy(40, x+1+i);
		printf("None");
		changeColor(1);
		gotoxy(37, x+1+i);
		printf("%c",179);
		changeColor(15);
		gotoxy(52, x+1+i);
		printf("%d", i + 1);
		changeColor(1);
		gotoxy(48, x+1+i);
		printf("%c",179);
		changeColor(15);
		i++;
	} else
		while (bestScoreMedium[i] > 0 && i < 5)
		{
			gotoxy(25,x+1+i);
			printf("%s", nameMedium[i]);
			changeColor(1);
			gotoxy(22, x+1+i);
			printf("%c",179);
			changeColor(15);
			gotoxy(40,x+1+i);
			printf("%d", bestScoreMedium[i]);
			changeColor(1);
			gotoxy(37, x+1+i);
			printf("%c",179);
			changeColor(15);
			gotoxy(52, x+1+i);
			printf("%d", i + 1);
			changeColor(1);
			gotoxy(48, x+1+i);
			printf("%c",179);
			changeColor(15);
			i++;
		}
	changeColor(1);
	gotoxy(21, x + 1 + i);
	printf("%c%c",196, 217);
	gotoxy(22, x + 2 + i);
	printf("%c%c", 218, 196);
	gotoxy(36, x + 1 + i);
	printf("%c%c",196, 217);
	gotoxy(37, x + 2 + i);
	printf("%c%c", 218, 196);
	gotoxy(47, x + 1 + i);
	printf("%c%c",196, 217);
	gotoxy(48, x + 2 + i);
	printf("%c%c", 218, 196);
	changeColor(15);
	x = x+2+i;
	i = 0;
	gotoxy(14, x+1);
	changeColor(11);
	printf("Easy");
	changeColor(15);
	if (bestScoreEasy[i] == 0)
	{
		gotoxy(25, x+1+i);
		printf("None");
		changeColor(1);
		gotoxy(22, x+1+i);
		printf("%c",179);
		changeColor(15);
		gotoxy(40, x+1+i);
		printf("None");
		changeColor(1);
		gotoxy(37, x+1+i);
		printf("%c",179);
		changeColor(15);
		gotoxy(52, x+1+i);
		printf("%d", i + 1);
		changeColor(1);
		gotoxy(48, x+1+i);
		printf("%c",179);
		changeColor(15);
		i++;
	} else{
		while (bestScoreEasy[i] > 0 && i < 5)
		{
			gotoxy(25, x+1+i);
			printf("%s", nameEasy[i]);
			changeColor(1);
			gotoxy(22, x+1+i);
			printf("%c",179);
			changeColor(15);
			gotoxy(40,x+1+i);
			printf("%d", bestScoreEasy[i]);
			changeColor(1);
			gotoxy(37, x+1+i);
			printf("%c",179);
			changeColor(15);
			gotoxy(52, x+1+i);
			printf("%d", i + 1);
			changeColor(1);
			gotoxy(48, x+1+i);
			printf("%c",179);
			changeColor(15);
			i++;
		}
	}
	changeColor(1);
	gotoxy(21, x + 1 + i);
	printf("%c%c",196, 217);
	gotoxy(36, x + 1 + i);
	printf("%c%c",196, 217);
	gotoxy(47, x + 1 + i);
	printf("%c%c",196, 217);
	changeColor(15);
	gotoxy(25,40);
	printf("Press Esc to back Menu!");
	gotoxy(1, 45);
	char c;
	do
	{
		c = getch();
	}while (c != 27);
	system("cls");
}



//**********Setting**********
void makeChoiceSetting(){
	if (choiceSetting == 1){
		speedBoss = 1;
		speedBoss2 = 10;
		speedBoss3 = 25;
		hp1 = 20;
		hp2 = 70;
	}		
	else if (choiceSetting == 2){
		speedBoss = 2;
		speedBoss2 = 20;
		speedBoss3  = 35;
		hp1 = 20;
		hp2 = 60;
	}	
	else{
		speedBoss = 3;
		speedBoss2 = 25;
		speedBoss3 = 40;
		hp1 = 10;
		hp2 = 50;
	}
		
}

int getSetting(){
	chr1 = getch();
	if (chr1 == 72 && choiceSetting > 1)
		choiceSetting--;
	if (chr1 == 80 && choiceSetting < 3)
		choiceSetting++;
	if (chr1 == 13)
		makeChoiceSetting();
}

void printSetting(){
	changeColor(15);
	if (choiceSetting == 1)
		changeColor(591);
	gotoxy(27, 24);
	printf("      HARD      ");
	changeColor(15);
	if (choiceSetting == 2 )
		changeColor(111);
	gotoxy(27, 28);
	printf("     MEDIUM     ");
	changeColor(15);
	if (choiceSetting == 3)
		changeColor(319);
	gotoxy(27, 32);
	printf("      EASY      ");
	changeColor(15);
	gotoxy(25,40);
	printf("Press Esc to back Menu!");
	gotoxy(1, 45);
}

void setting(){
	int exit = 0;
	printLeverLetter();
	do
	{
		drawDisplay();
		printSetting();
		getSetting();
		if (chr1 == 13 || chr1 == 27){
			exit = 1;
		}
	}while (exit == 0);
	system("cls");
}

void printLeverLetter(){
	changeColor(4);
	gotoxy(15,14);
	printf("%c%c%c     %c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c%c%c%c ",219,219,187,219,219,219,219,219,219,219,187,219,219,187,219,219,187,219,219,219,219,219,219,219,187,219,219,187);
	gotoxy(15,15);                                                   
	printf("%c%c%c     %c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c%c%c%c ",219,219,186,     219,219,201,205,205,205,205,188,219,219,186,   219,219,186,219,219,201,205,205,205,205,188,219,219,186);  
	gotoxy(15,16);                                                                               
	printf("%c%c%c     %c%c%c%c%c%c  %c%c%c   %c%c%c%c%c%c%c%c%c  %c%c%c ",219,219,186,     219,219,219,219,219,187,  219,219,186,   219,219,186,219,219,219,219,219,187,  219,219,186);
	gotoxy(15,17);                                                                               
	printf("%c%c%c     %c%c%c%c%c%c  %c%c%c%c %c%c%c%c%c%c%c%c%c%c  %c%c%c ",219,219,186,     219,219,201,205,205,188,  200,219,219,187, 219,219,201,188,219,219,201,205,205,188,  219,219,186);    
	gotoxy(15,18);                                                                                             
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c ",219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187, 200,219,219,219,219,201,188, 219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187);   
	gotoxy(15,19);                                                                                             
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,188,200,205,205,205,205,205,205,188,  200,205,205,205,188,  200,205,205,205,205,205,205,188,200,205,205,205,205,205,205,188);                                                                 																															  
	changeColor(15);																															  	                                                                                                                
}



//**********Menu**********
void printMenuLetter(){
	changeColor(4);
	gotoxy(16,14);
	printf("%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c",219,219,219,187,   219,219,219,187,219,219,219,219,219,219,219,187,219,219,219,187,   219,219,187,219,219,187,   219,219,187);
	gotoxy(16,15);                                                   
	printf("%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c%c   %c%c%c",219,219,219,219,187, 219,219,219,219,186,219,219,201,205,205,205,205,188,219,219,219,219,187,  219,219,186,219,219,186,   219,219,186);  
	gotoxy(16,16);                                                                               
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c%c %c%c%c%c%c%c   %c%c%c",219,219,201,219,219,219,219,201,219,219,186,219,219,219,219,219,187,  219,219,201,219,219,187, 219,219,186,219,219,186,   219,219,186);
	gotoxy(16,17);                                                                               
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c",219,219,186,200,219,219,201,188,219,219,186,219,219,201,205,205,188,  219,219,186,200,219,219,187,219,219,186,219,219,186,   219,219,186);    
	gotoxy(16,18);                                                                                             
	printf("%c%c%c %c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,186, 200,205,188, 219,219,186,219,219,219,219,219,219,219,187,219,219,186, 200,219,219,219,219,186,200,219,219,219,219,219,219,201,188);                                                                																															  
	gotoxy(16,19);                                                                                             
	printf("%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c %c%c%c%c%c%c%c",200,205,188,     200,205,188,200,205,205,205,205,205,205,188,200,205,188,  200,205,205,205,188, 200,205,205,205,205,205,188);   
	changeColor(15);																															  	                                                                                                                
}

void printMenu(){
	if (choiceMenu == 1)
		changeColor(30);
	gotoxy(27, 24);
	printf("      PLAY      ");
	changeColor(15);
	if (choiceMenu==2)
		changeColor(30);
	gotoxy(27, 28);
	printf("  HIGHEST SCORE ");
	changeColor(15);
	if (choiceMenu==3)
		changeColor(30);
	gotoxy(27, 32);
	printf("     SETTING    ");
	changeColor(15);
	if (choiceMenu==4)
		changeColor(591);
	gotoxy(27, 36);
	printf("      EXIT      ");
	changeColor(15);
	gotoxy(1, 45);
}

void makeChoice()
{
	if (choiceMenu==4){
		system("cls");
		choiceExit=0;
	}	
	else if (choiceMenu==1){
		system("cls");
		playGame();
	}		
	else if(choiceMenu==3){
			system("cls");
			setting();
		}
	else
		{
			system("cls");
			printHighScore();
		}		
}

void getMenu(){
	char chr;
	chr = getch();
	if (chr == 72 && choiceMenu > 1)
		choiceMenu--;
	if (chr == 80 && choiceMenu < 4)
		choiceMenu++;
	if (chr == 13)
		makeChoice();
}



//**********Display**********
void drawDisplay(){
	changeColor(769);
	gotoxy(9,5);
	printf("%c",218);
	for (int i = 1; i <= 50; i++)
		printf("%c", 196);
	printf("%c", 191);
	for (int i = 1; i <= 35; i++)
	{
		gotoxy(9,5+i);
		printf("%c", 179);
		gotoxy(60,5+i);
		printf("%c", 179);
	}
	gotoxy(9,41);
	printf("%c", 192);
	for (int i = 1; i <= 50; i++)
		printf("%c", 196);
	printf("%c", 217);	
}



//**********Plane**********
void drawPlane1(int x, int y){
	gotoxy(x+2,y);
	changeColor(3);
	printf("%c",201);
	changeColor(15);
	printf("%c",bullet);
	changeColor(3);
	printf("%c",187);
	gotoxy(x+1,y+1);
	changeColor(3);
	printf("/%c",206);
	changeColor(1);
	printf("%c",206);
	changeColor(3);
	printf("%c\\",206);
	gotoxy(x,y+2);
	changeColor(3);
	printf("/%c",201);
	changeColor(1);
	printf("%c%c%c",219,223,219);
	changeColor(3);
	printf("%c\\",187);
	gotoxy(x+2,y+3);
	changeColor(4);
	printf("%c",223);
	changeColor(4);
	printf(" ");
	changeColor(4);
	printf("%c",223);
	changeColor(15);
	gotoxy(200,200);
}

void drawPlane2(int x, int y){
	gotoxy(x+2,y);
	changeColor(3);
	printf("%c",201);
	changeColor(15);
	printf(" ");
	changeColor(3);
	printf("%c",187);
	gotoxy(x+1,y+1);
	changeColor(3);
	printf("/%c",206);
	changeColor(1);
	printf("%c",206);
	changeColor(3);
	printf("%c\\",206);
	gotoxy(x,y+2);
	changeColor(3);
	printf("/%c",201);
	changeColor(1);
	printf("%c%c%c",219,223,219);
	changeColor(3);
	printf("%c\\",187);
	gotoxy(x+1,y+3);
	changeColor(12);
	printf("%c%c",176,178);
	changeColor(4);
	printf(" ");
	changeColor(12);
	printf("%c%c",178,176);
	changeColor(15);
	gotoxy(200,200);
}



//**********Boss**********
void deleteBoss(int x, int y){
	int hpBoss = mapBoss[x][y];
	for(int i = x+4; i > x-4; i--){
		for(int j = y; j < y+10; j++){
			if (hpBoss == mapBoss[i][j])
				mapBoss[i][j] -= 1;
			else if(mapBoss[i][j] == 0) break;
		}
	}	
	for(int i = x+4; i > x-4; i--){
		for(int j = y-1; j > y-10; j--){
			if (hpBoss == mapBoss[i][j])
				mapBoss[i][j] -= 1;
			else if(mapBoss[i][j] == 0) break;	
		}
	}	
}

void boss0(){
	int ranhp1 = random(hp1,hp2), ranhp2 = random(hp1,hp2), ran1 = random(1,18), ran2 = random(25,43);
	
	mapBoss[1][ran1+0] = ranhp1;
	mapBoss[1][ran1+1] = ranhp1;
	mapBoss[1][ran1+2] = ranhp1;
	mapBoss[1][ran1+3] = ranhp1;
	mapBoss[1][ran1+4] = ranhp1;
	mapBoss[2][ran1+0] = ranhp1;
	mapBoss[2][ran1+1] = ranhp1;
	mapBoss[2][ran1+2] = ranhp1;
	mapBoss[2][ran1+3] = ranhp1;
	mapBoss[2][ran1+4] = ranhp1;
	mapBoss[3][ran1+0] = ranhp1;
	mapBoss[3][ran1+1] = ranhp1;
	mapBoss[3][ran1+2] = ranhp1;
	mapBoss[3][ran1+3] = ranhp1;
	mapBoss[3][ran1+4] = ranhp1;
	
	mapBoss[1][ran2+0] = ranhp2;
	mapBoss[1][ran2+1] = ranhp2;
	mapBoss[1][ran2+2] = ranhp2;
	mapBoss[1][ran2+3] = ranhp2;
	mapBoss[1][ran2+4] = ranhp2;
	mapBoss[2][ran2+0] = ranhp2;
	mapBoss[2][ran2+1] = ranhp2;
	mapBoss[2][ran2+2] = ranhp2;
	mapBoss[2][ran2+3] = ranhp2;
	mapBoss[2][ran2+4] = ranhp2;
	mapBoss[3][ran2+0] = ranhp2;
	mapBoss[3][ran2+1] = ranhp2;
	mapBoss[3][ran2+2] = ranhp2;
	mapBoss[3][ran2+3] = ranhp2;
	mapBoss[3][ran2+4] = ranhp2;
}

void boss1(){
	int ranhp = random(hp1,hp2), ranhp1 = random(hp1,hp2), ranhp2 = random(hp1,hp2), ran1 = random(1,10), ran2 = random(19,28), ran3 = random(37,39);
	mapBoss[1][ran1+0] = ranhp;
	mapBoss[1][ran1+1] = ranhp;
	mapBoss[1][ran1+2] = ranhp;
	mapBoss[1][ran1+3] = ranhp;
	mapBoss[1][ran1+4] = ranhp;
	mapBoss[1][ran1+5] = ranhp;
	mapBoss[1][ran1+6] = ranhp;
	mapBoss[1][ran1+7] = ranhp;
	mapBoss[2][ran1+0] = ranhp;
	mapBoss[2][ran1+1] = ranhp;
	mapBoss[2][ran1+2] = ranhp;
	mapBoss[2][ran1+3] = ranhp;
	mapBoss[2][ran1+4] = ranhp;
	mapBoss[2][ran1+5] = ranhp;
	mapBoss[2][ran1+6] = ranhp;
	mapBoss[2][ran1+7] = ranhp;
	mapBoss[3][ran1+0] = ranhp;
	mapBoss[3][ran1+1] = ranhp;
	mapBoss[3][ran1+2] = ranhp;
	mapBoss[3][ran1+3] = ranhp;
	mapBoss[3][ran1+4] = ranhp;
	mapBoss[3][ran1+5] = ranhp;
	mapBoss[3][ran1+6] = ranhp;
	mapBoss[3][ran1+7] = ranhp;
	
	mapBoss[1][ran3+0] = ranhp1;
	mapBoss[1][ran3+1] = ranhp1;
	mapBoss[1][ran3+2] = ranhp1;
	mapBoss[1][ran3+3] = ranhp1;
	mapBoss[1][ran3+4] = ranhp1;
	mapBoss[2][ran3+0] = ranhp1;
	mapBoss[2][ran3+1] = ranhp1;
	mapBoss[2][ran3+2] = ranhp1;
	mapBoss[2][ran3+3] = ranhp1;
	mapBoss[2][ran3+4] = ranhp1;
	mapBoss[3][ran3+0] = ranhp1;
	mapBoss[3][ran3+1] = ranhp1;
	mapBoss[3][ran3+2] = ranhp1;
	mapBoss[3][ran3+3] = ranhp1;
	mapBoss[3][ran3+4] = ranhp1;
	mapBoss[1][ran3+5] = ranhp1;
	mapBoss[1][ran3+6] = ranhp1;
	mapBoss[1][ran3+7] = ranhp1;	
	mapBoss[2][ran3+5] = ranhp1;
	mapBoss[2][ran3+6] = ranhp1;
	mapBoss[2][ran3+7] = ranhp1;
	mapBoss[3][ran3+5] = ranhp1;
	mapBoss[3][ran3+6] = ranhp1;
	mapBoss[3][ran3+7] = ranhp1;
	
	mapBoss[1][ran2+0] = ranhp2;
	mapBoss[1][ran2+1] = ranhp2;
	mapBoss[1][ran2+2] = ranhp2;
	mapBoss[1][ran2+3] = ranhp2;
	mapBoss[1][ran2+4] = ranhp2;
	mapBoss[1][ran2+5] = ranhp2;
	mapBoss[1][ran2+6] = ranhp2;
	mapBoss[1][ran2+7] = ranhp2;
	mapBoss[2][ran2+0] = ranhp2;
	mapBoss[2][ran2+1] = ranhp2;
	mapBoss[2][ran2+2] = ranhp2;
	mapBoss[2][ran2+3] = ranhp2;
	mapBoss[2][ran2+4] = ranhp2;
	mapBoss[3][ran2+0] = ranhp2;
	mapBoss[2][ran2+5] = ranhp2;
	mapBoss[2][ran2+6] = ranhp2;
	mapBoss[2][ran2+7] = ranhp2;
	mapBoss[3][ran2+1] = ranhp2;
	mapBoss[3][ran2+2] = ranhp2;
	mapBoss[3][ran2+3] = ranhp2;
	mapBoss[3][ran2+4] = ranhp2;
	mapBoss[3][ran2+5] = ranhp2;
	mapBoss[3][ran2+6] = ranhp2;
	mapBoss[3][ran2+7] = ranhp2;
}

void boss2(){
	int ran = random(1,40), ranhp = random(hp1,hp2);	
	mapBoss[1][ran+1] = ranhp;
	mapBoss[1][ran+2] = ranhp;
	mapBoss[1][ran+3] = ranhp;
	mapBoss[1][ran+0] = ranhp;
	mapBoss[1][ran+4] = ranhp;
	mapBoss[1][ran+5] = ranhp;
	mapBoss[1][ran+6] = ranhp;
	mapBoss[1][ran+7] = ranhp;
	mapBoss[1][ran+8] = ranhp;
	mapBoss[1][ran+9] = ranhp;
	mapBoss[1][ran+0] = ranhp;
	mapBoss[2][ran+0] = ranhp;
	mapBoss[2][ran+1] = ranhp;
	mapBoss[2][ran+2] = ranhp;
	mapBoss[2][ran+3] = ranhp;
	mapBoss[2][ran+4] = ranhp;
	mapBoss[2][ran+5] = ranhp;
	mapBoss[2][ran+6] = ranhp;
	mapBoss[2][ran+7] = ranhp;
	mapBoss[2][ran+8] = ranhp;
	mapBoss[2][ran+9] = ranhp;
	mapBoss[3][ran+8] = ranhp;
	mapBoss[3][ran+9] = ranhp;
	mapBoss[3][ran+0] = ranhp;
	mapBoss[3][ran+1] = ranhp;
	mapBoss[3][ran+2] = ranhp;
	mapBoss[3][ran+3] = ranhp;
	mapBoss[3][ran+4] = ranhp;
	mapBoss[3][ran+5] = ranhp;
	mapBoss[3][ran+6] = ranhp;
	mapBoss[3][ran+7] = ranhp;
}

void bornBoss(){
	int ran = random(0,2);
	switch(ran){
			case 0:
				boss0();
				break;
			case 1:
				boss1();
				break;
			case 2:
				boss2();
				break;
	}
}

void setUpBoss(int x, int y){
	for (int i = 49; i >= 0; i--)
		for (int j = 0; j < 50; j++)
			mapBoss[i+1][j] = mapBoss[i][j];
	if (checkGameOver(y,x)){
		printGameOver();
	}				
}


void drawBoss(int x, int y){
	setUpBullet(x,y);
	for (int i = 4; i < 39; i++)
	{
		for (int j = 0; j < 49; j++)
			{
				gotoxy(j+10,2+i);
				if (mapBoss[i][j] > 0)
				{
					changeColor(mapBoss[i][j]+55);
					printf("%d",mapBoss[i][j]%10);
					changeColor(15);
				}
				else
					if (mapBullet[i][j] == 1)
						printf("%c", bullet);
					
					else	
						printf(" ");					
			}
	}
}



//**********Bullet**********
void checkBullet(){
	int plus;
	if(choiceSetting == 1) plus = 3;
	else if(choiceSetting == 2) plus = 2;
	else plus = 1;
	for(int i = 1; i < 50; i++){
		for(int j = 0; j < 50; j++){
			if(mapBullet[i][j] == 1 && mapBoss[i][j] >= 1){
				mapBullet[i][j] = 0;
				deleteBoss(i,j);
				score += plus;
			}
		}
	}		
}

void setUpBullet(int x, int y){
	for (int i = 1; i < 50; i++)
		for (int j=0;j<50;j++)
			mapBullet[i-1][j] = mapBullet[i][j];	
		mapBullet[y-3][x-7] = 1;	
	checkBullet();
}



//**********GameOver**********
int checkGameOver(int x, int y){
	for(int i = 0; i < 7; i++){
		if (mapBoss[x+cld[i]][y+clc[i]] > 0)
			return 1;
	}
	return 0;
}

void printGameOverLetter(){
	changeColor(4);
	gotoxy(18,7);
	printf("  %c%c%c%c%c  %c%c%c       %c%c%c%c %c%c%c%c%c%c%c%c%c%c%c",220,219,219,219,219  ,220,220,220       ,219,219,219,220 ,220,219,219,219,178,178,219,219,219,219,219);
	gotoxy(18,8);
	printf(" %c%c%c %c%c%c%c%c%c%c%c%c    %c%c%c%c%c%c%c %c%c%c%c%c   %c",219,219,177 ,223,219,177,177,219,219,219,219,220    ,178,219,219,177,223,219,223 ,219,219,177,178,219   ,223);
	gotoxy(18,9);
	printf("%c%c%c%c%c%c%c%c%c%c%c  %c%c%c  %c%c%c    %c%c%c%c%c%c%c%c",177,219,219,176,220,220,220,176,177,219,219  ,223,219,220  ,178,219,219    ,178,219,219,176,177,219,219,219);
	gotoxy(18,10);
	printf("%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c %c%c%c    %c%c%c %c%c%c  %c",176,178,219  ,219,219,178,176,219,219,220,220,220,220,219,219 ,177,219,219    ,177,219,219 ,177,178,219  ,220);
	gotoxy(18,11);
	printf("%c%c%c%c%c%c%c%c %c%c   %c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c",176,177,178,219,219,219,223,177 ,178,219   ,178,219,219,177,177,219,219,177   ,176,219,219,177,176,177,219,219,219,219,177);
	gotoxy(18,12);
	printf(" %c%c   %c  %c%c   %c%c%c%c%c %c%c   %c  %c%c%c %c%c %c",176,177   ,177  ,177,177   ,178,177,219,176,176 ,177,176   ,176  ,176,176,176 ,177,176 ,176);	
	gotoxy(18,13);
	printf("  %c   %c   %c   %c%c %c%c  %c      %c %c %c  %c",176   ,176   ,177   ,177,177,176,176  ,176      ,176 ,176 ,176  ,176);	
	gotoxy(18,14);
	printf("%c %c   %c   %c   %c   %c      %c      %c",176 ,176   ,176   ,176   ,177   ,176      ,176      ,176);	
	
	gotoxy(18,16);
	printf("%c%c%c%c%c%c   %c%c%c   %c%c%c%c%c%c%c%c  %c%c%c%c%c%c",177,219,219,219,219,219   ,219,219,177   ,219,178,178,219,219,219,219,219  ,219,219,223,219,219,219);
	gotoxy(18,17);
	printf("%c%c%c%c  %c%c%c%c%c%c%c   %c%c%c%c   %c %c%c%c %c %c%c%c",177,219,219,177  ,219,219,177,178,219,219,176   ,219,177,178,219   ,223 ,178,219,219 ,177 ,219,219,177);
	gotoxy(18,18);
	printf("%c%c%c%c  %c%c%c %c%c%c  %c%c%c%c%c%c%c   %c%c%c %c%c%c %c",177,219,219,176  ,219,219,177 ,178,219,219  ,219,177,176,177,219,219,219   ,178,219,219 ,176,220,219 ,177);
	gotoxy(18,19);
	printf("%c%c%c   %c%c%c  %c%c%c %c%c%c%c%c%c  %c %c%c%c%c%c%c%c",177,219,219   ,219,219,176  ,177,219,219 ,219,176,176,177,178,219  ,220 ,177,219,219,223,223,219,220);
	gotoxy(18,20);
	printf("%c %c%c%c%c%c%c%c   %c%c%c%c  %c%c%c%c%c%c%c%c%c%c%c %c%c%c%c",176 ,219,219,219,219,178,177,176   ,177,223,219,176  ,176,177,219,219,219,219,177,176,219,219,178 ,177,219,219,177);
	gotoxy(18,21);
	printf("%c %c%c%c%c%c%c    %c %c%c  %c%c %c%c %c%c %c%c %c%c%c%c",176 ,177,176,177,176,177,176    ,176 ,219,176  ,176,176 ,177,176 ,176,176 ,177,178 ,176,177,178,176);	
	gotoxy(18,22);
	printf("  %c %c %c%c    %c %c%c   %c %c  %c  %c%c %c %c%c",176 ,177 ,177,176    ,176 ,176,176   ,176 ,176  ,176  ,176,177 ,176 ,177,176);	
	gotoxy(18,23);
	printf("%c %c %c %c       %c%c     %c     %c%c   %c",176 ,176 ,176 ,177       ,176,176     ,176     ,176,176   ,176);	
	changeColor(31);
	gotoxy(28,28);
	printf("Your score : %d", score);
}

void printGameOver(){
	char c;
	GOV = 0;
	
	system("cls");
	drawDisplay();
	printGameOverLetter();
	changeColor(1);
	gotoxy(13,30);
	printf("Enter your name : ");
	changeColor(15);
	gets(playerName);
	fflush(stdin);
	while(strlen(playerName) > 9){
		system("cls");
		drawDisplay();
		printGameOverLetter();
		changeColor(4);
		gotoxy(13,30);
		printf("Your name too long!");
		gotoxy(13,31);
		printf("Enter your name again: ");
		changeColor(15);
		gets(playerName);
	}
	if (strlen(playerName)==0)
	{
		char none[10]="No name";
		strcat(playerName,none);
	}
	changeColor(15);
	gotoxy(25,40);
	printf("Press Esc to back Menu!");
	gotoxy(1,45);
	fflush(stdin);
	do{
		c = getch();
	}while(c != 27);
	
	changeScore();
	saveScore();
}




//**********Play**********
void setUpPlay(){
	for (int i = 0; i <50; i++)
		for (int j = 0; j < 50; j++)
			mapBullet[i][j] = 0;
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			mapBoss[i][j] = 0;
	GOV  =  1;
	score  =  0;			
}

void stopGame()
{
	gotoxy(23,20);
	changeColor(4);
	printf("Stop! Press ESC to exit");
	gotoxy(22,21);
	printf("Press any key to continue");
	changeColor(15);
	char chr;
	chr=getch();
	if (chr == 27 )
		GOV=0;
}

void playGame(){
	drawDisplay();
	setUpPlay();
	char chr;
	int x = 31,y = 37, xt = 0, ct  =  0, countBullet  =  0, countBullet1  =  0, draw = 1, rand;
	clock_t timeS,timeE;
	timeS = clock();
	bornBoss();	
	if (choiceSetting == 1){
		gotoxy(49,4);
		changeColor(591);
		printf("Lever : HARD");
		changeColor(15);
	}
	else if (choiceSetting == 2){
		changeColor(111);
		gotoxy(47,4);
		printf("Lever : MEDIUM");
		changeColor(15);
	}
	else {
		changeColor(319);
		gotoxy(49,4);
		printf("Lever : EASY");
		changeColor(15);
	}

	do{
		srand(time(NULL));
		rand = random(speedBoss2, speedBoss3);
		if (x != xt){
			drawBoss(x,y);
			if(draw%2 == 0)
				drawPlane1(x,y);	
			else drawPlane2(x,y);
			draw++;
			countBullet++;
			countBullet1++;
		}
		xt=x;
		changeColor(30);
		gotoxy(9,4);
		printf("Score : %d",score);
		changeColor(15);
		timeE = clock();
		if ((timeE-timeS) % 50 == 0)
		{
			
			drawBoss(x,y);			
			if(draw%2 == 0)
				drawPlane1(x,y);	
			else drawPlane2(x,y);
			draw++;
			countBullet++;
			countBullet1++;
		}
		if (countBullet > speedBoss){
			setUpBoss(x,y);
			countBullet = 0;		
		}
		if (countBullet1 > rand){
			hp1++;
			hp2++;
			bornBoss();	
			countBullet1 = 0;
		}
		if (kbhit()){		
			chr = getch();
			if (chr == 75 && x > 11)
				x--;
			if (chr == 77 && x < 51)
				x++;
			if (chr == 27)
				stopGame();
			}				
	} while (GOV);
	system("cls");
}



int main(){

	readScore();
	srand(time(NULL));
	resizeConsole(620, 800);	
	intro();
	system("cls");
	do
	{
		drawDisplay();
		printMenuLetter();
		printMenu();
		getMenu();
	}while (choiceExit);
	return 0;
}
