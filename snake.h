#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

struct snake {
	int x;
	int y;
	};
int len=1,over=0;
void update(char board[8][8], struct snake s[63]){
	int i,j,k,T=0;
	//let's update things....
	// using len so that we can limit length of snack.
	for(i=len-1;i>=0;i--){
		board[s[i].x][s[i].y]='o';
		}
	// checking if there's any unwanted dot on screen....
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
		T=0;
		if(board[i][j]=='o'){
			for(k=len-1;k>=0;k--){
				if(i==s[k].x && j==s[k].y){
					T++;
					}
				}
				if(T==0){
				board[i][j]=' ';	
					}
			}	
			}
		}
	// Finally, time to print board!!
	for(i=0;i<16;i++){
			for(j=0;j<16;j++){
				if(i%2==0){
				printf("--");	
					}
				else if(j%2==0){
					printf(" | ");
					}
				else {
					printf("%c",board[i/2][j/2]);
					}
				}
			printf("\n");
		}
	}

void move(char board[8][8],struct snake s[63], int m){
	/*
	Now, this one is a vital func for game cause, this decides almost things to make game dynamic.
	here x and y are cordinates for head dot of snack.
	m values:
	1-->
	2↓
	3<--
	4↑
	*/
	int x,y,i;
	x=s[len-1].x;
	y=s[len-1].y;
	
	if(m==1){
		// so, if we are gonna move right, we need to be <7 so that we can go to 8th block.
		if((y+1)<8 && y>=0){
		y++;
		// if we get a apple in way, we increase length of snack.
		if(board[x][y]=='*'){
			len++;
			}
		// if we bump our self, we are out!!
		if(board[x][y]=='o'){
			over=1;
			}
		// let's update this in array of cordinates.
		// if length is greater than 1, we can handle things with looping
		if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		//this one updates last one 
		s[i].x=x;
		s[i].y=y;
		}
		// else, we have only 2 cordinates to update.
		else {
			s[0].x=x;
			s[0].y=y;
			}
		}
		
	// And if we are on 8th block, we need to go to 1st one.
		//logic is same here.
		else if(y==7){
			y=0;
			if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
			if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;
			}
		else {
			s[0].x=x;
			s[0].y=y;
			}
			
			}
	// at last, updating board....
	update(board,s);
	}
	//same thing for other tree values.....
	if(m==3){
			
		if(y<8 && y-1>=0){
		y--;
		if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
		if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;
		}
		else {
			s[0].x=x;
			s[0].y=y;
			}	
		}
		else if(y==0){
			y=7;
			if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
			if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;  }
		else {
			s[0].x=x;
			s[0].y=y;
			}
			
			}
	
	update(board,s);
	}
	else if(m==2){	
		if((x+1)<8 && x>=0){
		x++;
		if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
		if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;  }
		else {
			s[0].x=x;
			s[0].y=y;
			}
		}
		else if(x==7){
			x=0;
			if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
			if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;  }
		else {
			s[0].x=x;
			s[0].y=y;
			}
			
			}
	
	update(board,s);
	}
	else if(m==4){
		
		 
		
		if(x<8 && x-1>=0){
		x--;
		if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
		if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;  }
		else {
			s[0].x=x;
			s[0].y=y;
			}
		}
		else if(x==0){
			x=7;
			if(board[x][y]=='*'){
			len++;
			}
		if(board[x][y]=='o'){
			over=1;
			}
			if(len>1){
		for(i=0;i<=len-2;i++){
			s[i].x=s[i+1].x;
			s[i].y=s[i+1].y;
		}
		s[i].x=x;
		s[i].y=y;  }
		else {
			s[0].x=x;
			s[0].y=y;
			}
			
			}
	
	update(board,s);
	}
}
/*
This one checks if apple is there or not. if not, then adds one on random empty place....
*/
void apple(char board[8][8]){
	int i,j,t=0,m=9,n=9;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]=='*'){
				t++;
				break;
				}
			}
		}
	if(t==0){
		while(board[m][n]!=' ')
		{
			
			srand(time(NULL)); 
			m=rand() % 8;
			n=rand() % 8;
			}
		board[m][n]='*';
		}
	}
