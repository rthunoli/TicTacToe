#include"Tictac.h"
using namespace std;

TicTac::TicTac()
{
	solutions[0][0] = 0;
	solutions[0][1] = 1;
	solutions[0][2] = 2;

	solutions[1][0] = 3;
	solutions[1][1] = 4;
	solutions[1][2] = 5;

	solutions[2][0] = 6;
	solutions[2][1] = 7;
	solutions[2][2] = 8;

	solutions[3][0] = 0;
	solutions[3][1] = 3;
	solutions[3][2] = 6;

	solutions[4][0] = 1;
	solutions[4][1] = 4;
	solutions[4][2] = 7;

	solutions[5][0] = 2;
	solutions[5][1] = 5;
	solutions[5][2] = 8;

	solutions[6][0] = 0;
	solutions[6][1] = 4;
	solutions[6][2] = 8;

	solutions[7][0] = 2;
	solutions[7][1] = 4;
	solutions[7][2] = 6;
}

//void TicTac::showPositions()
//{
//
//	for (int i = 0; i < 9; i++) {
//		cout << positions[i] << "\t";
//		if (i > 0 && ((i + 1) % 3 == 0))
//			cout << endl;
//
//	}
//}

void TicTac::setPosition(int pos = -1, string mark)
{
	if (pos > -1) {
		pos--;
		positions[pos] = mark;
	}
}

string TicTac::checkSolution(const int* p)
{
	if (positions[p[0]] == YM && positions[p[1]] == YM && positions[p[2]] == YM)
		return "u"; //user wins

	if (positions[p[0]] == MM && positions[p[1]] == MM && positions[p[2]] == MM)
		return "c"; //computer wins

	return "x";
}

string TicTac::checkSolutions()
{
	string result;
	for (int i = 0; i < 8; i++) {
		result = checkSolution(solutions[i]);
		if (result != "x")
			return result;
	}
	for (int i = 0; i < 9; i++) {
		if (positions[i] != YM && positions[i] != MM)
			return "x";
	}
	return "t"; //tie
}

void TicTac::restart()
{
	positions[0] = "1"; positions[1] = "2"; positions[2] = "3";

	positions[3] = "4"; positions[4] = "5"; positions[5] = "6";

	positions[6] = "7"; positions[7] = "8"; positions[8] = "9";

	system("cls");

	//ofstream of("ranks.txt", ios::trunc);
}

int** TicTac::getSolutions(int position, int& size)
{

	int k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if (solutions[i][j] == position)
				k++;
		}
	}

	size = k;
	int** ptr;
	ptr = new int*[k];

	k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++)
			if (solutions[i][j] == position) {
				ptr[k] = solutions[i];
				k++;
			}
	}
	return ptr;
}

int TicTac::getRank(int position)
{
	int size;
	int** ptr;
	int p;
	int rank = 0;
	int totrank = 0;
	string prev = "";
	ptr = getSolutions(position, size);

	for (int i = 0; i < size; i++) {
		totrank += rank;
		rank = 0;
		prev = "";
		for (int j = 0; j < 3; j++) {
			p = ptr[i][j];
			if (p != position) {
				if (positions[p] == YM || positions[p] == MM) {
					if (prev == "") {
						rank++;
					}
					else if (prev == positions[p]) {
						if (prev == MM)
							rank += 100;
						else
							rank += 50;
					}
					else {
						rank--;
					}
					prev = positions[p];
				}
			}
		}
	}
	totrank += rank;

	delete[] ptr;
	ptr = nullptr;

	return totrank;
}

void TicTac::rankPositions()
{
	ranks.resize(0);
	for (int i = 0; i < 9; i++) {
		if (positions[i] != YM && positions[i] != MM) {
			ranks.resize(ranks.size() + 1);
			rnk r;
			r.position = i;
			r.rank = getRank(i);
			ranks[ranks.size() - 1] = r;
		}
	}
}

bool TicTac::continueGame()
{
	string ans;
	cout << "Continue game? (y/n) : ";
	cin >> ans;
	if (ans == "Y" || ans == "y") {
		restart();
		//showPositions();
		return true;
	}
	else {
		return false;
	}
}

string TicTac::think()
{
	string r;
	r = checkSolutions();

	if (r == "u") {
		//showPositions();
		cout << "Congrats you win!" << endl;
		think_stat = "uw";
		/*if (continueGame())
		return "";
		else
		return "n";*/
		return "n";
	}
	else if (r == "t") {
		//showPositions();
		cout << "Tied!" << endl;
		think_stat = "ti";
		//if (continueGame())
		//	return "";
		//else
		//	return "n";
		return "n";
	}

	rankPositions();

	int maxrank = -10, pos = -10;
	for (int i = 0; i < ranks.size(); i++) {
		if (ranks[i].rank > maxrank) {
			maxrank = ranks[i].rank;
			pos = ranks[i].position;
		}
	}

	setPosition(pos + 1, MM);

	think_stat = "";
	think_pos = pos;

	r = checkSolutions();
	if (r == "c") {
		//showPositions();
		cout << "I win!" << endl;
		think_stat = "iw";
		/*	if (continueGame())
		return "";
		else
		return "n";*/
		return "n";
	}
	else if (r == "t") {
		//showPositions();
		cout << "Tied!" << endl;
		think_stat = "ti";
		/*if (continueGame())
		return "";
		else
		return "n";*/
		return "n";
	}
	return "";
}

string TicTac::getStat()
{
	return think_stat;
}

int TicTac::getPos()
{
	return think_pos;
}

string TicTac::showStat()
{
	return to_string(think_pos) + " * " + think_stat;
}

bool TicTac::validPosition(int pos)
{
	pos--;
	if (positions[pos] != YM && positions[pos] != MM)
		return true;
	else
		return false;
}

