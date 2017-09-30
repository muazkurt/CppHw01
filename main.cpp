/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: muaz
 *
 * Created on 18 Eylül 2017 Pazartesi, 23:13
 */

#include <iostream>
#define Y_X 2
using namespace std;

//	Map creating functions
	/*
		Takes an (int **) and size to create,
		Returns a square 2d array
	*/
	int ** Create_2d_Array(int ** input, int size);

	/*
		Takes (int **) and it' s created size,
		fills it with 0s.
	*/
	int ** Fill_2d_with_0(int ** array, int size);

	/*
		The function that uses Create_2d_Array and Fill_2d_with_0
		functions and return a useable square array.
	*/
	int ** Create_2d_Useable(int ** input, int size);

//	Map printing functions
	/*
		Printing a string like header.
		Takes an size input and prints letters from a until size.
	*/
	void printHead(int size);

	/*
		Prints given (int **) array.
		Each line' s length will be given size.
	*/
	void printBody(int ** array_2d, int size);

	/*
		User function of printHead and printBody functions.
	*/
	void printMap(int ** array_2d, int size);

//	Getting Input
	/*
		Using for ignoring case sensitivity.
		takes an char and returns it as lowercase
	*/
	char CharLover(char x);

	/*
		Finding the first empty place in x position of array.
		Takes an (int **) as 2d array, an x position and an int for length of array.
		Returns the found empty place.
	*/
	int PositionY(int ** board, int size, int positionX);

	/*
		Takes a (int **) as 2d array and an int array sized 2 for updating coordinate,
		and a int for size of 2d array.
		In the function, user asked for an input in range of 'a', 'a'+(size) letter.
		Then searches for empty place in 2d array' s input position by PositionY function.
		Updates coordinate array and returns.
	*/
	int * getInput(int ** board, int size, int * coordinate);

//	Making user move
	/*
		Takes 2d array as (int **), it' s size,
		an int for user number, and a array sized 2 for taking Y_X coordinations.
		Updates the map with taken argumants.
	*/
	int ** MakeMove(int ** board, int size, int user, int position[Y_X]);

//	Search for winning situations.
	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X
		and an int defines the searching way.
		Searching way values can be:
			0 -> Up to down
			1 -> Right down
			2 -> Right up
			3 -> Left down
			4 -> left Up
		Searches if the game can be finished by the last move by the lines and returns a bool.
	*/
	bool IsCheckable(int ** board, int size, const int position[Y_X], int search_way);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much stacked from last played player and returns the size of stack.
	*/
	int Up_Down(int ** board, int size, const int position[Y_X]);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Right-down way stacked from last played player and returns the size of stack.
	*/
	int Right_Down(int ** board, int size, const int position[Y_X]);


	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Right-up way stacked from last played player and returns the size of stack.
	*/
	int Right_Up(int ** board, int size, const int position[Y_X]);


	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Left-down way stacked from last played player and returns the size of stack.
	*/
	int Left_Down(int ** board, int size, const int position[Y_X]);


	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Left-up way stacked from last played player and returns the size of stack.
	*/
	int Left_Up(int ** board, int size, const int position[Y_X]);


bool WinSituation(const int ** board, int position[Y_X], int size);

void freeint(int ** board, int size);

int main(int argc, char * argv[])
{
	int ** board;
	int size = 0;
	if(argc > 1)
		size = atoi(argv[1]);
	size = 10;
	board = Create_2d_Useable(board, size);
	int x[Y_X];
	do {
		printint((const int **)board, size);
		getInput((const int **)board, x, size);
		board = MakeMove(board, 1, x);
		printint((const int **)board, size);
	} while(WinSituation((const int **)board, x, size) == false);
	freeint(board, size);
	return 0;
}






//Works well
	int ** Create_2d_Array(int ** input, int size)
	{
	    input = new int*[size];
	    for(int i = 0; i < size; ++i)
	        input[i] = new int[size];
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
					default:
						cout << '-';
						break;
				}
				cout << ' ';
			}
			cout << endl;
		}
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
	

	int ** MakeMove(int ** board, int size, int user, int position[Y_X])
	{
		getInput(board, size, position);
		if(user == 1)
			board[position[0]][position[1]] = 1;
		else
			board[position[0]][position[1]] = 2;
		return board;
	}


	int Up_Down(int ** board, int size, const int position[Y_X])
	{
		int i = 1;
		bool Legal = true;
		while(Legal == true 
			&& position[0] + i < size)
			{
				if(board[position[0]][position[1]] != board[position[0] + i][position[1]])
					Legal = false;
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
			while(Legal == true 
				&& position[0] + i < size 
				&& position[1] + i < size)
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
			while(Legal == true 
				&& position[0] - i >= 0
				&& position[1] + i < size)
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
			while(Legal == true 
					&& position[0] + i < size
					&& position[1] - i >= 0)
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
			while(Legal == true 
					&& position[0] - i >= 0
					&& position[1] - i >= 0)
				{
					if(board[position[0]][position[1]] != board[position[0] - i][position[1] - i])
						Legal = false;
					else
						++i;
				}
		}
		return i;
	}

//


bool WinSituation(const int ** board, int position[Y_X], int size)
{
    if(/*checkHorisontal(board, position, size) == true
            || checkLeft(board, position, size) == true
            || */checkRight(board, position, size) == true)
        return true;
    return false;
}

void freeint(int ** board, int size)
{
    for(int i = 0; i < size; ++i)
        delete board[size];
    delete[] board;
}

	bool IsCheckable(int ** board, int size, const int position[Y_X], int search_way)
	{
		bool Legal = false;
		switch (search_way)
		{
			//Is that possible to finish Up to down way from my position.
				case 0:
					if(size - position[0] > 2)
						Legal = true;
					break;
			//Is that possible to finish Right-Down way from my position.
				case 1:
					if((size - position[0] > 2) && (size - position[1] > 2))
					{
						int i = 1;
						while(i < 4 && i > 0)
						{
							if(board[position[0] + i][position[1] + i] == 0)
								i = -1;
							++i;
						}
						if (i != 0)
							Legal = true;
					}
					break;
			//Is that possible to finish Right-Up way from my position.
				case 2:
					if((position[0] > 2) && (size - position[1] > 3))
					{
						int i = 1;
						while(i < 4 && i > 0)
						{
							if(board[position[0] - i][position[1] + i] == 0)
								i = -1;
							++i;
						}
						if (i != 0)
							Legal = true;
					}
					break;
			//Is that possible to finish Left-Down way from my position.
				case 3:
					if((size - position[0] > 3) && (position[1] > 2))
					{
						int i = 1;
						while(i < 4 && i > 0)
						{
							if(board[position[0] + i][position[1] - i] == 0)
								i = -1;
							++i;
						}
						if (i != 0)
							Legal = true;
					}
					break;
			//Is that possible to finish Left-Up way from my position.
				case 4:
					if((position[0] > 2) && (position[1] > 2))
						{
							int i = 1;
							while(i < 4 && i > 0)
							{
								if(board[position[0] - i][position[1] - i] == 0)
									i = -1;
								++i;
							}
							if (i != 0)
								Legal = true;
						}
						break;
			default:
				break;
		}
		return Legal;
	}
