#include <stdio.h>
#include <stdlib.h>
#ifndef GAME_H
#define GAME_H

void copy(char board[8][8], char b[8][8]);
int mate = 0, fake = 0;
void update(char board[8][8]);
void move(char board[8][8], int a, int c, int d, int e);
void checkMove(char board[8][8], char b[8][8], int m, int n, int o, int p, int avl);
int checkAvl(char board[8][8], int m, int n, int o, int p);
int pAvl(char board[8][8], int m, int n, int o, int p);
int hAvl(char board[8][8], int m, int n, int o, int p);
int check(char board[8][8], int m, int n, char k);
int kingAvl(char board[8][8], char k, int m, int n, int o, int p);
void checkmate(char board[8][8], char b[8][8], int m, int n, char k);

int ckx = 9, cky = 9;

void update(char board[8][8])
{
	int i, j;
	for (i = 0; i < 18; i++)
	{
		// space for cordinates
		if (i == 17)
		{
			printf("      ");
		}
		for (j = 0; j < 16; j++)
		{
			if (j == 1 && i < 17)
			{
				// cordinates for vertical line.
				if (i % 2 != 0)
				{
					printf("%d", 8 - (i / 2));
				}
				printf("   ");
			}
			if (i == 17)
			{
				// cordinates for horizontal line.
				if (j >= 0 && j % 2 == 0)
				{
					printf("%d", ((j + 2) / 2));
				}
				else
				{
					printf("   ");
				}
			}
			// horizontal lines of board
			if (i % 2 == 0)
			{
				printf("--");
			}
			else
			{
				// vertical lines of board
				if (j % 2 == 0 && i != 17)
				{
					printf("| ");
					// pieces on the board
				}
				else if (i < 17)
				{
					printf("%c ", board[i / 2][j / 2]);
				}
			}
		}
		printf("\n");
	}
}
void move(char board[8][8], int m, int n, int o, int p)
{
	char temp;
	// changes position of pieces.
	temp = board[8 - m][n - 1];
	board[8 - m][n - 1] = ' ';
	board[8 - o][p - 1] = temp;
	//we use fake =1 when we won't to check but, not update.'
	if (fake == 0)
	{
		update(board);
	}
}

int pAvl(char board[8][8], int m, int n, int o, int p)
{
	int avl = 0;
	/*
     Here, pawns move in different directions according to their sides. 
   So, we have to define two separate actions for both types.
     */
	// checking side of pawn
	if (board[8 - m][n - 1] < 91 && board[8 - m][n - 1] > 65)
	{
		// if forward space is empty
		if (board[8 - (m + 1)][n - 1] == ' ' && n == p)
		{
			// if we want to move two steps for the first time.
			if (board[4][n - 1] == ' ' && m + 2 == o && o == 4 && n == p)
			{
				avl = 1;
			}
			// if we want to move one step only
			else if ((m + 1) == o && n == p)
			{
				avl = 1;
			}
		}
		// To kill opponents in cross.
		else if (board[8 - (m + 1)][n] >= 'a' && (m + 1) == o && (n + 1) == p)
		{
			avl = 1;
		}
		else if (board[8 - (m + 1)][n - 2] >= 'a' && (m + 1) == o && (n - 1) == p)
		{
			avl = 1;
		}
		// To not kill our own pieces
		else if (board[8 - (m + 1)][n] <= 'Z' && (m + 1) == o && (n + 1) == p)
		{
			avl = -1;
		}
		else if (board[8 - (m + 1)][n - 2] <= 'Z' && (m + 1) == o && (n - 1) == p)
		{
			avl = -1;
		}
		// if cross places are empty, you can't move.
		else
		{
			avl = 0;
		}
	}
	// Same things for lowercase pawns
	if (board[8 - m][n - 1] < 123 && board[8 - m][n - 1] > 97)
	{
		// checking empty spaces
		if (board[8 - m + 1][n - 1] == ' ' && n == p)
		{
			// moving two steps
			if (board[3][n - 1] == ' ' && m - 2 == o && o == 5 && n == p)
			{
				avl = 1;
			}
			// moving one step
			else if ((m - 1) == o && n == p)
			{
				avl = 1;
			}
		}
		// killing enemy in cross
		else if (board[8 - m + 1][n] <= 'Z' && board[8 - m + 1][n] >= 'A' && m - 1 == o && (n + 1) == p)
		{
			avl = 1;
		}

		else if (board[8 - m + 1][n - 2] <= 'Z' && (m - 1) == o && (n - 1) == p)
		{
			avl = 1;
		}
		// not killing our own pieces
		else if (board[8 - m + 1][n] <= 'z' && board[8 - m + 1][n] >= 'a' && m - 1 == o && (n + 1) == p)
		{
			avl = -1;
		}

		else if (board[8 - m + 1][n - 2] >= 'a' && (m - 1) == o && (n - 1) == p)
		{
			avl = -1;
		}
		else
		{
			avl = 0;
		}
	}

	return avl;
}

