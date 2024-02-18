#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <direct.h>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <sstream>
#include <algorithm>
#include <random>
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
		if (Masty >= 0 and Masty <= 3) //0-Черви = C, 1-Пики = P, 2-Бубны = B, 3-Крестье = X
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

	void printCardOnPos(int X, int Y, Cards card, bool open)
	{
		SetCursor(X, Y);
		for (size_t i = 0; i <= 6; i++)
		{
			for (size_t j = 0; j <= 6; j++)
			{
				if ((i == 0 or i == 6) or (j == 0 or j == 6))
				{
					cout << "*";
				}
				else if(i == 1 and j == 1 or i == 5 and j == 5)
				{
					if (open)  //0-Черви = C, 1-Пики = P, 2-Бубны = B, 3-Крестье = X
					{
						if (card.GetMasty() == 0)
						{
							SetColor(Red, Black);
							cout << "C";
							SetColor(White, Black);
						}
						else if (card.GetMasty() == 1)
						{
							cout << "P";
						}
						else if (card.GetMasty() == 2)
						{
							SetColor(Red, Black);
							cout << "B";
							SetColor(White, Black);
						}
						else if (card.GetMasty() == 3)
						{
							cout << "X";
						}
					}
					else
					{
						cout << "?";
					}
				}
				else if (i == 3 and j == 3)
				{
					if (open)
					{
						if (card.GetNomel() >= 2 and card.GetNomel() <= 10)
						{
							cout << card.GetNomel();
						}
						else if (card.GetNomel() == 11)
						{
							cout << "J";
						}
						else if (card.GetNomel() == 12)
						{
							cout << "Q";
						}
						else if (card.GetNomel() == 13)
						{
							cout << "K";
						}
						else if (card.GetNomel() == 14)
						{
							cout << "A";
						}
					}
					else
					{
						cout << "?";
					}
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

void printMenu(vector <string> str, int punkt)
{
	int X = 15, Y = 5;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (punkt == i)
		{
			SetColor(Magenta, Black);
		}
		else
		{
			SetColor(White, Black);
		}
		SetCursor(X, Y + i);//перед выводом
		cout << str[i];

	}
	SetColor(White, Black);
}

int Menu(vector <string> str)
{
	int key = 0, punktOfMenu = 0;
	do
	{
		printMenu(str, punktOfMenu);
		key = _getch();
		switch (key)
		{
		case Down:
			if (punktOfMenu < str.size())
			{
				punktOfMenu++;

			}
			break;
		case Up:
			if (punktOfMenu > 0)
			{
				punktOfMenu--;
			}
			break;
		case Enter:
			return punktOfMenu;
			break;
		}

	} while (key != Esc);
	return -1;

}

int main()
{
	setlocale(LC_ALL, "RUS");
	Cards card;
	vector<Cards> cards(52);
	int count = 0, countCard = 0, bot1balance = 20000, bot2balance = 20000, bot3balance = 20000, playerbalance = 20000;
	vector<string> menu = { "Начать игру", "Выход" };
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
	Table t;
	
	auto rng = default_random_engine{};
	shuffle(cards.begin(), cards.end(), rng);
	//карты стола
	Menu(menu);
	t.printCard();
	for (size_t i = 18; i <= 50; i+=8)
	{
		t.printCardOnPos(i, 12, cards[countCard], true);
		countCard++;
	}
	//карты левого бота
	for (size_t i = 9; i <= 17; i += 8)
	{
		t.printCardOnPos(1, i, cards[countCard], false);
		countCard++;
	}
	//карты верхнего бота
	for (size_t i = 29; i <= 41; i+= 12)
	{
		t.printCardOnPos(i, 1, cards[countCard], false);
		countCard++;
	}
	//карты правого бота
	for (size_t i = 9; i <= 17; i += 8)
	{
		t.printCardOnPos(66, i, cards[countCard], false);
		countCard++;
	}
	//наши карты
	for (size_t i = 29; i <= 41; i += 12)
	{
		t.printCardOnPos(i, 24, cards[countCard], true);
		countCard++;
	}
	system("pause");
	SetCursor(0, 28);
	cout << "\n\n\n\n\n\n";
	/*for (int i = 0; i < 52; i++)
	{
		cout << "Card " << i + 1 << ": Nomel = " << cards[i].GetNomel() << ", Masty = " << cards[i].GetMasty() << endl;
	}*/
}
