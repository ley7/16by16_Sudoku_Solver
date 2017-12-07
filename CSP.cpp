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

// unordered_map<int, int> domainCount; //key is the slot's index in the board, value is this slot's domain, 
// 										//based on this we can find the most constraint vaiable
// void assignValue(int &x, int &y, int &value);
// int addConstraint(int &x, int &y, int &value);
// int removeConstraint(int &x, int &y, int &value);
// int recoverValue(int &x, int &y, int &value);

// bool use[256];
// int board[16][16];
// vector<int> domainSize;
// unordered_map<int, int> valueCount;  //to maintain a value count, track the number of the same value used in the board, 
// 									//based on this we can find the least restricting value
// bool isDone()
// {
// 	bool success = true;
// 	for (int i = 0; i < 256; i++)
// 	{
// 		success &= use[i];
// 		if (!success) break;
// 	}
// 	return success;
// }
// bool SortByDomainSize(int &v1,int &v2)
// {
// 	auto ite = domain.find(v1);
// 	int size1;
// 	int size2;
// 	if (ite != domain.end())
// 	{
// 		size1 = ite->second;
// 	}
// 	ite = domain.find(v2);
// 	if (ite != domain.end())
// 	{
// 		size2 = ite->second.size();
// 	}
// 	return size1 < size2;
// }

// int getMostConstraintVariable()
// {
// 	int minSize = 17;
// 	int index = 0;
// 	for (auto it = domain.begin(); it != domain.end(); ++it)
// 	{
// 		if (use[it->first]) continue;
// 		if (it->second.size() > 16)
// 			cout << "something is wrong!!" << endl;
// 		if (it->second.size() < minSize)
// 		{
// 			index = it->first;
// 			minSize = it->second.size();
// 		}
// 	}
// 	return index;
// 	sort(domainSize.begin(),domainSize.end(),SortByDomainSize);
// }

// // int getLeastConstraintValue(vector<int> &vec)
// // {
// // 	int min = 0;
// // 	int value;
// // 	if(vec.size() > 0) 
// // 		value = vec[0];
// // 	for(int i=0;i<vec.size();i++)
// // 	{
// // 		auto ite = valueCount.find(vec[i]);
// // 		if (ite != domain.end())
// // 		{
// // 			if(ite->second < min)
// // 			{
// // 				min = ite->second;
// // 				value = ite->first;
// // 			}

// // 		}
// // 	}
// // 	return value;
// // }

// int removeValue(int &value, vector<int> &vec)
// {
// 	for (int i = 0; i<vec.size(); i++)
// 	{
// 		if (vec[i] == value)
// 		{
// 			vec.erase(vec.begin() + i, vec.begin() + i + 1);
// 			return 0;
// 		}

// 	}
// 	return -1;
// }

// int addValue(int &value, vector<int> &vec)
// {
// 	vec.push_back(value);
// 	return 0;
// }

// void assignValue(int &x, int &y, int &value)
// {
// 	int index = x * 16 + y;
// 	use[index] = true;
// 	board[x][y] = value;
// 	cout << "[assign value] value:" << value << " x:" << x << " y:" << y << endl;
// 	auto ite = valueCount.find(value);
// 	if (ite != valueCount.end())
// 	{
// 		ite->second++;
// 	}
// 	addConstraint(x, y, value);
// 	if (value == 2 && x == 11 && y == 6)
// 		cout << "here" << endl;
// }

// int recoverValue(int &x, int &y, int &value)
// {
// 	int index = x * 16 + y;
// 	use[index] = false;
// 	board[x][y] = 0;
// 	cout << "[recover value] value:" << value << " x:" << x << " y:" << y << endl;
// 	auto ite = valueCount.find(value);
// 	if (ite != valueCount.end())
// 	{
// 		ite->second = ite->second - 1;
// 	}
	
// 	removeConstraint(x, y, value);
// }

// void initDomain(int x, int y)
// {
// 	int index = x * 16 + y;
// 	auto it = domain.find(index);
// 	for (int i = 0; i<16; i++)
// 	{
// 		int index2 = i * 16 + y;
// 		if (!use[index2] || i == x) continue;
// 		else
// 		{
// 			removeValue(board[i][y], it->second);
// 		}
// 	}

