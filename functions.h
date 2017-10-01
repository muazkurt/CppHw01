#include <iostream> 
#include <cstdlib>	//For malloc, rand and srand functions
#include <ctime>	//For time function.
#define Y_X 2		//Defining the size of coordinate.
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
		Ask the user for User vs Coop or User vs User
	*/
	int doesMultiplayer();

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

	/*
		Takes 2d array as (int **), it's size, an (int *) includes the enimy' s last move.
		Searches for possible moves and tries to win.
	*/
	int * Ai_input(int ** board, int size, int * position);

//	Making user move
	/*
		Takes 2d array as (int **), it' s size,
		an int for user number, and a array sized 2 for taking Y_X coordinations.
		Updates the map with taken argumants.
		If the last variable setted by user, then User 2 will be computer.
	*/
	int ** MakeMove(int ** board, int size, int user, int position[Y_X], int AI_Active = 0);

//	Search for winning situations.
	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much stacked from last played player and returns the size of stack.
	*/
	int Up_Down(int ** board, int size, const int position[Y_X]);

	/*
	Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
	Checks how much Right down way stacked from last played player and returns the size of stack.
	*/
	int Right_Down(int ** board, int size, const int position[Y_X]);


	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Right up way stacked from last played player and returns the size of stack.
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

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much right way stacked from last played player and returns the size of stack.
	*/
	int To_Right(int ** board, int size, const int position[Y_X]);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much left way stacked from last played player and returns the size of stack.
	*/
	int To_Left(int ** board, int size, const int position[Y_X]);
	
	/*
		Checks if game is finish or not.
		If game finishes, then updates the map.
	*/
	bool WinSituation(int ** board, int size, int position[Y_X]);

//	Destroying allocated memory.
	/*
		Takes a squre array as an (int **) and it' s size as int.
		Frees all the memory about it.
	*/
	void free_square(int ** array, int size);