int hAvl(char board[8][8], int m, int n, int o, int p)
{
	int avl = 0;
	int min;
	int M;
	// setting limits for enemy range.
	if (board[8 - m][n - 1] > 65 && board[8 - m][n - 1] < 90)
	{
		min = 96;
		M = 123;
	}
	else if (board[8 - m][n - 1] > 97 && board[8 - m][n - 1] < 123)
	{
		min = 65;
		M = 90;
	}
	// checking all 8 combinations for knight.
	// x,y=+2,+1
	if (m + 2 < 9 && n + 1 < 9 && o == m + 2 && p == n + 1)
	{
		if ((board[8 - (m + 2)][n] > min && board[8 - (m + 2)][n] < M) || board[8 - (m + 2)][n] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=+2,-1
	else if (m + 2 < 9 && n - 1 > 0 && o == m + 2 && p == n - 1)
	{
		if ((board[8 - (m + 2)][n - 2] > min && board[8 - (m + 2)][n - 2] < M) || board[8 - (m + 2)][n - 2] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=-2,+1
	else if (m - 2 > 0 && n + 1 < 9 && o == m - 2 && p == n + 1)
	{
		if ((board[8 - (m - 2)][n] > min && board[8 - (m - 2)][n] < M) || board[8 - (m - 2)][n] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=-2,-1
	else if (m - 2 > 0 && n - 1 > 0 && o == m - 2 && p == n - 1)
	{
		if ((board[8 - (m - 2)][n - 2] > min && board[8 - (m - 2)][n - 2] < M) || board[8 - (m - 2)][n - 2] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=+1,+2
	else if (n + 2 < 9 && m + 1 < 9 && o == m + 1 && p == n + 2)
	{
		if ((board[8 - (m + 1)][n + 1] > min && board[8 - (m + 1)][n + 1] < M) || board[8 - (m + 1)][n + 1] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=-1,+2
	else if (n + 2 < 9 && m - 1 > 0 && o == m - 1 && p == n + 2)
	{
		if ((board[8 - (m - 1)][n + 1] > min && board[8 - (m - 1)][n + 1] < M) || board[8 - (m - 1)][n + 1] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=+1,-2
	else if (n - 2 > 0 && m + 1 < 9 && o == m + 1 && p == n - 2)
	{
		if ((board[8 - (m + 1)][n - 3] > min && board[8 - (m + 1)][n - 3] < M) || board[8 - (m + 1)][n - 3] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}
	// x,y=-1,-2
	else if (n - 2 > 0 && m - 1 > 0 && o == m - 1 && p == n - 2)
	{
		if ((board[8 - (m - 1)][n - 3] > min && board[8 - (m - 1)][n - 3] < M) || board[8 - (m - 1)][n - 3] == ' ')
		{
			avl = 1;
		}
		else
		{
			avl = -1;
		}
	}

	return avl;
}
int rAvl(char board[8][8], int m, int n, int o, int p)
{
	int i, c = 0, avl = 0;
	int min;
	int M;
	// setting limits for enemy range
	if (board[8 - m][n - 1] > 65 && board[8 - m][n - 1] < 90)
	{
		min = 96;
		M = 123;
	}
	else if (board[8 - m][n - 1] > 97 && board[8 - m][n - 1] < 123)
	{
		min = 65;
		M = 90;
	}
	// tracing var c to check if anything comes in between points.
	c = 0;
	if (avl == 0)
	{
		// to check down side
		for (i = 9 - m; i < 8; i++)
		{
			if (c == 0)
			{
				if (board[i][n - 1] == ' ')
				{
					if (o == 8 - i && p == n)
					{
						avl = 1;
						break;
					}
				}
				// if not empty, then stop checking forward and give value.
				else if (board[i][n - 1] != ' ')
				{
					if (board[i][n - 1] >= min && board[i][n - 1] <= M && o == 8 - i && p == n)
					{
						avl = 1;
					}
					else if (o == 8 - i && p == n)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}

	c = 0;
	if (avl == 0)
	{
		// checking up side
		for (i = 8 - (m + 1); i >= 0; i--)
		{
			if (c == 0)
			{
				if (board[i][n - 1] == ' ')
				{
					if (o == 8 - i && p == n)
					{
						avl = 1;
						break;
					}
				}
				else if (board[i][n - 1] != ' ')
				{
					if (board[i][n - 1] >= min && board[i][n - 1] <= M && o == 8 - i && p == n)
					{
						avl = 1;
					}
					else if (o == 8 - i && p == n)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}
	c = 0;
	if (avl == 0)
	{
		// checking right side
		for (i = n; i <= 8; i++)
		{
			if (c == 0)
			{
				if (board[8 - m][i] == ' ')
				{
					if (o == m && p == i + 1)
					{
						avl = 1;
						break;
					}
				}
				else if (board[8 - m][i] != ' ')
				{
					if (board[8 - m][i] >= min && board[8 - m][i] <= M && o == m && p == i + 1)
					{
						avl = 1;
					}
					else if (o == m && p == i + 1)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}
	c = 0;
	if (avl == 0)
	{
		// checking left side
		for (i = n - 2; i >= 0; i--)
		{
			if (c == 0)
			{
				if (board[8 - m][i] == ' ')
				{
					if (o == m && p == i + 1)
					{
						avl = 1;
						break;
					}
				}
				else if (board[8 - m][i] != ' ')
				{
					if (board[8 - m][i] >= min && board[8 - m][i] <= M && o == m && p == i + 1)
					{
						avl = 1;
					}
					else if (o == m && p == i + 1)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}

	return avl;
}

int bAvl(char board[8][8], int m, int n, int o, int p)
{
	int i, j, c, avl = 0;
	int min;
	int M;
	// setting limit for enemy range.
	if (board[8 - m][n - 1] > 65 && board[8 - m][n - 1] < 90)
	{
		min = 96;
		M = 123;
	}
	else if (board[8 - m][n - 1] > 97 && board[8 - m][n - 1] < 123)
	{
		min = 65;
		M = 90;
	}
	c = 0;
	if (avl == 0)
	{
		// for bottom right
		for (i = 9 - m, j = n; i < 8 && j < 8; i++, j++)
		{
			if (c == 0)
			{
				if (board[i][j] == ' ')
				{
					if (o == 8 - i && p == j + 1)
					{
						avl = 1;
						break;
					}
				}
				else if (board[i][j] != ' ')
				{
					if (board[i][j] >= min && board[i][j] <= M && o == 8 - i && p == j + 1)
					{
						avl = 1;
					}
					else if (o == 8 - i && p == j + 1)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}
	c = 0;
	if (avl == 0)
	{
		// for bottom left
		for (i = 9 - m, j = n - 2; i < 8 && j >= 0; i++, j--)
		{
			if (c == 0)
			{
				if (board[i][j] == ' ')
				{
					if (o == 8 - i && p == j + 1)
					{
						avl = 1;
						break;
					}
				}
				else if (board[i][j] != ' ')
				{
					if (board[i][j] >= min && board[i][j] <= M && o == 8 - i && p == j + 1)
					{
						avl = 1;
					}
					if ((board[i][j] <= min || board[i][j] >= M) && o == 8 - i && p == j + 1)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}
	c = 0;
	if (avl == 0)
	{
		// for top left
		for (i = 7 - m, j = n - 2; i >= 0 && j >= 0; i--, j--)
		{
			if (c == 0)
			{
				if (board[i][j] == ' ')
				{
					if (o == 8 - i && p == j + 1)
					{
						avl = 1;
						break;
					}
				}
				else if (board[i][j] != ' ')
				{
					if (board[i][j] >= min && board[i][j] <= M && o == 8 - i && p == j + 1)
					{
						avl = 1;
					}
					if ((board[i][j] <= min || board[i][j] >= M) && o == 8 - i && p == j + 1)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}
	c = 0;
	if (avl == 0)
	{
		// for top right
		for (i = 7 - m, j = n; i >= 0 && j < 8; i--, j++)
		{
			if (c == 0)
			{
				if (board[i][j] == ' ')
				{
					if (o == 8 - i && p == j + 1)
					{
						avl = 1;
						break;
					}
				}
				else if (board[i][j] != ' ')
				{
					if (board[i][j] >= min && board[i][j] <= M && o == 8 - i && p == j + 1)
					{
						avl = 1;
					}
					if ((board[i][j] <= min || board[i][j] >= M) && o == 8 - i && p == j + 1)
					{
						avl = -1;
					}
					c++;
					break;
				}
			}
		}
	}
	return avl;
}
int check(char board[8][8], int m, int n, char k)
{
	/*
This function verifies check on kings and returns value in 0 or 1;
*/
	int i, j, avl = 0;
	int min;
	int M;
	char ch;
	// setting limit for enemy range.
	if (k > 65 && k < 90)
	{
		min = 96;
		M = 123;
	}
	else if (k > 97 && k < 123)
	{
		min = 65;
		M = 90;
	}
	// we need to verify from every place so,
	/*
   if enemy can reach king, then only there's a check on king.
   so we will verify every possible move.
   */
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			// for knights
			if (avl == 0)
			{
				ch = (min == 96) ? 'k' : 'K';
				if (board[i][j] == ch)
				{
					avl = hAvl(board, 8 - i, j + 1, m, n);
					if (avl != 0)
					{
						if (avl == 1)
						{
							ckx = i;
							cky = j;
						}
						break;
					}
				}
			}
			// for rooks
			if (avl == 0)
			{
				ch = (min == 96) ? 'r' : 'R';
				if (board[i][j] == ch)
				{
					avl = rAvl(board, 8 - i, j + 1, m, n);
					if (avl != 0)
					{
						if (avl == 1)
						{
							ckx = i;
							cky = j;
						}
						break;
					}
				}
			}
			// for bishops
			if (avl == 0)
			{
				ch = (min == 96) ? 'b' : 'B';
				if (board[i][j] == ch)
				{
					avl = bAvl(board, 8 - i, j + 1, m, n);
					if (avl != 0)
					{
						if (avl == 1)
						{
							ckx = i;
							cky = j;
						}
						break;
					}
				}
			}
			// for queen, we are taking combination of rook and bishop so, if anyone is one, we can move.
			if (avl == 0)
			{
				ch = (min == 96) ? 'q' : 'Q';
				if (board[i][j] == ch)
				{
					avl = bAvl(board, 8 - i, j + 1, m, n);
					if (avl == 0)
					{
						avl = rAvl(board, 8 - i, j + 1, m, n);
					}

					if (avl != 0)
					{
						if (avl == 1)
						{
							ckx = i;
							cky = j;
						}
						break;
					}
				}
			}
			// this one is for pawn. they have only two places to verify so,
			if (avl == 0)
			{
				if (k == 'C')
				{
					if (board[i][j] == 'p')
					{
						if (8 - m == i + 1 && (n - 1 == j + 1 || n - 1 == j - 1))
						{
							avl = 1;
							if (avl == 1)
							{
								ckx = i;
								cky = j;
							}
							break;
						}
						else
						{
							avl = 0;
						}
					}
				}
				// pawns for lowercase king
				if (k == 'c')
				{
					if (board[i][j] == 'P')
					{
						if (8 - m == i - 1 && (n - 1 == j + 1 || n - 1 == j - 1))
						{
							avl = 1;
							if (avl == 1)
							{
								ckx = i;
								cky = j;
							}
							break;
						}
						else
						{
							avl = 0;
						}
					}
				}
			}
		}
		if (avl > 0)
		{
			break;
		}
	}
	return avl;
}

int kingAvl(char board[8][8], char k, int m, int n, int o, int p)
{
	/*
	This function checks if king can move to perticular place or not.
	*/
	int avl = 0;
	int min;
	int M;
	// setting enemy limits.
	if (k > 65 && k < 90)
	{
		min = 96;
		M = 123;
	}
	else if (k > 97 && k < 123)
	{
		min = 65;
		M = 90;
	}
	// king has only eight pieces to move to so, checking for them.
	if (((o - m) >= -1 && (o - m) <= 1) && ((p - n) >= -1 && (p - n) <= 1))
	{
		// this func gives us value if we can get check on that place or not
		avl = check(board, o, p, k);
		// if check is  not there then, we can move .

		if (avl <= 0)
		{
			if (board[8 - o][p - 1] == ' ')
			{
				avl += 1;
			}
			else if (board[8 - o][p - 1] != ' ')
			{
				if (board[8 - o][p - 1] >= min && board[8 - o][p - 1] <= M)
				{
					avl += 1;
					// if enemy is protected then, you can't kill him. so, avl = 0; else avl=1
				}
			}
		}
	}

	return avl;
}

int checkAvl(char board[8][8], int m, int n, int o, int p)
{
	/*
	This func checks availability of move and return value of avl.
	if movable, avl>0
	if our own piece is there, avl<0
	else 0
	*/

	int avl = 0;
	char k;
	// different func for different pieces
	if (board[8 - m][n - 1] == 'p' || board[8 - m][n - 1] == 'P')
	{
		avl = pAvl(board, m, n, o, p);
	}
	else if (board[8 - m][n - 1] == 'k' || board[8 - m][n - 1] == 'K')
	{
		avl = hAvl(board, m, n, o, p);
	}
	else if (board[8 - m][n - 1] == 'r' || board[8 - m][n - 1] == 'R')
	{
		avl = rAvl(board, m, n, o, p);
	}
	else if (board[8 - m][n - 1] == 'b' || board[8 - m][n - 1] == 'B')
	{
		avl = bAvl(board, m, n, o, p);
	}
	else if (board[8 - m][n - 1] == 'q' || board[8 - m][n - 1] == 'Q')
	{
		avl = rAvl(board, m, n, o, p);

		if (avl <= 0)
		{
			avl = bAvl(board, m, n, o, p);
		}
	}
	else if (board[8 - m][n - 1] == 'c' || board[8 - m][n - 1] == 'C')
	{
		k = board[8 - m][n - 1];
		avl = kingAvl(board, k, m, n, o, p);
	}

	return avl;
}

int CM(char b[8][8],char k,int m, int n){
	/*
	This one is sub function for checkmate func.
	It checks available and movable positions for king and returns 0 or 1.
	*/

	int i,j,y=0;
	// checking all nine places
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			y=kingAvl(b,k,m,n,m+i,n+j);
			if(y==1){
				break;
				}

			}
		}
		return y;
	}
//int CM2(char board[8][8], char b[8][8], char k, int m, int n, int i, int j){
//	/*
//	This one is also a sub function for checkmate func.
//	this one checks every possible move for perticular piece and returns 1 if that move prevents check.
//*/
//	int o,p,avl=0,x,y;
//
//	for(o=0;o<8;o++){
//				for(p=0;p<8;p++){
//
//					avl=checkAvl(b,8-i,j+1,8-o,p+1);
//					if(avl>0){
//					fake=1;
//					move(b,8-i,j+1,8-o,p+1);
//					x=check(b,m,n,k);
//					y=CM(b,k,m,n);
//
//		if(x==1 && y<=0){
//						avl=0;
//						copy(board,b);
//						}
//		if(x==0 || y==1){
//						avl=1;
//						break;
//						}
//						}
//					}
//				}
//			return avl;
//	}
//void checkmate(char board[8][8],char b[8][8],int m, int n, char k){
//	int i,j,ch,x,y,avl;
//	int min;
//    int M;
//
//    if(k>65 && k<90){
//    		min=65;
//    		M=90;
//    		}
//    else if(k>97 && k<123){
//    		min=97;
//    		M=123;
//    		}
//
//	copy(board,b);
//	x=check(b,m,n,k);
//	y=CM(b,k,m,n);
//
//	if(x==1 && y<=0){
//	for(i=0;i<8;i++){
//		for(j=0;j<8;j++){
//			ch=b[i][j];
//
//			if(ch<M && ch>min){
//
//				avl=CM2(board,b,k, m, n,i,j);
//				if(avl>0){
//					break;
//					}
//				}
//			}
//			if(avl>0){
//					break;
//					}
//		}
//		if(avl==0){
//			mate=1;
//			}
//		}
//	}
/**/

void checkmate(char board[8][8], char b[8][8], int m, int n, char K)
{
	int i, j, x, y, k, l, avl = 0, ck = 0;
	int min;
	int M;

	if (K > 65 && K < 90)
	{
		min = 96;
		M = 123;
	}
	else if (K > 97 && K < 123)
	{
		min = 64;
		M = 91;
	}
	if (board[ckx][cky] != ('K' - 64 + min) && board[ckx][cky] != ('P' - 64 + min))
	{
		for (i = ckx, j = cky; i!=m && j!=n; (i < m) ? i++ : i--, (j < n) ? j++ : j--)
		{
			
			for (k = 0; k < 8; k++)
			{
				for (l = 0; l < 8; l++)
				{
				copy(board, b);
				if(b[k][l]<min || b[k][l]>M)
				{
					if(checkAvl(b,8-k,l+1,8-i,j+1)==1){
					fake=1;
					move(b,8-k,l+1,8-i,j+1);
					x=check(b,m,n,K);
					ck=CM(b,K,m,n);
					if(x==0 || ck==1){
						avl++;
						}
					
						}
					}
				}
		
			}
			
		}
		
		if(avl==0){
				mate=1;
				
				}
		
	}
	else {
		copy(board,b);
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(checkAvl(b,8-i,j+1,8-ckx,cky+1)==1){
				break;	
					}
				}
			if(avl==1){
				break;
				}
			}
		if(avl==0){
				mate=1;
				
				}
		}
}

void checkMove(char board[8][8], char b[8][8], int m, int n, int o, int p, int avl)
{
	int king, kx, ky, i, j;
	char k;
	avl = checkAvl(board, m, n, o, p);
	if (avl != 127 && avl > 0)
	{
		system("clear");
		fake = 0;
		move(board, m, n, o, p);
	}
	else
	{
		printf("Sorry!! move not available!!\n");
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == 'c' || board[i][j] == 'C')
			{
				kx = 8 - i;
				ky = j + 1;
				k = board[i][j];
				king = check(board, kx, ky, k);
				if (king > 0)
				{
					printf("It's a check on %c!!\n ", k);
					checkmate(board, b, m, n, k);
					if(mate==1){
						printf("GAME OVER!!!\n%c WINS!!",(k<90)?'c':'C');
						}
					ckx = 9;
					cky = 9;
					break;
				}
			}
		}
	}
}

#endif