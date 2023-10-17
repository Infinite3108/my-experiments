#include<stdio.h>
void main(){
	int i,j,m,n,a[3][3];
	char w=0,o;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			a[i][j]=' ';
		}
	}
	update(a);
	while(w==0){
	printf("Enter cordinates for move: \n");
	scanf("%d %d %c",&m,&n,&o);
	
	move(a,m,n,o,w);
	}
}
void update(int a[3][3]){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(i==1 || i==3){
				printf("--");
			}
			else if(j==1 || j==3){
				printf(" | ");
			}
			else {
				printf("%c",a[i/2][j/2]);
			}
		}
		printf("\n");
	}
	
}
void move(int a[3][3],int m,int n,char o, char w){
	if(a[m][n]==' '){
		a[m][n]=o;
		update(a);
		check(a,w);
		if(w!=0){
			printf("And winner is %c!!\n",w);
		}
	}
	else{
	printf("place is already occupied!!\n");
	}
}
void check(int a[3][3],char w){
	int i,j,c;
	for(i=0;i<3;i++){
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[i][j]=='O'){
					c++;
				}
				
			}
			if(c==3){
					w='O';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[i][j]=='X'){
					c++;
				}
			}
			if(c==3){
					w='X';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[j][i]=='O'){
					c++;
				}
			}
			if(c==3){
					w='O';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[j][i]=='X'){
					c++;
				}
			}
			if(c==3){
					w='X';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[j][j]=='O'){
					c++;
				}
			}
			if(c==3){
					w='O';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[j][j]=='X'){
					c++;
				}
			}
			if(c==3){
					w='X';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[2-j][j]=='O'){
					c++;
				}
			}
			if(c==3){
					w='O';
				}
		}
		if(c<3){
			c=0;
			for(j=0;j<3;j++){
				if(a[2-j][j]=='X'){
					c++;
				}
			}
			if(c==3){
					w='X';
				}
		}
	}
	
}
