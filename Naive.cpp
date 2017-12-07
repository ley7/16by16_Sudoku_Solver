#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <assert.h>
#include <unordered_map>
using namespace std;

int board[16][16];
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
					cout<<"[***Assign:***]"<<i<<" "<<j<<" "<<board[i][j]<<endl;
					if (dfs(board, pos + 1))
						return true;
					else{
						cout<<"[------recover:------]"<<i<<" "<<j<<" "<<board[i][j]<<endl;
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

string fileName = "hexa7.txt";
	ifstream infile; 
	char arr[256];
	infile.open(fileName);   
	assert(infile.is_open());
    char c;
	int count = 0;
    while (!infile.eof())
    {
        infile >> c;
		 cout<<c<<" ";
        arr[count] = c;
		count++;
    }
	cout<<endl;
    infile.close();   

		// static const char arr[] = { '8','7','0','0','0','0','0','0','0','3','0','0','D','0','4','0',  //Medium
		// '0','5','E','0','0','0','3','A','F','9','1','0','0','6','0','0',
		// 'G','0','0','0','5','8','7','0','0','E','0','0','9','0','B','C',
		// '0','0','4','0','0','E','6','D','0','B','A','C','0','7','0','3',
		// 'E','0','0','8','0','0','1','0','0','0','0','3','7','4','C','0',
		// '9','0','0','0','0','6','F','C','0','0','D','E','0','3','1','0',
		// 'B','0','A','3','0','0','D','0','0','8','0','1','0','0','6','0',
		// '6','0','0','1','E','0','4','0','0','5','0','9','B','0','0','D',
		// '0','0','0','0','F','0','0','0','0','0','9','0','5','0','2','A',
		// 'A','1','0','0','6','0','5','0','D','F','7','G','0','0','0','0',
		// '0','0','G','B','0','4','0','8','2','0','0','0','0','D','0','7',
		// '0','9','0','7','1','3','0','2','6','0','8','A','G','F','E','4',
		// '7','0','D','0','9','G','0','5','0','0','E','4','3','8','0','2',
		// '0','0','3','0','A','0','0','0','0','0','0','0','0','G','F','0',
		// '1','0','9','0','0','0','E','4','0','0','0','0','0','0','7','0',
		// '0','6','8','0','3','0','0','0','A','7','0','0','0','0','0','0' };         

	cout << "[initial]: -------------------------------------------------" << endl;
	for (int i = 0; i<16; i++) {
		for (int j = 0; j<16; j++) {
			int row = i;
			int col = j;
			int index = i * 16 + j;
			// domainSize.push_back(index);
			int temp;
			switch (arr[index]) {
			case 'A': {temp = 10; break; }
			case 'B': {temp = 11; break; }
			case 'C': {temp = 12; break; }
			case 'D': {temp = 13; break; }
			case 'E': {temp = 14; break; }
			case 'F': {temp = 15; break; }
			case 'G': {temp = 16; break; }
			case '*': {temp = -1; break; }
			default: {temp = arr[index] - '0'; break; }
			}
			cout << temp << '\t';
			temp++;
			board[i][j] = temp;
		}
		cout << endl;
	}

		clock_t start;
    double duration;
    start = clock();  

    dfs(board,0);

		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		cout<< "Time: " << duration*1000 << "ms" << endl;
		myfile << fixed << setprecision(8) << duration*1000 << endl;

		cout << "[standard result]: ----------------------------------------------------" << endl;
	for (int i = 0; i<16; i++) {
		for (int j = 0; j<16; j++) {
			board[i][j]--;
			switch (board[i][j]) {
			case 10: {cout << 'A' << '\t'; break; }
			case 11: {cout << 'B' << '\t'; break; }
			case 12: {cout << 'C' << '\t'; break; }
			case 13: {cout << 'D' << '\t'; break; }
			case 14: {cout << 'E' << '\t'; break; }
			case 15: {cout << 'F' << '\t'; break; }
			case 16: {cout << 'G' << '\t'; break; }
			default: {cout << board[i][j] << '\t'; break; }
			}
		}
		cout << endl;
	}
    return 0;
  }
