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
unordered_map<int, vector<int>> domain; //key is the slot's index in the board, value is this slot's domain, 

int use[16][16][17];
int constraintCount[16][16];
int board[16][16];
bool occupy[16][16];
int constraintCounter[16][16];

void initDomain(int x, int y);

int removeValue(int &value, vector<int> &vec)
{
	for (int i = 0; i<vec.size(); i++)
	{
		if (vec[i] == value)
		{
			vec.erase(vec.begin() + i, vec.begin() + i + 1);
			return 0;
		}

	}
	return -1;
}

void initBoard()
{
	for (int i = 0; i<16; i++)
	{
		for (int j = 0; j<16; j++)
		{
			int index = i * 16 + j;
			if (!occupy[index])
			{
				initDomain(i, j);
			}
		}
	}
}

void initDomain(int x, int y)
{
	int index = x * 16 + y;
	auto it = domain.find(index);
	for (int i = 0; i<16; i++)
	{
		int index2 = i * 16 + y;
		if (!occupy[index2] || i == x) continue;
		else
		{
			removeValue(board[i][y], it->second);
		}
	}

	for (int j = 0; j<16; j++)
	{
		int index2 = x * 16 + j;
		if (!occupy[index2] || j == y) continue;
		else
		{
			removeValue(board[x][j], it->second);
		}
	}

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			int index2 = m * 16 + n;
			if (!occupy[index2] || m == x || n == y) continue;
			removeValue(board[m][n], it->second);
		}
	}

}

int Count(int &x,int &y,int &num){
	int count = 0;
	// cout<<"[Assign]"<<"value:"<<num<<" x:"<<x<<" y:"<<endl;
	for (int i=0 ; i < 16 ; i++){
		if (occupy[x][i])
		{
			if(num == board[x][i])
				count++;
		}
		if (occupy[i][y])
		{
			if(num == board[i][y])
				count++;
		}
	}

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			if (occupy[m][n] && m != x && n != y){
				if(num == board[m][n])
					count++;
			}
		}
	}	
	return count;
}

void Assign(int &x,int &y,int &num){
	board[x][y] = num;
	occupy[x][y] = true;
	// cout<<"[Assign]"<<"value:"<<num<<" x:"<<x<<" y:"<<endl;
	for (int i=0 ; i < 16 ; i++){
		if (!occupy[x][i]){

			if (!use[x][i][num])
			{
				constraintCount[x][i]++;
			}
			use[x][i][num]++;	
		}

		if (!occupy[i][y]){
			if (!use[i][y][num])
			{
				constraintCount[i][y] ++;
			}
			use[i][y][num]++;
		}
			
	}

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			
			if (!occupy[m][n]){
				constraintCounter[m][n]++;
				if (!use[m][n][num]) 
				{
					constraintCount[m][n]++;
				}
				use[m][n][num]++;	
				// if (constraintCount[m][n] == 16) ans = -1;
			}
		}
	}	
}


void Recover(int &x, int &y, int &num){
	for (int i =0 ; i < 16 ; i++){
		if (!occupy[x][i]){
			if (1 == use[x][i][num]) constraintCount[x][i] --;
			use[x][i][num] --;	
		}
		if (!occupy[i][y]){
			if (1 == use[i][y][num]) constraintCount[i][y] --;
			use[i][y][num] --;
		}		
	}
	int bigrow = x / 4, bigcol = y / 4;
	for(int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for(int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			if(!occupy[m][n]){
				// cout<< use[m][n][num]<<endl;
				if (1 == use[m][n][num]) constraintCount[m][n] --;
				use[m][n][num] --;
			}
		}
	}	
	
	board[x][y] = 0;
	occupy[x][y] = 0;
}

bool SortByValueConstraint(pair<int,int> p1,pair<int,int> p2)
{
	p1.first < p2.first;
}

int getMostConstraintVariable()
{
	int nx=0, ny=0, max = -1;

	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			if (occupy[i][j]) continue;
			if (constraintCount[i][j] > max){
				max = constraintCount[i][j];
				nx = i, ny = j;
			}
		}
	}
	if(max == -1) return -1;
	int x = nx * 16 + ny;
	return x;
}

void getLeastRectrictValue(vector<pair<int,int>> &vec, vector<int> &domain, int &x,int &y)
{
	for (int c = 0; c < domain.size(); c++)
	{
		int num = domain[c];
		if (!use[x][y][num]){
			// cout<< num << endl;
			int count = Count(x,y,num);
			//Recover(nx,ny);
			vec.push_back(make_pair(count,num));
		}
	}
	sort(vec.begin(),vec.end(), SortByValueConstraint);
}


bool dfs()
{
	int index = getMostConstraintVariable();
	
	if(index == -1) 
		return true;

	int x = index / 16;
	int y = index % 16;

	auto it = domain.find(index);
	vector<pair<int,int> > valueConstraint;
	getLeastRectrictValue(valueConstraint, it->second,x,y);
	
	for(int i=0;i<valueConstraint.size();i++)
	{
		Assign(x,y,valueConstraint[i].second);
		if(dfs()) 
			return true;
		Recover(x,y,valueConstraint[i].second);
	}
	return false;
}

int main() {

	vector<int> originVec;
	for (int i = 1; i <= 16; i++)
	{
		originVec.push_back(i);
		// valueCount.insert(make_pair(i,0));
		
	}
		
	ofstream myfile;
	myfile.open("CSP_Time.txt", std::ofstream::out | std::ofstream::app);

	string fileName = "hexa1.txt";
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
			for(int i=0;i<16;i++)
			{
				for(int j=0;j<16;j++)
				{
					if(board[i][j]){
						occupy[i][j] = true;
						Assign(i,j,board[i][j]);
						// cout << i <<" "<< j << endl;
						// cout <<use[1][2][1] <<endl;
					}
				}
			}
			if (temp == 0)
			{
				domain.insert(make_pair(index, originVec));
			}
			// else
			// {
			// 	auto ite = valueCount.find(temp);
			// 	if (ite != valueCount.end())
			// 	{
			// 		ite->second++;
			// 	}
			// }

		}
		cout << endl;
	}

	clock_t start;
	double duration;
	start = clock();

	//initBoard();
	dfs();
	// initBoard();
	// int pos = getMostConstraintVariable();
	// dfs(board, pos);

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << fileName<<" Time: " << duration * 1000 << "ms" << endl;
	myfile << fixed << setprecision(6) << duration * 1000 << endl;

	// cout << "[result]: ----------------------------------------------------" << endl;
	// for (int i = 0; i<16; i++) {
	// 	for (int j = 0; j<16; j++) {
	// 		cout << board[i][j] << '\t';
	// 	}
	// 	cout << endl;
	// }

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
