#include "./functions.h"


int ** Create_2d_Array(int ** input, int size)
{
	input = (int **)std::malloc(sizeof(int *) * size);
	for(int i = 0; i < size; ++i)
		input[i] = (int *)std::malloc(sizeof(int) * size);
	return input;
}


int ** Fill_2d_with_0(int ** array, int size)
{
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            array[i][j] = 0;
    return array;
}


int ** Create_2d_Useable(int ** input, int size)
{
    input = Create_2d_Array(input, size);
    input = Fill_2d_with_0(input, size);
    return input;
}


void printHead(int size)
{
	char a = 'a';
	for(int i = 0; i < size; ++i)
	{
		cout << a++;
		if(i != size - 1)
			cout << '-';
	}
	cout << endl;
	return;
}


void printBody(int ** array_2d, int size)
{
	int won = 0;
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			switch(array_2d[i][j]) 
			{
				case 1:
					cout << 'X';
					break;
				case 2:
					cout << 'O';
					break;
				case 3:
					won = 1;
					cout << 'x';
					break;
				case 4:
					won = 2;
					cout << 'o';
					break;
				default:
					cout << '-';
					break;
			}
			cout << ' ';
		}
		cout << endl;
	}
	if(won > 0)
		cout << "User " << won << " won!" << endl;
	return;
}

void printMap(int ** array_2d, int size)
{
	printHead(size);
	printBody(array_2d, size);
	return;
}

char CharLover(char x)
{
	if(x >= 'A' && x <= 'Z')
		x -= ('A' - 'a');
	return x;
}

int doesMultiplayer()
{
	cout << "   ------------" << endl
		<<  "1) User vs User" << endl
		<<  "2) User vs Coop" << endl
		<<  "Choice: ";
	int input = 0;
	while(input == 0)
	{
		cin >> input;
		if(input > 2 || input < 0)
		{
			cout << "Please give another input in range of (1, 2)" << endl
				 << "Choice: ";
			input = 0;
		}
	}
	return input - 1;
}

int PositionY(int ** board, int size, int positionX)
{
	int i = size - 1;
    if(board[0][positionX] == 0)
    	for(i; board[i][positionX] > 0 && i >= 0; --i);
    else
    	i = -1;
    return i;
}

int * getInput(int ** board, int size, int * coordinate)
{
	coordinate[1] = -1;
    do{
    	cout << "Please give me a character in range a - "
			<< (char)('a' + (size - 1)) 
			<< " to make your move: ";
		char Input;
		cin >> Input;
		Input = CharLover(Input);
		if(Input > 'a' + (size - 1) || Input < 'a')
			cout << "This is not legal." << endl;
        else
        {
            coordinate[1] = (Input - 'a');
            coordinate[0] = PositionY(board, size, coordinate[1]);
            if(coordinate[0] == -1)
        	{
				cout << "This is not legal." << endl;
				coordinate[1] = -1;
        	}
        }
    } while(coordinate[1] == -1);
    return coordinate;
}

