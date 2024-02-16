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

class Cards
{
	int Nomel, Masty; 
public:

	void SetNomel(int Nomel)
	{
		if (Nomel > 1 and Nomel <= 14)
		{
			this->Nomel = Nomel;
		}
	}

	void SetMasty(int Masty)
	{
		if (Masty >= 0 and Masty <= 3) //0-Черви, 1-Пики, 2-Бубны, 3-Крестье
		{
			this->Masty = Masty;
		}
	}

	int GetNomel() const
	{
		return Nomel;
	}

	int GetMasty() const
	{
		return Masty;
	}

	Cards()
	{
		SetNomel(2);
		SetMasty(0);
	}

	Cards(int Nomel, int Masty)
	{
		SetNomel(Nomel);
		SetMasty(Masty);
	}
};

class Table
{
	int X = 14, Y = 8, height = 13, width = 48;
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
			SetCursor(X, ++Y);
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
			SetCursor(X, ++Y);
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
		SetCursor(X, ++Y);
		for (size_t i = 0; i <= width; i++)
			{
				cout << "-";
			}
		SetColor(White, Black);
	}
};

int main()
{
	Cards card;
	vector<Cards> cards(52);
	int count = 0;
	for (int i = 0; i <= 3; i++)
	{
		for (size_t j = 2; j <= 14; j++)
		{
			if (count == 52)
			{
				break;
			}
			else
			{
				cards[count] = Cards(j, i);
				count++;
			}
		}
	}
	/*for (int i = 0; i < 33; ++i)
	{
		cards[i].SetNomel((i % 13) + 2);
		cards[i].SetMasty(i % 4);
	}*/
	Table t;
	t.printCard();
	//карты стола
	for (size_t i = 18; i <= 50; i+=8)
	{
		t.printCardOnPos(i, 12);
	}
	//карты левого бота
	for (size_t i = 9; i <= 17; i+=8)
	{
		t.printCardOnPos(1, i);
	}
	//карты верхнего бота
	for (size_t i = 29; i <= 41; i+= 12)
	{
		t.printCardOnPos(i, 1);
	}
	//карты правого бота
	for (size_t i = 9; i <= 17; i += 8)
	{
		t.printCardOnPos(66, i);
	}
	//наши карты
	for (size_t i = 29; i <= 41; i += 12)
	{
		t.printCardOnPos(i, 24);
	}
	SetCursor(0, 26);
	for (int i = 0; i < 52; i++)
	{
		cout << "Card " << i + 1 << ": Nomel = " << cards[i].GetNomel() << ", Masty = " << cards[i].GetMasty() << endl;
	}
}
