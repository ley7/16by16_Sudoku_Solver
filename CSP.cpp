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
										//based on this we can find the most constraint vaiable
void assignValue(int &x, int &y, int &value);
int addConstraint(int &x, int &y, int &value);
int removeConstraint(int &x, int &y, int &value);
int recoverValue(int &x, int &y, int &value);

bool use[256];
int board[16][16];

unordered_map<int, int> valueCount;  //to maintain a value count, track the number of the same value used in the board, 
									//based on this we can find the least restricting value
bool isDone()
{
	bool success = true;
	for (int i = 0; i < 256; i++)
	{
		success &= use[i];
		if (!success) break;
	}
	return success;
}

int getMostConstraintVariable()
{
	int minSize = 17;
	int index = 0;
	for (auto it = domain.begin(); it != domain.end(); ++it)
	{
		if (use[it->first]) continue;
		if (it->second.size() > 16)
			cout << "something is wrong!!" << endl;
		if (it->second.size() < minSize)
		{
			index = it->first;
			minSize = it->second.size();
		}
	}
	return index;
}

// int getLeastConstraintValue(vector<int> &vec)
// {
// 	int min = 0;
// 	int value;
// 	if(vec.size() > 0) 
// 		value = vec[0];
// 	for(int i=0;i<vec.size();i++)
// 	{
// 		auto ite = valueCount.find(vec[i]);
// 		if (ite != domain.end())
// 		{
// 			if(ite->second < min)
// 			{
// 				min = ite->second;
// 				value = ite->first;
// 			}

// 		}
// 	}
// 	return value;
// }

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

int addValue(int &value, vector<int> &vec)
{
	vec.push_back(value);
	return 0;
}

void assignValue(int &x, int &y, int &value)
{
	int index = x * 16 + y;
	use[index] = true;
	board[x][y] = value;
	// cout << "[assign value] value:" << value << " x:" << x << " y:" << y << endl;
	auto ite = valueCount.find(value);
	if (ite != valueCount.end())
	{
		ite->second++;
	}
	addConstraint(x, y, value);
	if (value == 2 && x == 11 && y == 6)
		cout << "here" << endl;
}

int recoverValue(int &x, int &y, int &value)
{
	int index = x * 16 + y;
	use[index] = false;
	board[x][y] = 0;
	// cout << "[recover value] value:" << value << " x:" << x << " y:" << y << endl;
	auto ite = valueCount.find(value);
	if (ite != valueCount.end())
	{
		ite->second = ite->second - 1;
	}
	
	removeConstraint(x, y, value);
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

int removeConstraint(int &x, int &y, int &value)
{
	int index;
	for (int i = 0; i<16; i++)
	{
		index = i * 16 + y;
		if (i == x || use[index]) continue;
		else
		{
			auto ite = domain.find(index);
			if (ite != domain.end())
			{
				addValue(value, ite->second);
			}
			else
			{
				vector<int> v;
				v.push_back(value);
				domain.insert(make_pair(index, v));
			}
		}
	}

	for (int j = 0; j<16; j++)
	{
		index = x * 16 + j;
		if (j == y || use[index]) continue;
		else
		{
			auto ite2 = domain.find(index);
			if (ite2 != domain.end())
			{
				addValue(value, ite2->second);
			}
			else
			{
				vector<int> v;
				v.push_back(value);
				domain.insert(make_pair(index, v));
			}
		}
	}

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			index = m * 16 + n;
			if (m == x || n == y || use[index]) continue;

			auto ite3 = domain.find(index);
			if (ite3 != domain.end())
			{
				addValue(value, ite3->second);
			}
			else
			{
				vector<int> v;
				v.push_back(value);
				domain.insert(make_pair(index, v));
			}

		}
	}
	return 0;

}

