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
		int ** board;			//	The array to game playing
		int size;				//	Size of the array
		int AI_Open;			//	Does AI setted or not? If equals 0, then AI plays.
		int user;				//	Turn counter of the player.
		int coordinate[Y_X];	//	Last played position. Defaultly setted by {0,0}
	} game;

//	Map creating functions
	/*
		For only using auto obey.
		Searches an int from cin.
	*/
	auto returnInt() -> decltype (0);

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
		Takes game board, board's new size.
		if didn't setted:
			AI will be 0 and user will be 1 as default.
		Creates a game struct.
	*/
	void Create_Game(game & board, int size, int ai = 0, int user = 1);

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
		Ignoring case sensitivity.
		Takes a string and updates it with lowercase latters.
		Returns the count of changed latter.
	*/
	int stringLover(string & traget);

	/*
		Ask the user for User vs Coop or User vs User
	*/
	int doesMultiplayer();

	/*
		Finding the first empty place in x position of game board.
		Searches on game board's coordinate part's 1 object.
		Returns the found empty place.
	*/
	int PositionY(const game & situation);

	/*
		Takes game board address and searches for input.
		Possible inputs are:
			"load",
			"save",
			'a' to size of game counted other char.
		Load and save takes a filename.
		Opens and reads/writes it.
		Load, updates the map as the file obey.
	*/
	void getInput(game & onTarget);

	/*
		Takes 2d array as (int **), it's size, an (int *) includes the enimy' s last move.
		Searches for possible moves and tries to win.
	*/
	void Ai_input(game & onTarget);

//	Making user move
	/*
		Takes game board address. Gets input and updates thea game.
		Updates the map with taken argumants.
	*/
	void MakeMove(game & onTarget);


//	Search for winning situations.
	/*
		Takes the game board and checks how much up way stacked from last played position.
		Returns the size of stack.
	*/
	int Up_Down(const game & input);

	/*
		Takes the game board and checks how much Right down way stacked from last played position.
		Returns the size of stack.
	*/
	int Right_Down(const game & input);


	/*
		Takes the game board and checks how much Right up way stacked from last played position.
		Returns the size of stack.
	*/
	int Right_Up(const game & input);

	/*
		Takes the game board and checks how much Left-down way stacked from last played position.
		Returns the size of stack.
	*/
	int Left_Down(const game & input);
	/*
		Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
		Checks how much Left-up way stacked from last played position.
		Returns the size of stack.
	*/
	int Left_Up(const game & input);

	/*
		Takes the game board and checks how much right way stacked from last played position.
		Returns the size of stack.
	*/
	int To_Right(const game & input);

	/*
		Takes the game board and checks how much left way stacked from last played position.
		Returns the size of stack.
	*/
	int To_Left(const game & input);
	
	/*
		Checks if game is finish or not.
		If game finishes, then updates the map.
	*/
	bool WinSituation(const game & searchOn);


//	Load File.
	/*
		Search the string until the given parameter.
		Each object will a part of an int, until the paramater.
		Returns the position of found parameter.
	*/
	int stringParser(const string & input, int & size, const char param = '/');

	/*
		Overloaded function for creating 2d useable.
		Takes a line of int included in a string and a game board address.
		updates the boards componnents with string.
	*/
	int Create_2d_Useable(const string & input, game & board);

	/*
		Takes a string with informations about game board. 
		Info parsed with a paramater. Searches that parses and updates declared positions.
	*/
	void parseInput(const string & input, game & area);

	/*
		Takes a string as a filename.
		Opens it and reads a line of information.
		Updates loaded with this information.
		Returns loaded.
	*/
	string fileInput(const string & filename, string & loaded);

	/*
		Takes a filename and game board.
		Opens file, reads information and updates the game board.
	*/
	void Load(const string & filename, game & output);


//	Save file.
	/*
		Takes a game board and parse it's componnents, then writes them to
		output string.
	*/
	void Int_2d_String(const game & input, string & output);

	/*
		Takes a filename, opens it and writes the game board in
		it as load function can read.
	*/
	void Save(const string & filename, const game & input);


//	Destroying allocated memory.
	/*
		Takes a squre array as an (int **) and it' s size as int.
		Frees all the memory about it.
	*/
	void free_square(int **& array, int size);

