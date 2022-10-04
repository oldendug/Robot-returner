// Robot-returner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using std::cout;
using std::cin;
using std::rand;
using namespace std;

void gener_lab(const int&,const int&);
void paint_lab(const int&, const int&);
void turn_bot(int&,int);

//varianles for editing
int step_paint = 0;							//number of step for one painting / if 0 then only start, end, return painting
constexpr int limitedSizeOfArray = 118;		//small screen 30(64) / full screen (118) / dont more 254, if  gener_list is int(no char) then 1020 


char lab[limitedSizeOfArray+2][limitedSizeOfArray+2];
char memory_bot[limitedSizeOfArray * (limitedSizeOfArray - 1)]={1};

int memory_numb = 1;
char cl = 0;
int main()
{
	int rows;
	int columns;
	do
	{
		cout << "Write the number colomns and the number rows(don't more then " << limitedSizeOfArray/2-1 << ")\n";
		cin >> columns >> rows;
	} while (not(	(columns > 1) and (columns <= limitedSizeOfArray/2-1)
					and (rows > 1) and (rows <= limitedSizeOfArray/2-1)));

	const int x = 2*columns+2;	// max coordinates in array of labirint (with walls, crossroads ets)
	const int y = 2*rows+2;
		
	gener_lab(x,y);

	int corn_bot = 1;			//corner of bot position / 0=up, 1=right, 2=down,3=left
	int column_bot = 1;			//bot position in cells of labirint, if you need position in lab array then x2
	int row_bot = 1;
	lab[2 * column_bot][2 * row_bot] = 2;
	paint_lab(x,y);
	//for (auto& numbers : lab){for (int numb : numbers)cout << numb;cout << "\n";};
	int step = 1;
	do //way to finish
	{
		lab[2 * column_bot][2 * row_bot] = 3;

		//begin algorithm and move robot to finish
		char ncorn = corn_bot;
		turn_bot(corn_bot, -1);
		for(int i = 0; i < 4; i++)
		{
			int dx = 0;
			int dy = 0;
			switch (corn_bot)
			{
			case 0:			//up
				dy = -1;
				break;
			case 1:			//right
				dx = 1;
				break;
			case 2:			//down
				dy = 1;
				break;
			case 3:			//left
				dx = -1;
				break;
			}
			if (lab[2 * column_bot + dx][2 * row_bot + dy] == 0)
			{
				column_bot += dx;
				row_bot += dy;
				turn_bot(corn_bot, -1);
				i=4;
			}
			turn_bot(corn_bot, 1);
		}
		//memory algorithm

		memory_bot[memory_numb] = corn_bot;
		if ((memory_bot[memory_numb] - memory_bot[memory_numb-1] + 4) % 4 == 2)
			memory_numb--;
		else
			memory_numb++;

		//end 

		lab[2 * column_bot][2 * row_bot] = 2;
		if (step <= step_paint)
		{
			if (step  == 1)
				paint_lab(x, y);
			step++;
			if (step > step_paint)
				step = 1;
		}
	} while ((column_bot != columns) || (row_bot != rows));



	paint_lab(x, y);
	step = 1;
	int i = memory_numb-1;
	do //way return
	{
		lab[2 * column_bot][2 * row_bot] = 4;

		//begin algorithm and move robot back

		int dx = 0;
		int	dy = 0;
		switch (memory_bot[i])
		{
		case 2:			//up
			dy = -1;
			break;
		case 3:			//right
			dx = 1;
			break;
		case 0:			//down
			dy = 1;
			break;
		case 1:			//left
			dx = -1;
			break;
		}
		column_bot += dx;
		row_bot += dy;		
		i--;

		//end 

		lab[2 * column_bot][2 * row_bot] = 2;
		if (step <= step_paint)
		{
			if (step == 1)
				paint_lab(x, y);
			step++;
			if (step > step_paint)
				step = 1;
		}
	} while ((column_bot != 1) || (row_bot != 1));
	paint_lab(x, y);
}



void turn_bot(int& corn, int dcorn)		// 0=up, 1=right, 2=down,3=left 
{
	corn += dcorn;
	while (corn < 0)
		corn += 4;
	while (corn > 3)
		corn -= 4;
}


int second_gen(int, int, const int&, const int&);
char built_cells[limitedSizeOfArray / 2 ][limitedSizeOfArray / 2 ] = { 1 };	//if cell was building in labirinth then 1

