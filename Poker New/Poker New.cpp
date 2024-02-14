#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <direct.h>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <sstream>
using namespace std;
vector <int> numbers;
enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void SetColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27 };
void SetCursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hStdOut, coord);
}

class Table
{
	int X, Y, height = 25, width = 48;
public:
	void setX(int X)
	{
		if (X >= 0 or X <= 60)
		{
			this->X = X;
		}
	}

	void setY(int Y)
	{
		if (Y >= 0 or Y <= 70)
		{
			this->Y = Y;
		}
	}

	void printCardOnPos(int X, int Y)
	{
		SetCursor(X, Y);
		for (size_t i = 0; i <= 5; i++)
		{
			for (size_t j = 0; j <= 6; j++)
			{
				if ((i == 0 or i == 5) or (j == 0 or j == 6))
				{
					cout << "*";
				}
				else
				{
					cout << " ";
				}
			}
			cout << endl;
			SetCursor(X, Y++);
		}
	}

	void printCard()
	{
		//int numberRow = 1;
		SetColor(Black, White);
		SetCursor(X, Y);
		for (size_t i = 0; i <= width; i++)
		{
			cout << "-";
		}
		cout << endl;
		for (size_t i = 0; i < height; i++)
		{
			cout << "|";//рамка открывающая
			for (size_t j = 0; j <= width-1; j++)
			{


				if (j == width-1)
				{
					cout << "|";//с закрывающийся рамкой
				}
				else
				{
					cout << " ";
				}
			}
			cout << endl;
			
		}
		for (size_t i = 0; i <= width; i++)
			{
				cout << "-";
			}
		SetColor(White, Black);
	}
};

int main()
{
	Table t;
	t.printCard();
	t.printCardOnPos(4, 7);
}
