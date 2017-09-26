#include <iostream>
#define SIZE 10
using namespace std;

struct map
{
	bool fill;
	int user;
};

char lover(char x)
{
	if(x >= 'A' && x <= 'Z')
		x -= ('A' + 'a');
	return x;
}
void printHead()
	{
		char a = 'a';
		for(int i = 0; i < SIZE; ++i)
		{
			cout << a++;
			if(i != SIZE - 1)
				cout << '-';
		}
		cout << endl;
		return;
	}
void printBody(const map printable[][SIZE])
	{
		for(int i = 0; i < SIZE; ++i)
		{
			for(int j = 0; j < SIZE; ++j)
			{
				printable[i][j].fill == true ? 
					cout << printable[i][j].user:
					cout << "-";
				cout << " ";
			}
			cout << endl;
		}
		return;
	}
void printmap(const map printable[][SIZE])
	{
		printHead();
		printBody(printable);
	}

int getInput()
{
	cout << "Please give me a character in range a - "
		<< (char)('a' + SIZE) << " to make your move: ";
	char Input;
	cin >> Input;
	Input = lover(Input);
	if(Input > 'a' + SIZE || Input < 'a')
		cout << "This is not legal." << endl;
	return (Input - 'a');
}

/*
a b c d
- - - -
- - - -
- - - -
- - - -
*/
/*
first we need square board to play game.
Score
Print
Input search


*/



int main(void)
{
	map board[SIZE][SIZE];
	for(int i = 0; i < SIZE; ++i)
		for(int j = 0; j < SIZE; ++j)
		{
			board[i][j].fill = false;
			board[i][j].user = 0;
		}
	board[2][2].fill = true;
	board[2][2].user = 1;
	printmap(board);
	cout << getInput() << endl;
	cout << "hello world" << endl;
	return 0;
}#include <iostream>
#define SIZE 10
using namespace std;

struct map
{
	bool fill;
	int user;
};

char lover(char x)
{
	if(x >= 'A' && x <= 'Z')
		x -= ('A' + 'a');
	return x;
}
void printHead()
	{
		char a = 'a';
		for(int i = 0; i < SIZE; ++i)
		{
			cout << a++;
			if(i != SIZE - 1)
				cout << '-';
		}
		cout << endl;
		return;
	}
void printBody(const map printable[][SIZE])
	{
		for(int i = 0; i < SIZE; ++i)
		{
			for(int j = 0; j < SIZE; ++j)
			{
				printable[i][j].fill == true ? 
					cout << printable[i][j].user:
					cout << "-";
				cout << " ";
			}
			cout << endl;
		}
		return;
	}
void printmap(const map printable[][SIZE])
	{
		printHead();
		printBody(printable);
	}

int getInput()
{
	cout << "Please give me a character in range a - "
		<< (char)('a' + SIZE) << " to make your move: ";
	char Input;
	cin >> Input;
	Input = lover(Input);
	if(Input > 'a' + SIZE || Input < 'a')
		cout << "This is not legal." << endl;
	return (Input - 'a');
}

/*
a b c d
- - - -
- - - -
- - - -
- - - -
*/
/*
first we need square board to play game.
Score
Print
Input search


*/



int main(void)
{
	map board[SIZE][SIZE];
	for(int i = 0; i < SIZE; ++i)
		for(int j = 0; j < SIZE; ++j)
		{
			board[i][j].fill = false;
			board[i][j].user = 0;
		}
	board[2][2].fill = true;
	board[2][2].user = 1;
	printmap(board);
	cout << getInput() << endl;
	cout << "hello world" << endl;
	return 0;
}