#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include"snake.h"
/*
This game's idea came up when i got to know how we can generate random nums.
i just needed some more function to operate like _kbhit() and _getch() to get input with looping.
it took me 7 days to make it, in total.
*/
void main() {
	int i,j,m=1,dummy;
	struct snake s[63];
	// this structure is just to keep cordinates of every dots of snack.
// in is input while we are looping, used with kbhit and getch .	
	char in;
	// these time_t funcs control timing for updating screen.
	time_t sec1;
	time_t sec2;
	// basically, it's a 8x8 box cause, 9th raw is invisible to use.
	// it's there to handle new coming dots on screen.
	char board[9][8];
	//this loop initializes every dot's position so, that it doesn't interfare in coutinuous game.
	for(i=0;i<63;i++){
	s[i].x=8;
	s[i].y=7;	
		}
		
	// this one is for starting point.
	s[0].x=4;
	s[0].y=4;
	// also, we need to initialize positions in board, too.
	for(i=0;i<8;i++){
			for(j=0;j<8;j++){
			if(board[i][j]!='*'){
			board[i][j]=' ';
			}
			}
		}
		
	// Just some printing stuffs
		
	printf("\n\n\t\tSNAKE GAME\n\t\tmade with passion\n\n");
	printf("1. Use 'r' for right\n");
		printf("2. Use 'l' for left\n");
		printf("3. Use 'u' for up\n");
		printf("4. Use 'd' for down\n\n\n");
	printf("Enter anything if you are ready\n");
	scanf("%d",&dummy);
	//Here starts game!!!
	// showing board in the start
	update(board,s);
	i=0;
	//this gives universal time difference in seconds 
	sec1=time(NULL);
	// Now, game runs!! over is handling things for us.
	while(over==0){
		sec2=time(NULL);
		//kbhit() checks if key is hit or not
		if(_kbhit()){
		//gets char for us and performs funcs for us.
		in=_getch();
		if(in=='u'){
			m=4;
			}
		if(in=='l'){
			m=3;
			}
		if(in=='d'){
			m=2;
			}
		if(in=='r'){
			m=1;
			}
		}
		//this will check time difference for us and will do funcs if it's >0
		if((sec2-sec1)>0){
		// And let's check if someone ate the apple or not. 
		// this func checks if there's a apple on board and if not any then, puts one on random place.
		apple(board);
		//things need to be updated. let's clear and update it.
		system("clear");
		move(board,s,m);
		// finally, updating time cause, that is the reason we can see transition.
		sec1=sec2;
		
		}
		}
		//And this ends program.
		if(over>0){
		printf("\n\nGAME OVER!!\n\n");	
			}
	}