// 	for (int j = 0; j<16; j++)
// 	{
// 		int index2 = x * 16 + j;
// 		if (!use[index2] || j == y) continue;
// 		else
// 		{
// 			removeValue(board[x][j], it->second);
// 		}
// 	}

// 	int bigrow = x / 4, bigcol = y / 4;
// 	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
// 	{
// 		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
// 		{
// 			int index2 = m * 16 + n;
// 			if (!use[index2] || m == x || n == y) continue;
// 			removeValue(board[m][n], it->second);
// 		}
// 	}

// }

// int removeConstraint(int &x, int &y, int &value)
// {
// 	int index;
// 	for (int i = 0; i<16; i++)
// 	{
// 		index = i * 16 + y;
// 		if (i == x || use[index]) continue;
// 		else
// 		{
// 			auto ite = domain.find(index);
// 			if (ite != domain.end())
// 			{
// 				addValue(value, ite->second);
// 			}
// 			else
// 			{
// 				vector<int> v;
// 				v.push_back(value);
// 				domain.insert(make_pair(index, v));
// 			}
// 		}
// 	}

// 	for (int j = 0; j<16; j++)
// 	{
// 		index = x * 16 + j;
// 		if (j == y || use[index]) continue;
// 		else
// 		{
// 			auto ite2 = domain.find(index);
// 			if (ite2 != domain.end())
// 			{
// 				addValue(value, ite2->second);
// 			}
// 			else
// 			{
// 				vector<int> v;
// 				v.push_back(value);
// 				domain.insert(make_pair(index, v));
// 			}
// 		}
// 	}

// 	int bigrow = x / 4, bigcol = y / 4;
// 	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
// 	{
// 		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
// 		{
// 			index = m * 16 + n;
// 			if (m == x || n == y || use[index]) continue;

// 			auto ite3 = domain.find(index);
// 			if (ite3 != domain.end())
// 			{
// 				addValue(value, ite3->second);
// 			}
// 			else
// 			{
// 				vector<int> v;
// 				v.push_back(value);
// 				domain.insert(make_pair(index, v));
// 			}

// 		}
// 	}
// 	return 0;

// }

// int addConstraint(int &x, int &y, int &value)
// {
// 	int index;
// 	for (int i = 0; i<16; i++)
// 	{
// 		index = i * 16 + y;
// 		if (i == x || use[index]) continue;
// 		else
// 		{
// 			auto ite = domain.find(index);
// 			if (ite != domain.end())
// 			{
// 				removeValue(value, ite->second);
// 				if (ite->second.size() == 1)
// 					assignValue(i, y, ite->second[0]);
// 			}
// 		}
// 	}

// 	for (int j = 0; j<16; j++)
// 	{
// 		index = x * 16 + j;
// 		if (j == y || use[index]) continue;
// 		else
// 		{
// 			auto ite2 = domain.find(index);
// 			if (ite2 != domain.end())
// 			{
// 				removeValue(value, ite2->second);
// 				if (ite2->second.size() == 1)
// 					assignValue(x, j, ite2->second[0]);
// 			}
// 		}
// 	}

// 	int bigrow = x / 4, bigcol = y / 4;
// 	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
// 	{
// 		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
// 		{
// 			index = m * 16 + n;
// 			if (m == x || n == y || use[index]) continue;

// 			auto ite3 = domain.find(index);
// 			if (ite3 != domain.end())
// 			{
// 				removeValue(value, ite3->second);
// 				if (ite3->second.size() == 1)
// 					assignValue(m, n, ite3->second[0]);
// 			}

// 		}
// 	}
// 	return 0;
// }

// void initBoard()
// {
// 	for (int i = 0; i<16; i++)
// 	{
// 		for (int j = 0; j<16; j++)
// 		{
// 			int index = i * 16 + j;
// 			if (!use[index])
// 			{
// 				initDomain(i, j);
// 			}
// 		}
// 	}
// }

// bool SortByValueConstraint(int &value1, int &value2)
// {
// 	int constraint1;
// 	int constraint2;
// 	auto ite1 = valueCount.find(value1);
// 	auto ite2 = valueCount.find(value2);

// 	if (ite1 != valueCount.end())
// 	{
// 		constraint1 = ite1->second;
// 	}
// 	if (ite2 != valueCount.end())
// 	{
// 		constraint2 = ite2->second;
// 	}
// 	return constraint1 < constraint2;
// }

