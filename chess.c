#include<stdio.h>
#include<stdlib.h>
#include"game.h"

/*
*/

/*
here, m and n are current position cordinates.
o and p are transfer position cordinates.
*/

void main(){
	char b[8][8],board[8][8],a[9]={'r','k','b','q','c','b','k','r','p'};
	int i,j,m=0,n,o,p,avl=0;
	for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(i==0){
					board[i][j]=a[j];
					}
				else if(i==1){
					board[i][j]=a[8];
					}
				else if(i==6){
					board[i][j]=a[8]-32;
					}
				else if(i==7){
					board[i][j]=a[j]-32;
					}
				else {
					board[i][j]=' ';
					}
			}	
		}	
	
		update(board);
	while(mate==0){
		printf("Enter cordinate of piece:\n");
		scanf("%d %d",&m,&n);
		printf("Enter cordinate to move piece:\n");
		scanf("%d %d",&o,&p);
		 checkMove(board,b,m,n,o,p,avl);
		}
		
}
void copy(char board[8][8],char b[8][8]){
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            b[i][j]=board[i][j];
        }
    }
}
