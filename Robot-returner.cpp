// Robot-returner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using std::cout;
using std::cin;
using std::string;
using std::rand;
using namespace std;

void gener_lab(int,int);
void paint_lab(int,int);

constexpr int limitedSizeOfArray = 30;
char lab[limitedSizeOfArray][limitedSizeOfArray];
string str;

int main()
{
	int rows;
	int columns;
	do
	{
		cout << "Write the number colomns and the number rows(don't more then " << limitedSizeOfArray/2-1 << ")\n";
		cin >> columns >> rows;
	} while (not(	(columns > 0) and (columns <= limitedSizeOfArray/2-1)
					and (rows > 0) and (rows <= limitedSizeOfArray/2-1)));

	const int x = 2*columns+2;	// max coordinates in array of labirint (with walls, crossroads ets)
	const int y = 2*rows+2;
		
	gener_lab(x,y);

	int column_bot = 1;			//bot position in cells of labirint, if you need position in lab array then x2
	int row_bot = 1;
	paint_lab(x,y);
	for (auto& numbers : lab){for (int numb : numbers)cout << numb;cout << "\n";};
		
	do //way to finish
	{
		lab[2 * column_bot][2 * row_bot] = 3;

		//begin algorithm and move robot to finish



		//end 

		lab[2 * column_bot][2 * row_bot] = 2;
		paint_lab(x, y);
	} while ((column_bot != columns) && (row_bot != rows));

	do //way return
	{
		lab[2 * column_bot][2 * row_bot] = 4;

		//begin algorithm and move robot back



		//end 

		lab[2 * column_bot][2 * row_bot] = 2;
		paint_lab(x, y);
	} while ((column_bot != 1) && (row_bot != 1));
}

void gener_lab(int x, int y)
{   
	for (int i = 1; i < x; i++)			//build outside walls
	{	
		lab[i][1]=1;
		lab[i][y-1]=1;
	}
	for (int j = 1; j < y; j++)			
	{
		lab[1][j]=1;
		lab[x-1][j]=1;
	}

	for (int i = 2; i < x - 1; i++)			//build all inside walls
	{
		if((i&1)==0)
			for (int j = 3; j < y - 1; j+=2)
			{
			lab[i][j]=1;
			}
		else
			for (int j = 2; j < y - 1; j+=2)
			{
			lab[i][j] = 1; 
			}
	}

	bool built_cells[limitedSizeOfArray / 2 - 1] [limitedSizeOfArray / 2 - 1]={1};	//if cell was building in labirinth then 1
	int numb_gen_cells=1;														//number cells what be gener
	const int numb_cells = (x/2-1) * (y/2-1);									//number all cells
	const double percent_cells = 1.0;											//percent(proportion) of gen cells for taking to second algotithm
	srand(time(0));

	int i=0, j=0;
	while(!(!(numb_gen_cells < percent_cells * numb_cells)||!(numb_gen_cells < numb_cells)))		//first gener algorithm
	{
		int di=0, dj = 0;
		switch (rand() % 4)
		{
		case 0:			//up
			dj = -1;
			break;
		case 1:			//right
			di = 1;
			break;
		case 2:			//down
			dj = 1;
			break;
		case 3:			//left
			di = -1;
			break;
		}
		if ((i + di >= 0) && (i + di < x / 2 - 1)
			&& (j + dj >= 0) && (j + dj < y / 2 - 1))
		{
			if (built_cells[i + di][j + dj] != 1)
			{
				lab[2*i+2+di][2*j+2+dj] = 0;
				built_cells[i + di][j + dj] = 1;
				numb_gen_cells++;
				cout << di << dj<<"\n";
			}
			i += di;
			j += dj;
		}
	}

	while (numb_gen_cells < numb_cells)		//second gener algorithm
	{

	}
}

void paint_lab(int x,int y)
{
	for (int y1 = 1; y1 < y; y1++)
	{
		if ((y1 & 1) == 0)
			for (int x1 = 1; x1 < x; x1++)
			{
				switch (lab[x1][y1])
				{
				case 0:
					if ((x1 & 1) == 0)
						cout << "   ";
					else cout << " ";
					break;
				case 1:
					cout << "|";
					break;
				case 2:
					cout << " # ";	//bot
					break;
				case 3:
					cout << " * ";	//way to finish
					break;
				case 4:
					cout << " x ";	//way to start (return)
						break;
				}
			}

		else
			for (int x1 = 2; x1 < x; x1 += 2)
			{
				cout << " ";
				if (lab[x1][y1])
					cout << "---";
				else
					cout << "   ";
			};
		cout <<" "<< "\n";
	};
	cin >> str;
	//cout << " " << std::endl;

}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