// bool checkDomain()
// {
// 	for (auto it = domain.begin(); it != domain.end(); ++it)
// 	{
// 		if(it->second.size() > 1) return false;
// 	}
// 	return true;
// }


int use[16][16][17], constraintCount[16][16], board[16][16];
bool occupy[16][16];

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
			if (!use[index])
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
		if (!use[index2] || i == x) continue;
		else
		{
			removeValue(board[i][y], it->second);
		}
	}

	for (int j = 0; j<16; j++)
	{
		int index2 = x * 16 + j;
		if (!use[index2] || j == y) continue;
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
			if (!use[index2] || m == x || n == y) continue;
			removeValue(board[m][n], it->second);
		}
	}

}

int constraintCounter[16][16];
int Count(int &x,int &y,int &num){
	int ans = 0;
	// cout<<"[Put]"<<"value:"<<num<<" x:"<<x<<" y:"<<endl;
	for (int i=0 ; i < 16 ; i++){
		if (occupy[x][i])
		{
			if(num == board[x][i])
				ans++;
		}
		if (occupy[i][y])
		{
			if(num == board[i][y])
				ans++;
		}
	}

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			if (occupy[m][n] && m != x && n != y){
				if(num == board[m][n])
					ans++;
			}
		}
	}	
	return ans;
}

int Put(int &x,int &y,int &num){
	int ans = 0;
	board[x][y] = num;
	occupy[x][y] = true;
	// cout<<"[Put]"<<"value:"<<num<<" x:"<<x<<" y:"<<endl;
	for (int i=0 ; i < 16 ; i++){
		if (!occupy[x][i]){

			if (!use[x][i][num])
			{
				constraintCount[x][i]++;
				ans++;
			}
			use[x][i][num]++;	
			// if (constraintCount[x][i] == 16) ans = -1;
		}


		if (!occupy[i][y]){
			if (!use[i][y][num])
			{
				constraintCount[i][y] ++;
				// constraintCounter[i][y]++;
				ans++;
			}
			use[i][y][num]++;
			// if (constraintCount[i][y] == 16) ans = -1;
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
					constraintCount[m][n] ++;
					 ans ++;
				}
				use[m][n][num] ++;	
				// if (constraintCount[m][n] == 16) ans = -1;
			}
		}
	}	
	return ans;
}


void Take(int &x, int &y){
	int num = board[x][y];
	int xx = x / 3 * 3, yy = y / 3 * 3;

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			if (!occupy[m][n]){
				if (1 == use[m][n][num]) constraintCount[m][n] --;
				use[m][n][num] --;
			}
		}
	}	


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
	
	board[x][y] = 0;
	occupy[x][y] = 0;
}

bool SortByValueConstraint(pair<int,int> p1,pair<int,int> p2)
{
	p1.first < p2.first;
}

bool dfs()
{
	int nx=0, ny=0, mcnt = -1;
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			if (occupy[i][j]) continue;
			if (constraintCount[i][j] > mcnt){
				mcnt = constraintCount[i][j];
				nx = i, ny = j;
			}
		}
	}
	// cout << nx << " "<< ny << " "<<constraintCounter[nx][ny] <<  endl;
	// cout << mcnt << endl;
	if(mcnt == -1) return 1;
	vector<pair<int,int> > w;
	int pos = nx*16+ny;
	auto it = domain.find(pos);

	for (int c = 0; c < it->second.size(); c++)
	{
		int num = it->second[c];
		if (!use[nx][ny][num]){
			// cout<< num << endl;
			int eff = Count(nx,ny,num);
			//Take(nx,ny);
			w.push_back(make_pair(eff,num));
		}
	}
	
	sort(w.begin(),w.end(), SortByValueConstraint);
	for(int i=0;i<w.size();i++)
	{
		Put(nx,ny,w[i].second);
		if (dfs()) return 1;
		Take(nx,ny);
	}
	return 0;
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
						Put(i,j,board[i][j]);
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

	initBoard();
	dfs();
	// initBoard();
	// int pos = getMostConstraintVariable();
	// dfs(board, pos);

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << fileName<<" Time: " << duration * 1000 << "ms" << endl;
	myfile << fixed << setprecision(8) << duration * 1000 << endl;

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
