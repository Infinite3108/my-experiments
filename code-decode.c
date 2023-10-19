#include<stdio.h>
void main(){
	int i,c,s,n=100;
	char set[n];
	printf("enter 1 to encode and 0 to decode message: \n");
	scanf("%d",&c);
	if(c==1){
		printf("enter secret code: \n");
		scanf("%d",&s);
		printf("enter your message: \n");
		scanf("\n%[^\n]s",set);
		for(i=0;set[i]!='\0';i++){
			if(set[i]!=' ' && set[i]!='.'){
				if(set[i]<91){
					set[i]+=32;
				}
				if(set[i]+s<123){
				set[i]=set[i]+s;	
				}
				else {
					set[i]=set[i]+s-26;
				}
			}
		}
		
	}
	
	if(c==0){
		printf("enter secret code: \n");
		scanf("%d",&s);
		printf("enter secret message: \n");
		scanf("\n%[^\n]s",set);
		for(i=0;set[i]!='\0';i++){
			if(set[i]!=' ' && set[i]!='.'){
				if(set[i]<91){
					set[i]+=32;
				}
				if(set[i]-s>96){
				set[i]=set[i]-s;	
				}
				else {
					set[i]=set[i]-s+2626;
				}
			}
		}
		
	}
	printf("Your message:\n %s",set);
}