int addConstraint(int &x, int &y, int &value)
{
	int index;
	for (int i = 0; i<16; i++)
	{
		index = i * 16 + y;
		if (i == x || use[index]) continue;
		else
		{
			auto ite = domain.find(index);
			if (ite != domain.end())
			{
				removeValue(value, ite->second);
				if (ite->second.size() == 1)
					assignValue(i, y, ite->second[0]);
			}
		}
	}

	for (int j = 0; j<16; j++)
	{
		index = x * 16 + j;
		if (j == y || use[index]) continue;
		else
		{
			auto ite2 = domain.find(index);
			if (ite2 != domain.end())
			{
				removeValue(value, ite2->second);
				if (ite2->second.size() == 1)
					assignValue(x, j, ite2->second[0]);
			}
		}
	}

	int bigrow = x / 4, bigcol = y / 4;
	for (int m = 4 * bigrow; m < 4 * (bigrow + 1); m++)
	{
		for (int n = 4 * bigcol; n < 4 * (bigcol + 1); n++)
		{
			index = m * 16 + n;
			if (m == x || n == y || use[index]) continue;

			auto ite3 = domain.find(index);
			if (ite3 != domain.end())
			{
				removeValue(value, ite3->second);
				if (ite3->second.size() == 1)
					assignValue(m, n, ite3->second[0]);
			}

		}
	}
	return 0;
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

bool SortByValueConstraint(int &value1, int &value2)
{
	int constraint1;
	int constraint2;
	auto ite1 = valueCount.find(value1);
	auto ite2 = valueCount.find(value2);

	if (ite1 != valueCount.end())
	{
		constraint1 = ite1->second;
	}
	if (ite2 != valueCount.end())
	{
		constraint2 = ite2->second;
	}
	return constraint1 < constraint2;
}

bool dfs(int(&board)[16][16], int pos)
{
	if (isDone())
	{
		// for(int )
		// if (domain.size() == 0)
			return true;
	}
	int i = pos / 16;
	int j = pos % 16;

	if (board[i][j] != 0)
	{
		pos = getMostConstraintVariable();
		return dfs(board, pos);
	}

	else
	{
		auto it = domain.find(pos);
		sort(it->second.begin(),it->second.end(),SortByValueConstraint);	//sort by the the possible values constraints, want to choose the least restricting value
		// cout<<"sort:";
		// for(int i=0;i<it->second.size();i++)
		// {
		// 	auto ite = valueCount.find(it->second[i]);
		// 	int x;
		// 	if (ite != valueCount.end())
		// 	{
		// 		x = ite->second;
		// 	}
		// 	cout<<it->second[i]<<" "<<x<<"     ";
		// }
		// cout<<endl;
		for (int c = 0; c < it->second.size(); c++)
		{
			int value = it->second[c];

			board[i][j] = c;

			assignValue(i, j, value);
			pos = getMostConstraintVariable();
			if (dfs(board, pos))
				return true;
			else {
				recoverValue(i, j, value);
			}
		}
		return false;
	}
}

int main() {

	vector<int> originVec;
	for (int i = 1; i <= 16; i++)
	{
		originVec.push_back(i);
		valueCount.insert(make_pair(i,0));
	}
		
	ofstream myfile;
	myfile.open("CSP_Time.txt");


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

	// static const char arr[] = { '8','7','0','0','0','0','0','0','0','3','0','0','D','0','4','0',  //Medium
	// 	'0','5','E','0','0','0','3','A','F','9','1','0','0','6','0','0',
	// 	'G','0','0','0','5','8','7','0','0','E','0','0','9','0','B','C',
	// 	'0','0','4','0','0','E','6','D','0','B','A','C','0','7','0','3',
	// 	'E','0','0','8','0','0','1','0','0','0','0','3','7','4','C','0',
	// 	'9','0','0','0','0','6','F','C','0','0','D','E','0','3','1','0',
	// 	'B','0','A','3','0','0','D','0','0','8','0','1','0','0','6','0',
	// 	'6','0','0','1','E','0','4','0','0','5','0','9','B','0','0','D',
	// 	'0','0','0','0','F','0','0','0','0','0','9','0','5','0','2','A',
	// 	'A','1','0','0','6','0','5','0','D','F','7','G','0','0','0','0',
	// 	'0','0','G','B','0','4','0','8','2','0','0','0','0','D','0','7',
	// 	'0','9','0','7','1','3','0','2','6','0','8','A','G','F','E','4',
	// 	'7','0','D','0','9','G','0','5','0','0','E','4','3','8','0','2',
	// 	'0','0','3','0','A','0','0','0','0','0','0','0','0','G','F','0',
	// 	'1','0','9','0','0','0','E','4','0','0','0','0','0','0','7','0',
	// 	'0','6','8','0','3','0','0','0','A','7','0','0','0','0','0','0' };

		// 'C'  'E'  '*'  'F'   '*'  '*'  '4'  '*'   '*'  '*'  '*'  9   5  *  *  * 
		// *  *  8  *   *  A  *  F   *  *  *  *   *  *  *  * 
		// *  *  A  4   C  *  7  *   D  *  0  *   6  *  3  * 
		// 6  2  *  *   0  *  *  *   5  *  *  *   *  *  8  C 

		// 0  *  *  8   2  *  *  *   *  *  *  *   *  *  *  * 
		// *  *  *  6   *  *  *  *   E  *  *  4   *  *  A  D 
		// *  *  *  *   3  *  *  *   *  *  *  C   *  6  *  2 
		// *  C  *  7   *  F  *  5   *  1  *  *   *  *  *  * 

		// 9  *  *  *   A  3  0  *   *  *  C  *   *  *  D  E 
		// *  *  *  5   8  D  *  6   *  2  *  E   7  C  *  F 
		// *  A  *  *   9  *  *  *   *  *  1  *   2  *  *  3 
		// *  1  D  2   *  *  E  *   F  *  *  *   *  *  B  * 

		// *  9  *  3   D  *  *  C   8  4  *  *   *  *  0  5 
		// *  *  *  *   *  *  *  *   B  *  5  D   *  4  2  A 
		// *  *  7  *   *  *  *  B   *  E  3  A   C  *  *  * 
		// *  B  2  *   *  *  6  *   *  *  9  *   *  F  *  * 
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
			board[row][col] = temp;
			use[index] = true;
			if (temp == 0)
			{
				use[index] = false;
				domain.insert(make_pair(index, originVec));
			}
			else
			{
				auto ite = valueCount.find(temp);
				if (ite != valueCount.end())
				{
					ite->second++;
				}
			}

		}
		cout << endl;
	}
	clock_t start;
	double duration;
	start = clock();

	initBoard();
	int pos = getMostConstraintVariable();
	dfs(board, pos);

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Time: " << duration * 1000 << "ms" << endl;
	myfile << fixed << setprecision(8) << duration * 1000 << endl;

	cout << "[result]: ----------------------------------------------------" << endl;
	for (int i = 0; i<16; i++) {
		for (int j = 0; j<16; j++) {
			cout << board[i][j] << '\t';
		}
		cout << endl;
	}

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
