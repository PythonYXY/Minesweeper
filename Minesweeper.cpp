/*
-------------------------------------------------------------------------------
Name:        Minesweeper
Purpose:     Entertainment

Author:      Xinyan

Created:     11/03/2015
Copyright:   (c) Xinyan 2015
version:     1.0
-------------------------------------------------------------------------------
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

int field[11][11] = {0};

void init(int row, int col)
{
	srand((unsigned)time(0));
	int cnt = 0, bomb_r, bomb_c;

	while(cnt != 10){
		int temp = rand() % 81 + 1;
		bomb_r = temp / 9 + 1;
		bomb_c = temp % 9 + 1;
		if(bomb_r == row || bomb_c == col || field[bomb_r][bomb_c] == -1) continue;
		field[bomb_r][bomb_c] = -1;
		cnt++;
	}
}

void print()
{
	cout << "     ";
	for(int i = 1; i < 10; i++) cout << setw(3) << setiosflags(ios::left) << i << ' ';
	cout << endl << "   " << "------------------------------------" << endl;
	for(int i = 1; i < 10; i++){
		cout << setw(3) << setiosflags(ios::left) << i << "| ";
		for(int j = 1; j < 10; j++){
			if(field[i][j] == 9 || field[i][j] == -1) cout << setw(3) << '.' << ' ';
			else if (field[i][j] == 0) cout << setw(3) << ' ' << ' ';
			else cout << setw(3) << field[i][j] << ' ';
		}
		cout << endl << "   |" << endl;
	}
	cout << endl;
}

bool judge()
{
	for(int i = 1; i <=9; i++){
		for(int j = 1; j <= 9; j++){
			if (field[i][j] == 9) return false;
		}
	}
	return true;
}

int dfs(int r, int c)
{
	int cnt = 0;
	for (int i = c - 1; i <= c + 1; i++){
		if(field[r - 1][i] == -1) cnt++;
		if(field[r + 1][i] == -1) cnt++;
	}
	if(field[r][c - 1] == -1) cnt++;
	if(field[r][c + 1] == -1) cnt++;

	field[r][c] = cnt;
	if (cnt != 0) return 0;

	if (r > 1 && field[r - 1][c] != 0) dfs(r - 1, c);
	if (r < 9 && field[r + 1][c] != 0) dfs(r + 1, c);
	if (c > 1 && field[r][c - 1] != 0) dfs(r, c - 1);
	if (c < 9 && field[r][c + 1] != 0) dfs(r, c + 1);

	if(r > 1 && c > 1 && field[r - 1][c - 1] != 0) dfs(r - 1, c - 1);
	if(r > 1 && c < 9 && field[r - 1][c + 1] != 0) dfs(r - 1, c + 1);
	if(r < 9 && c > 1 && field[r + 1][c - 1] != 0) dfs(r + 1, c - 1);
	if(r < 9 && c < 9 && field[r + 1][c + 1] != 0) dfs(r + 1, c + 1);
	return 0;
}

int main()
{
    bool first = true;
    for(int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++) field[i][j] = 9;

	int r, c;
	cin >> r >> c;
	cout << endl;

	while(1){
		if(first){
			init(r, c);
			dfs(r, c);
			print();
			first = false;
			if(judge()) {cout << "You Win!"; break;}
			continue;
		}
		cin >> r >> c;
		if(field[r][c] == -1){cout << "You Lose!"; break;}

		dfs(r, c);
		print();
		if(judge()) {cout << "You Win!"; break;}

	}
	cin >> r;
	return 0;
}
