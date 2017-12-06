#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <limits.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;


	bool isInRow(int (&board)[16][16], int i, int c)
	{
		for (int k = 0; k <= 15; k++)
		{
			if (board[i][k] == c)
				return true;
		}
		return false;
	}

	bool isInCol(int (&board)[16][16],int j, int c)
	{
		for (int k = 0; k <= 15; k++)
		{
			if (board[k][j] == c)
				return true;
		}
		return false;
	}

	bool isInRec(int (&board)[16][16], int i, int j, int c)
	{
		int bigrow = i / 4, bigcol = j / 4;
		for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
		{
			for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
			{
				if (board[m][n] == c)
					return true;
			}
		}
		return false;
	}
  bool dfs(int (&board)[16][16], int pos)
	{
		//board[0][0] = 6;
		if (pos >= 256)
			return true;
		int i = pos / 16;
		int j = pos % 16;
		if (board[i][j] != 0)
			return dfs(board, pos + 1);
		else
		{
			for (int c = 1; c <= 16; c++)
			{
				if (!isInRow(board, i, c) && !isInCol(board, j, c) && !isInRec(board, i, j, c))
				{
					board[i][j] = c;
					// cout<<"[***Assign:***]"<<i<<" "<<j<<" "<<board[i][j]<<endl;
					if (dfs(board, pos + 1))
						return true;
					else{
						// cout<<"[------recover:------]"<<i<<" "<<j<<" "<<board[i][j]<<endl;
						board[i][j] = 0;
					}
						
				}
			}
			return false;
		}
	}

  int main(){
		ofstream myfile;
		myfile.open("Naive_time.txt");

    int board[16][16];
    // static const char arr[] = { '0','B','9','0','0','G','D','4','0','0','E','0','A','6','F','0',  //Easy
		// 														'4','C','F','0','3','6','0','B','0','5','0','1','G','7','E','2',
		// 														'1','0','6','0','F','2','0','0','B','9','A','0','0','0','8','0',
  	// 														'0','D','0','0','0','1','0','0','4','6','0','F','0','0','0','0',
		// 														'0','0','0','0','0','0','F','0','8','1','5','3','0','4','B','7',
		// 														'6','0','1','0','0','C','8','0','9','0','0','2','0','0','3','0',
		// 														'E','0','4','D','6','0','0','3','0','C','7','A','8','0','2','0',
		// 														'3','8','0','0','4','7','2','0','6','0','0','0','0','C','G','5',
		// 														'D','0','0','G','0','8','E','A','3','4','F','0','C','5','1','B',
		// 														'0','0','0','6','2','0','0','1','A','0','B','0','F','3','0','9',
		// 														'7','0','0','C','0','4','0','F','5','0','9','E','0','0','0','0',
		// 														'A','0','0','8','0','0','B','0','0','0','1','C','4','0','D','G',
		// 														'0','0','0','0','0','0','7','0','F','2','0','0','0','0','C','3',
		// 														'0','0','7','0','0','A','6','0','1','8','0','D','B','0','9','E',
		// 														'8','6','5','0','0','3','0','0','E','0','0','9','0','0','0','0',
		// 														'0','G','0','2','0','0','0','E','0','A','0','0','0','0','0','0'};

		static const char arr[] = { '8','7','0','0','0','0','0','0','0','3','0','0','D','0','4','0',  //Medium
																'0','5','E','0','0','0','3','A','F','9','1','0','0','6','0','0',
																'G','0','0','0','5','8','7','0','0','E','0','0','9','0','B','C',
  															'0','0','4','0','0','E','6','D','0','B','A','C','0','7','0','3',
																'E','0','0','8','0','0','1','0','0','0','0','3','7','4','C','0',
																'9','0','0','0','0','6','F','C','0','0','D','E','0','3','1','0',
																'B','0','A','3','0','0','D','0','0','8','0','1','0','0','6','0',
																'6','0','0','1','E','0','4','0','0','5','0','9','B','0','0','D',
																'0','0','0','0','F','0','0','0','0','0','9','0','5','0','2','A',
																'A','1','0','0','6','0','5','0','D','F','7','G','0','0','0','0',
																'0','0','G','B','0','4','0','8','2','0','0','0','0','D','0','7',
																'0','9','0','7','1','3','0','2','6','0','8','A','G','F','E','4',
																'7','0','D','0','9','G','0','5','0','0','E','4','3','8','0','2',
																'0','0','3','0','A','0','0','0','0','0','0','0','0','G','F','0',
																'1','0','9','0','0','0','E','4','0','0','0','0','0','0','7','0',
																'0','6','8','0','3','0','0','0','A','7','0','0','0','0','0','0'};
		cout<<"[initial]: -------------------------------------------------"<<endl;
    for (int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				int row = i;
	      int col = j;
				int index = i * 16 + j;
	      int temp;
	      switch (arr[index]){
	        case 'A': {temp = 10;break;}
	        case 'B': {temp = 11;break;}
	        case 'C': {temp = 12;break;}
	        case 'D': {temp = 13;break;}
	        case 'E': {temp = 14;break;}
	        case 'F': {temp = 15;break;}
					case 'G': {temp = 16;break;}
	        default:{temp = arr[index]-'0';break;}
	      }
				cout<<temp<<'\t';
	      board[row][col]=temp;
			}
			cout<<endl;
    }
		clock_t start;
    double duration;
    start = clock();  

    dfs(board,0);

		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		cout<< "Time: " << duration*1000 << "ms" << endl;
		myfile << fixed << setprecision(8) << duration*1000 << endl;

		cout<<"[result]: ----------------------------------------------------"<<endl;
    for (int i=0;i<16;i++){
      for (int j=0;j<16;j++){
      cout<<board[i][j]<<'\t';
    }
		cout<<endl;
    }
    return 0;
  }
