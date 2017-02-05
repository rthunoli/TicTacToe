#include<iostream>
#include<string>
#include<array>
#include<vector>

using namespace std;

const string YM = "X";	//your mark
const string MM = "#";  //my mark

class TicTac
{
private:
	string think_stat;
	int think_pos;

	array<string, 9>positions;
	int solutions[8][3];
	struct rnk {
		int position;
		int rank;
	};
	vector<rnk>ranks;

	string checkSolution(const int*);
	string checkSolutions();

	int** getSolutions(int position, int& size);
	int getRank(int position);
	void rankPositions();
	bool continueGame();

public:
	TicTac();
	void restart();
	void showPositions();
	void setPosition(int, string = YM);
	//int getPosition();
	bool validPosition(int pos);
	string think();
	string showStat();
	string getStat();
	int getPos();
};
