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
using namespace std;


struct map
{
    bool fill;
    int user;
};


map ** CreateMap(map ** board, int size)
{
    board = new map*[size];
    for(int i = 0; i < size; ++i)
        board[i] = new map[size];
    return board;
}


map ** FillEmpty(map ** board, int size)
{
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
        {
            board[i][j].fill = false;
            board[i][j].user = 0;
        }
    return board;
}


map ** MakeBoard(map ** board, int size)
{
    board = CreateMap(board, size);
    board = FillEmpty(board, size);
    return board;
}


char lover(char x)
{
	if(x >= 'A' && x <= 'Z')
		x -= ('A' - 'a');
	return x;
}



//Making Move
int PositionY(map ** board, int positionX, int size)
{
    int i = size - 1;
    for(i; board[i][positionX].fill == true && i >= 0; --i);
    return i;
}

int * getInput(map ** board, int * position, int size)
{
    position[1] = -1;
    do{
        cout << "Please give me a character in range a - "
		<< (char)('a' + size) << " to make your move: ";
	char Input;
	cin >> Input;
	Input = lover(Input);
	if(Input > 'a' + size || Input < 'a')
		cout << "This is not legal." << endl;
        else
        {
            position[1] = (Input - 'a');
            position[0] = PositionY(board, position[1], size);
        }
        }while(position[1] == -1);
    return position;
}



map ** MakeMove(map ** board, int position[2])
{
    board[position[0]][position[1]].fill = true;
    board[position[0]][position[1]].user = 1;
    return board;
}


//Printing map and componnents
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


void printBody(map ** printable, int size)
{
		for(int i = 0; i < size; ++i)
		{
			for(int j = 0; j < size; ++j)
			{
                            if(printable[i][j].fill == true) 
                            {
                                if(printable[i][j].user == 1)
                                        cout << 'X';
                                    else cout << 'O';
                            }
                            else
                                cout << "-";
                            cout << " ";
			}
			cout << endl;
		}
		return;
}


void printmap(map ** printable, int size)
{
		printHead(size);
		printBody(printable, size);
                return;
}


bool IsCheckable(map ** board, int position[2], int size, int line)
{
    bool Legal = false;
    switch (line)
    {
        case 0:
            if(size - 1 - position[0] > 3)
                Legal = true;
            break;
        /*
        case 1:
            if(position[0] > 2)
            {
                int i = 0;
                while(i != -1 && i < 3)
                {
                    if(board[position[1]][position[0]].fill == true &&
                       board[position[1] - (i + 1)][position[0] - (i + 1)].fill == true)
                        ++i;
                    else
                        i = -1;
                }
                if (i < 3)
                    Legal = true;
            }
            break;
        case 2:
            if(size - 1 - position[0] > 3);
            {
                int i = 0;
                while(i != -1 && i < 3)
                {
                    if(board[position[1]][position[0]].fill == true &&
                       board[position[1] + (i + 1)][position[0] + (i + 1)].fill == true)
                        ++i;
                    else
                        i = -1;
                }
                if (i < 3)
                    Legal = true;
            }
            break;
         */
        default:
            break;
    }
    return Legal;
}

bool checkHorisontal(map ** board, int position[2], int size)
{
    bool Legal = false;
    if(IsCheckable(board, position, size, 0) == true)
    {
        int i = 0;
        while(i != -1 && i < 3)
        {
        if(board[position[0]][position[1]].user == board[position[0]][position[1]].user)
                ++i;
            else i = -1;
        }
        if(i == 3)
            Legal == true;
    }
    return Legal;
}


bool checkLeft(map ** board, int position[2], int size)
{
    bool Legal = false;
    if(IsCheckable(board, position, size, 1) == true)
    {
        int i = 0;
        for(; i != -1 && i < 3; ++i)
        {
            if(board[position[1] - i][position[0] - i].user != board[position[1] - (i + 1)][position[0] - (i + 1)].user)
                i = -1;
        }
        if(i == 3)
            Legal == true;
    }
    return Legal;
}


bool checkRight(map ** board, int position[2], int size)
{
    bool Legal = false;
    if(IsCheckable(board, position, size, 2) == true)
    {
        int i = 0;
        for(; i != -1 && i < 3; ++i)
        {
            if(board[position[1] - i][position[0] + i].user != board[position[1] - (i + 1)][position[0] + (i + 1)].user)
                i = -1;
        }
        if(i == 3)
            Legal == true;
    }
    return Legal;
}


bool WinSituation(map ** board, int position[2], int size)
{
    if(checkHorisontal(board, position, size) == true
           /* || checkLeft(board, location) == true
            || checkRight(board, location) == true*/)
        return true;
    return false;
}

void freemap(map ** board)
{
    for(int i = 0; i < SIZE; ++i)
        delete board[SIZE];
    delete[] board;
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
 * Input search


*/


int main(int argc, char * argv[2])
{
	map ** board;
        int size = atoi(argv[1]);
        size = 10;
        board = MakeBoard(board, size);
        int x[2];
	do {
            printmap(board, size);
            getInput(board, x, size);
            board = MakeMove(board, x);
            printmap(board, size);
        } while(WinSituation(board, x, size) == false);
        freemap(board);
	return 0;
}