int * Ai_input(int ** board, int size, int * position)
{
	cout << "Computer moving to: ";
	int i = 0;
	bool PositionFound = false;
	while(PositionFound == false)
	{
		switch(i)
		{
			//Watch out for Up to down.
			case 0:
				if(Up_Down(board, size, (const int *) position) > 2 && position[0] > 0)
					{
						PositionFound = true;
						--position[0];
					}
				break;
			//	Watch out for right down + left up and if it is possible to win for user 1,
			//		then breake it by putting right down position.
			case 1:
				if(position[0] == size - 1 || position[1] == size - 1);
				else
				{
					int right_temp = Right_Down(board, size, (const int *) position);
					if(right_temp + Left_Up(board, size, (const int *) position) - 1 > 2)
					{
						if(position[0] + right_temp < size && position[1] + right_temp < size)
						if(PositionY(board, size, position[1] + right_temp) == (position[0] + right_temp))
						{
							position[0] += right_temp;
							position[1] += right_temp;
							PositionFound = true;
						}
					}
				}
				break;
			//	Watch out for right up + left down and if it is possible to win for user 1,
			//		then breake it by putting right up position.
			case 2:
				if(position[0] == 0 || position[1] == size - 1);
				else
				{
					int right_temp = Right_Up(board, size, (const int *) position);
					if(right_temp + Left_Down(board, size, (const int *) position) - 1 > 2)
					{
						if(position[0] - right_temp >= 0 && position[1] + right_temp < size)
						if(PositionY(board, size, position[1] + right_temp) == (position[0] - right_temp))
						{
							position[0] -= right_temp;
							position[1] += right_temp;
							PositionFound = true;
						}
					}
				}
				break;
			//	Watch out for left down + right up and if it is possible to win for user 1,
			//		then breake it by putting left down position.
			case 3:
				if(position[0] == size - 1 || position[1] == 0);
				else
				{
					int left_temp = Left_Down(board, size, (const int *) position);
					if(left_temp + Right_Up(board, size, (const int *) position) - 1 > 2)
					{
						if(position[0] + left_temp < size && position[1] - left_temp >= 0)
						if(PositionY(board, size, position[1] - left_temp) == (position[0] + left_temp))
						{
							position[0] += left_temp;
							position[1] -= left_temp;
							PositionFound = true;
						}
					}
				}
				break;
			//	Watch out for left up + right down and if it is possible to win for user 1,
			//		then breake it by putting left up position.
			case 4:
				if(position[0] == 0 || position[1] == 0);
				else
				{
					int left_temp = Left_Up(board, size, (const int *)  position);
					if(left_temp + Right_Down(board, size, (const int *)  position) - 1 > 2)
					{
						if(position[0] - left_temp >= 0 && position[1] - left_temp >= 0)
						if(PositionY(board, size, position[1] - left_temp) == (position[0] + left_temp))
						{
							position[0] -= left_temp;
							position[1] -= left_temp;
							PositionFound = true;			
						}
					}
				}
				break;

			//	Watch out for right + left  and if it is possible to win for user 1,
			//		then breake it by putting right position.
			case 5:
				if(position[1] == size - 1);
				else
				{
					int right_temp = To_Right(board, size, (const int *)  position);
					if(right_temp + To_Left(board, size, (const int *)  position) - 1 > 2)
					{
						if(position[1] + right_temp < size && position[0] == PositionY(board, size, position[1] + right_temp))
						{
							position[1] += right_temp;
							position[0] = PositionY(board, size, position[1]);
							PositionFound = true;			
						}
					}
				}
				break;

			//	Watch out for left + right and if it is possible to win for user 1,
			//		then breake it by putting left position.
			case 6:
				if(position[1] == 0);
				else
				{
					int left_temp = To_Left(board, size, (const int *)  position);
					if(left_temp + To_Right(board, size, (const int *)  position) - 1 > 2)
					{
						if(position[1] - left_temp >= 0 && position[0] == PositionY(board, size, position[1] - left_temp))
						{
							position[1] -= left_temp;
							PositionFound = true;			
						}
					}
				}
				break;

			//	Search that if there is a possible stack position in map for User 2 (AI) side.
			case 7:
				for(position[1] = 0, position[1] = PositionY(board, size, position[1]);
					PositionFound == false && position[1] < size; 
					++position[1], position[0] = PositionY(board, size, position[1]))
				{
					if(position[0] + 1 < size)
					{
						++position[0];
						if(board[position[0]][position[1]] == 2)
							if(Up_Down(board, size, (const int *) position) > 1)
								PositionFound = true;
						--position[0];
						// The way like '\' if i can check right down
						if(PositionFound == false && position[1] + 1 < size)
						{
							++position[0];
							++position[1];
							int right_temp = 0;
							if(board[position[0]][position[1]] == 2)
								right_temp = Right_Down(board, size, (const int *) position);
							--position[1];
							--position[0];
							if(position[0] - 1 >= 0 && position[1] - 1 >= 0)
							{
								--position[0];
								--position[1];
								if(board[position[0]][position[1]] == 2)
									right_temp += Left_Up(board, size, (const int *) position);
								++position[1];
								++position[0];
							}
							if(right_temp > 1)
								PositionFound = true;
						}
						// The way like '/' if i can check left down
						if(PositionFound == false && position[1] - 1 >= 0)
						{
							++position[0];
							--position[1];
							int left_temp = 0;
							if(board[position[0]][position[1]] == 2)
								left_temp = Left_Down(board, size, (const int *) position);
							++position[1];
							--position[0];
							if(position[0] - 1 >= 0 && position[1] + 1 < size)
							{
								--position[0];
								++position[1];
								if(board[position[0]][position[1]] == 2)
									left_temp += Right_Up(board, size, (const int *) position);
								--position[1];
								++position[0];
							}
							if(left_temp > 1)
								PositionFound = true;
						}
					}
					if(PositionFound == false && position[0] - 1 >= 0)
					{
						if(position[1] + 1 < size)
						{
							--position[0];
							++position[1];
							int right_temp = 0;
							if(board[position[0]][position[1]] == 2)
								right_temp = Right_Up(board, size, (const int *) position);
							--position[1];
							++position[0];
							if(position[0] + 1 < size && position[1] - 1 >= 0)
							{
								++position[0];
								--position[1];
								if(board[position[0]][position[1]] == 2)
									right_temp += Left_Down(board, size, (const int *) position);
								++position[1];
								--position[0];
							}
							if(right_temp > 1)
								PositionFound = true;
						}
						if(position[1] - 1 >= 0)
						{
							--position[0];
							--position[1];
							int left_temp = 0;
							if(board[position[0]][position[1]] == 2)
								left_temp = Left_Up(board, size, (const int *) position);
							++position[1];
							++position[0];
							if(position[0] + 1 < size && position[1] + 1 < size)
							{
								++position[0];
								++position[1];
								if(board[position[0]][position[1]] == 2)
									left_temp += Right_Down(board, size, (const int *) position);
								--position[1];
								--position[0];
							}
							if(left_temp > 1)
								PositionFound = true;
						}
					}
					if(PositionFound == false && position[1] + 1 < size)
					{
						++position[1];
						int right_temp = 0;
						if(board[position[0]][position[1]] == 2)
							right_temp = To_Right(board, size, (const int *) position);
						--position[1];
						if(position[1] - 1 >= 0)
						{
							--position[1];
							if(board[position[0]][position[1]] == 2)
								right_temp += To_Left(board, size, (const int *) position);
							++position[1];
						}
						if(right_temp > 1)
							PositionFound = true;
					}
					if(PositionFound == false && position[1] - 1 >= 0)
					{
						--position[1];
						int left_temp = 0;
						if(board[position[0]][position[1]] == 2)
							left_temp = To_Left(board, size, (const int *) position);
						++position[1];
						if(position[1] + 1 < size)
						{
							++position[1];
							if(board[position[0]][position[1]] == 2)
								left_temp = To_Right(board, size, (const int *) position);
							--position[1];
						}
						if(left_temp > 1)
							PositionFound = true;
					}
				}
				break;
			//Playing randomise.
			case 8:
				int temp = rand() % size;
				if(temp < 0)
					temp *= -1;
				position[1] = temp;
				position[0] = PositionY(board, size, position[1]);
				PositionFound = true;
				break;
			default:
				break;
		}
		++i;
	}
	cout << "[" << position[0] << "," << position[1] << "]" << endl;
	return position;
}