void gener_lab(const int& xlab, const int& ylab) //generation algorithm of labyrinth
{   
	for (int i = 1; i < xlab; i++)			//build outside walls
	{	
		lab[i][1]=1;
		lab[i][ylab-1]=1;
	}
	for (int j = 1; j < ylab; j++)			
	{
		lab[1][j]=1;
		lab[xlab-1][j]=1;
	}

	for (int i = 2; i < xlab - 1; i++)			//build all inside walls
	{
		if((i&1)==0)
			for (int j = 3; j < ylab - 1; j+=2)
			{
			lab[i][j]=1;
			}
		else
			for (int j = 2; j < ylab - 1; j+=2)
			{
			lab[i][j] = 1; 
			}
	}

	int xmax = (xlab>>1) - 1 + (xlab & 1);
	int ymax = (ylab>>1) - 1 + (ylab & 1);
	int numb_gen_cells=1;															//number cells what was gener
	const int numb_cells = (xmax) * (ymax);											//number all cells
	const double percent_cells = 0.8;												//percent(proportion) of gen cells for taking to second algotithm
	srand(time(0));

	int i=0, j=0;
	while(numb_gen_cells < percent_cells * numb_cells&&numb_gen_cells < numb_cells)		//first gener algorithm
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
		if ((i + di >= 0) && (i + di < xmax)
			&& (j + dj >= 0) && (j + dj < ymax))
		{
			if (built_cells[i + di][j + dj] != 1)
			{
				lab[2*i+2+di][2*j+2+dj] = 0;
				built_cells[i + di][j + dj] = 1;
				numb_gen_cells++;
			}
			i += di;
			j += dj;
		}
	}


	//second gener algorithm

	int s_region = 0;							//region size for preset check of generastion cell / variable++
	int s2_region = 0;							// --//-- but region inside the first algorithm
	i = 0;
	j = 0;
	int angle_gen = 0;							//angle which generation now / (for clock -> number in this variable) 1->0, 4->1, 7->2, 10->3
	int xhalf = (xmax >> 1) + (xmax & 1);
	int yhalf = (ymax >> 1) + (ymax & 1);

	while (numb_gen_cells < numb_cells)		
	{
		if (angle_gen < 2)
			if (s_region < xhalf)
				i = xmax - s_region;
			else
				i = xhalf;
		else
			if (s_region < xhalf)
				i = 1+s_region;
			else
				i = xhalf-1;											//Может просто поставить доп условия на <> перед алгоритмом какой-то половиной угла?

		if (angle_gen%3 == 0)
			if (s2_region < yhalf)
				j =1+ s2_region;
			else
				j = yhalf-1;											
		else
			if (s2_region < yhalf)
				j = ymax - s2_region;
			else
				j = yhalf;

		//begin direct gener
		if (built_cells[i-1][j-1] != 1) {
			numb_gen_cells += second_gen(i, j, xmax, ymax);
		}
		//end 

		if (s2_region == s_region)
		{
			angle_gen++;
			s2_region = 0;
		}
		else
		{
			//exchange i,j / i<->j		
			if (angle_gen < 2)
				if (s2_region < xhalf)
					i = xmax - s2_region;
				else
					i = xhalf;
			else
				if (s2_region < xhalf)
					i = 1 + s2_region;
				else
					i = xhalf-1;							

			if (angle_gen % 3 == 0)
				if (s_region < yhalf)
					j = 1 + s_region;
				else
					j = yhalf-1;								
			else
				if (s_region < yhalf)
					j = ymax - s_region;
				else
					j = yhalf;

			//begin direct gener
			if (built_cells[i-1][j-1] != 1) {
				numb_gen_cells+=second_gen(i,j,xmax,ymax);
			//end 
			} 
			s2_region++;	
		}
		if (angle_gen > 3)
		{
			angle_gen = 0;
			s_region++;
		}
	}
}

int second_gen(int x, int y, const int& xmax, const int& ymax)   //second gener algorithm
{
	char gener_list[limitedSizeOfArray][2];		//list of generation cells for this step / [~][0] -> x; [~][1] -> y;
	int num_list = 1;													//number of cells in gener_list
	int num_list1 = 0;
	gener_list[num_list][0] = x; 
	gener_list[num_list][1] = y;
	built_cells[x-1][y-1] = 2;												//
	do
	{
		int dx = 0, dy = 0;
		switch (rand() % 4)
		{
		case 0:			//up
			dy = -1;
			break;
		case 1:			//right
			dx = 1;
			break;
		case 2:			//down
			dy = 1;
			break;
		case 3:			//left
			dx = -1;
			break;
		}
		if ((x + dx >= 1) && (x + dx <= xmax)
			&& (y + dy >= 1) && (y + dy <= ymax))
		{
			switch (built_cells[x + dx-1][y + dy-1])
			{
			case 1:
				lab[2 * x + dx][2 * y  + dy] = 0;									
				break;
			case 2:																//
				break;
			default:
				lab[2 * x + dx][2 * y + dy] = 0;
				built_cells[x + dx-1][y + dy-1] = 2;							//
				num_list++;
				gener_list[num_list][0] = x+dx;
				gener_list[num_list][1] = y+dy;
				break;
			}
			x += dx;
			y += dy;
		}
	} while (built_cells[x-1][y-1] != 1 && num_list  < limitedSizeOfArray-1);
		//create recurcing function if second_gen is full, after this rewrite all 2 to 1 in built_cells
	if (num_list >= limitedSizeOfArray - 1)
		num_list1= second_gen(x, y, xmax, ymax)-1;
	for (int i = 1; i <= num_list; i++)
		built_cells[gener_list[i][0]-1][gener_list[i][1]-1] = 1;
	return (num_list+num_list1);
}

void paint_lab(const int& x, const int& y)	//graphic visualization of labyrinth
{
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
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
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED);
					cout << " # ";	//bot
					break;
				case 3:
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN);
					cout << " ' ";	//way to end labirinth
					break;
				case 4:
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE);
					cout << " * ";	//way to start (return)
						break;
				}
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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
	cl = 0;
	while (cl == 0) cl = (char)_getch();
}
// Запуск программы: CTRL+F5
