#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class FallingSand {
    public:
    vector<string> simulate(vector<string> board) {
        int n=board.size(),len=board[0].length();
	for(int i=n-2;i>=0;--i)
	{
		for(int j=0;j<len;++j) if(board[i][j]=='o')
		{
			int i1=i;
			board[i1][j]='.';
			while(i1+1<n && board[i1+1][j]=='.') ++i1;
			board[i1][j]='o';
		}
	}
	return board;
    }
};