int ** MakeMove(int ** board, int size, int user, int position[Y_X], int AI_Active)
{
	if(user == 1)
	{	
		getInput(board, size, position);
		board[position[0]][position[1]] = 1;
	}
	else
	{
		if(AI_Active == 1)
			position = Ai_input(board, size, position);
		else
			getInput(board, size, position);
		board[position[0]][position[1]] = 2;
	}
	return board;
}

int Up_Down(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	bool Legal = true;
	while(Legal == true && position[0] + i < size)
		{
			if(board[position[0]][position[1]] != board[position[0] + i][position[1]])
				Legal = false;
			else
				++i;
		}
	return i;
}

int Right_Down(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	if(position[0] == size - 1 || position[1] == size - 1);
	else
	{
		bool Legal = true;
		while(Legal == true && position[0] + i < size && position[1] + i < size)
			{
				if(board[position[0]][position[1]] != board[position[0] + i][position[1] + i])
					Legal = false;
				else
					++i;
			}
	}
	return i;
}

int Right_Up(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	if(position[0] == 0 || position[1] == size - 1);
	else
	{
		bool Legal = true;
		while(Legal == true && position[0] - i >= 0 && position[1] + i < size)
			{
				if(board[position[0]][position[1]] != board[position[0] - i][position[1] + i])
					Legal = false;
				else
					++i;
			}
	}
	return i;
}

