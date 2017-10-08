#include <iostream> 
#include <string>	//For string operations.
#include <cstdlib>	//For malloc, rand and srand functions
#include <ctime>	//For time function.
#include <fstream>
#define SAVE "save"
#define LOAD "load"
#define MEMORY "./game_memory/"
#define Y_X 2		//Defining the size of coordinate.
using namespace std;

//	Defining Struct for game.
	typedef struct
	{
		int ** board;
		int size;
		int AI_Open;
		int user;
		int coordinate[Y_X];
	} game;

//	Map creating functions
	/*
		Takes an (int **) and size to create,
		Returns a square 2d array
	*/
	void Create_2d_Array(int **& input, const int & size);

	/*
		Takes (int **) and it' s created size,
		fills it with 0s.
	*/
	void Fill_2d_with_0(int **& array, const int & size);

	/*
		The function that uses Create_2d_Array and Fill_2d_with_0
		functions and return a useable square array.
	*/
	void Create_2d_Useable(int **& input, const int & size);

	/*
	
	*/
	void Create_Game(game & board, int size, int ai = 0);

//	Map printing functions
	/*
		Printing a string like header.
		Takes an size input and prints letters from a until size.
	*/
	void printHead(const int & size);

	/*
		Prints given (int **) array.
		Each line' s length will be given size.
	*/
	void printBody(const int **& array_2d, const int & size);


	/*
		User function of printHead and printBody functions.
	*/
	void printMap(const int **& array_2d, int size);

//	Getting Input
	/*
		Using for ignoring case sensitivity.
		takes an char and updates it as lowercase.
		Returns 1 if updated or 0 if didn't.
	*/
	int CharLover(char & letter);
	
	/*
		Ask the user for User vs Coop or User vs User
	*/
	int doesMultiplayer();

	/*
		Finding the first empty place in x position of array.
		Takes an (int **) as 2d array, an x position and an int for length of array.
		Returns the found empty place.
	*/
	int PositionY(const game & situation);

	/*
		Takes a (int **) as 2d array and an int array sized 2 for updating coordinate,
		and a int for size of 2d array.
		In the function, user asked for an input in range of 'a', 'a'+(size) letter.
		Then searches for empty place in 2d array' s input position by PositionY function.
		Updates coordinate array and returns.
	*/
	void getInput(game & onTarget);

	/*
		Takes 2d array as (int **), it's size, an (int *) includes the enimy' s last move.
		Searches for possible moves and tries to win.
	*/
	void Ai_input(int ** board, int size, int * position);

//	Making user move
	/*
		Takes 2d array as (int **), it' s size,
		an int for user number, and a array sized 2 for taking Y_X coordinations.
		Updates the map with taken argumants.
		If the last variable setted by user, then User 2 will be computer.
	*/
	void MakeMove(game & onTarget);

//	Search for winning situations.
	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much stacked from last played player and returns the size of stack.
	*/
	int Up_Down(game & input);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Right down way stacked from last played player and returns the size of stack.
	*/
	int Right_Down(game & input);


	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Right up way stacked from last played player and returns the size of stack.
	*/
	int Right_Up(game & input);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Left-down way stacked from last played player and returns the size of stack.
	*/
	int Left_Down(game & input);
	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Left-up way stacked from last played player and returns the size of stack.
	*/
	int Left_Up(game & input);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much right way stacked from last played player and returns the size of stack.
	*/
	int To_Right(game & input);

	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much left way stacked from last played player and returns the size of stack.
	*/
	int To_Left(game & input);
	
	/*
		Checks if game is finish or not.
		If game finishes, then updates the map.
	*/
	bool WinSituation(int ** board, int size, int position[Y_X]);


//	File operations.
	int sizeFromFile(const string & input, int & size);

	int AIformFile(const string & input, int & AI_Open);

	int userFromFile(const string & input, int & user);

	int lastPlayedPosition(const string & input, int * coordinate);

	int Create_2d_Useable(const string & input, game & board);

	void parseInput(const string & input, game area);

	string fileInput(const string & filename, string & loaded);

	void Int_2d_String(const game & input, string & output);

	void Load(const string & filename,  game & output);

	void Save(const string & filename, const game & input);


//	Destroying allocated memory.
	/*
		Takes a squre array as an (int **) and it' s size as int.
		Frees all the memory about it.
	*/
	void free_square(int ** array, int size);