int Left_Down(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	if(position[0] == size - 1 || position[1] == 0);
	else
	{
		bool Legal = true;
		while(Legal == true && position[0] + i < size && position[1] - i >= 0)
			{
				if(board[position[0]][position[1]] != board[position[0] + i][position[1] - i])
					Legal = false;
				else
					++i;
			}
	}
	return i;
}

int Left_Up(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	if(position[0] == 0 || position[1] == 0);
	else
	{
		bool Legal = true;
		while(Legal == true && position[0] - i >= 0 && position[1] - i >= 0)
			{
				if(board[position[0]][position[1]] != board[position[0] - i][position[1] - i])
					Legal = false;
				else
					++i;
			}
	}
	return i;
}

int To_Right(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	if(position[1] == size - 1);
	else
	{
		bool Legal = true;
		while(Legal == true && position[1] + i < size)
			{
				if(board[position[0]][position[1]] != board[position[0]][position[1] + i])
					Legal = false;
				else
					++i;
			}
	}
	return i;
}

int To_Left(int ** board, int size, const int position[Y_X])
{
	int i = 1;
	if(position[1] == 0);
	else
	{
		bool Legal = true;
		while(Legal == true && position[1] - i >= 0)
		{
			if(board[position[0]][position[1]] != board[position[0]][position[1] - i])
				Legal = false;
			else
				++i;
		}
	}
	return i;
}

bool WinSituation(int ** board, int size, int position[Y_X])
{
	int y = 0, x = 0, filler = board[position[0]][position[1]];
	bool win = false;
	if((y = Up_Down(board, size, position)) >= 4)
	{
		for(y -= 1; y > 0; --y)
			board[position[0] + y][position[1]] = filler + 2;
		win = true;
	}
	else if((y = Right_Down(board, size, position)) + (x = Left_Up(board, size, position)) - 1 >= 4)
	{
		for(y -= 1; y > 0; --y)
			board[position[0] + y][position[1] + y] = filler + 2;
		for(x -= 1; x > 0; --x)
			board[position[0] - x][position[1] - x] = filler + 2;
		win = true;
	}
	else if((y = Right_Up(board, size, position)) + (x = Left_Down(board, size, position)) - 1 >= 4) 
	{
		for(y -= 1; y > 0; --y)
			board[position[0] - y][position[1] + y] = filler + 2;
		for(x -= 1; x > 0; --x)
			board[position[0] + x][position[1] - x] = filler + 2;
		win = true;
	}
	else if((y = To_Left(board, size, position)) + (x = To_Right(board, size, position)) - 1 >= 4) 
	{
		for(y -= 1; y > 0; --y)
			board[position[0]][position[1] - y] = filler + 2;
		for(x -= 1; x > 0; --x)
			board[position[0]][position[1] + x] = filler + 2;
		win = true;
	}
	if(win == true)
		board[position[0]][position[1]] = filler + 2;
	return win;
}

void free_square(int ** array, int size)
{
	for(int i = 0; i < size; ++i)
		std::free(array[i]);
	std::free(array);
	return;
}