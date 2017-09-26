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




int ** Createint(int ** board, int size);

int ** FillEmpty(int ** board, int size);

int ** MakeBoard(int ** board, int size);

char lover(char x);

//Making Move
int PositionY(const int ** board, int positionX, int size);

int * getInput(const int ** board, int * position, int size);

int ** MakeMove(int ** board, int user, const int position[2])

//Printing int and componnents
void printHead(int size);

void printBody(const int ** printable, int size);

void printint(const int ** printable, int size);

bool IsCheckable(const int ** board, const int position[2], int size, int line);

bool checkHorisontal(const int ** board, const int position[2], int size)

bool leftUp(const int ** board, const int position[2])

bool leftDown(const int ** board, const int position[2]);

bool checkLeft(const int ** board, const int position[2], int size);

bool RightUp(const int ** board, const int position[2]);

bool RightDown(const int ** board, const int position[2]);

bool checkRight(const int ** board, const int position[2], int size);

bool WinSituation(const int ** board, int position[2], int size);

void freeint(int ** board, int size);

int main(int argc, char * argv[])
{
	int ** board;
        int size = 0;
        if(argc > 1)
            size = atoi(argv[1]);
        size = 10;
        board = MakeBoard(board, size);
        int x[2];
	do {
            printint((const int **)board, size);
            getInput((const int **)board, x, size);
            board = MakeMove(board, 1, x);
            printint((const int **)board, size);
        } while(WinSituation((const int **)board, x, size) == false);
        freeint(board, size);
	return 0;
}



int ** Createint(int ** board, int size)
{
    board = new int*[size];
    for(int i = 0; i < size; ++i)
        board[i] = new int[size];
    return board;
}


int ** FillEmpty(int ** board, int size)
{
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            board[i][j] = 0;
    return board;
}


int ** MakeBoard(int ** board, int size)
{
    board = Createint(board, size);
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
int PositionY(const int ** board, int positionX, int size)
{
    int i = size - 1;
    for(i; board[i][positionX] > 0 && i >= 0; --i);
    return i;
}

int * getInput(const int ** board, int * position, int size)
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



int ** MakeMove(int ** board, int user, const int position[2])
{
    if(user = 1)
        board[position[0]][position[1]] = 1;
    else
        board[position[0]][position[1]] = 2;
    return board;
}


//Printing int and componnents
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


void printBody(const int ** printable, int size)
{
		for(int i = 0; i < size; ++i)
		{
			for(int j = 0; j < size; ++j)
			{
                switch(printable[i][j]) 
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


void printint(const int ** printable, int size)
{
		printHead(size);
		printBody(printable, size);
                return;
}


bool IsCheckable(const int ** board, const int position[2], int size, int line)
{
    bool Legal = false;
    switch (line)
    {
        case 0:
            if(size - 1 - position[0] > 2)
                Legal = true;
            break;
        //for right-down
        case 1:
            if(size - 1 - position[0] > 3 || size - 1 - position[0] > 3);
            {
                int i = 0;
                while(i != -1 && i < 3)
                {
                    if(board[position[1]][position[0]] > 0 &&
                       board[position[1] + (i + 1)][position[0] + (i + 1)] > 0)
                        ++i;
                    else
                        i = -1;
                }
                if (i < 3)
                   Legal = true;
            }
            break;
        //for right-up
        case 2:
            if(size - 1 - position[1] > 3);
            {
                int i = 0;
                while(i != -1 && i < 3)
                {
                    if(board[position[1]][position[0]] > 0 &&
                       board[position[1] - (i + 1)][position[0] + (i + 1)] > 0)
                        ++i;
                    else
                        i = -1;
                }
                if (i < 3)
                    Legal = true;
            }
            break;
            
        //For left-up
        case 3:
            if(position[1] > 2)
            {
                int i = 0;
                while(i != -1 && i < 3)
                {
                    if(board[position[1]][position[0]] > 0 &&
                       board[position[1] - (i + 1)][position[0] - (i + 1)] > 0)
                        ++i;
                    else
                        i = -1;
                }
                if (i < 3)
                    Legal = true;
            }
            break;
        //for left-down
        case 4:
            if(position[1] > 2 && size -1 - position[0] > 3)
            {
                int i = 0;
                while(i != -1 && i < 3)
                {
                    if(board[position[1]][position[0]] > 0&&
                       board[position[1] - (i + 1)][position[0] - (i + 1)] > 3)
                        ++i;
                    else
                        i = -1;
                }
                if (i < 3)
                    Legal = true;
            }
            break;
        default:
            break;
    }
    return Legal;
}

bool checkHorisontal(const int ** board, const int position[2], int size)
{
    bool Legal = false;
    if(IsCheckable(board, position, size, 0) == true)
    {
        int i = 0;
        if ((board[position[0]][position[1]] == board[position[0] + 1][position[1]]) &&
                (board[position[0] + 1][position[1]]
                == board[position[0] + 2][position[1]]) &&
                (board[position[0] + 2][position[1]]
                == board[position[0] + 3][position[1]]))
            Legal = true;
    }
    return Legal;
}


bool leftUp(const int ** board, const int position[2])
{
    bool Legal = false;
    if(
            (board[position[0]][position[1]] 
            == board[position[0] - 1][position[1] - 1]) &&
                (board[position[0] - 1][position[1] - 1]
                == board[position[0] - 2][position[1] - 2]) &&
                (board[position[0] - 2][position[1] - 2]
                == board[position[0] - 3][position[1] - 3]))
        Legal = true;
    return Legal;
}


bool leftDown(const int ** board, const int position[2])
{
    bool Legal = false;
    if(
            (board[position[0]][position[1]] 
            == board[position[0] + 1][position[1] - 1]) &&
                (board[position[0] + 1][position[1] - 1]
                == board[position[0] + 2][position[1] - 2]) &&
                (board[position[0] + 2][position[1] - 2]
                == board[position[0] + 3][position[1] - 3]))
        Legal = true;
    return Legal;
}


bool checkLeft(const int ** board, const int position[2], int size)
{
    bool Legal = false;
    if(IsCheckable(board, position, size, 3) == true)
        Legal = leftUp(board, position);
    if(Legal == false && IsCheckable(board, position, size, 4) == true)
        Legal = leftDown(board, position);
    return Legal;
}


bool RightUp(const int ** board, const int position[2])
{
    bool Legal = false;
    if(
            (board[position[0]][position[1]] 
            == board[position[0] - 1][position[1] + 1]) &&
                (board[position[0] - 1][position[1] + 1]
                == board[position[0] - 2][position[1] + 2]) &&
                (board[position[0] - 2][position[1] + 2]
                == board[position[0] - 3][position[1] + 3]))
        Legal = true;
    return Legal;
}

bool RightDown(const int ** board, const int position[2])
{
    if((board[position[0]][position[1]] == board[position[0] + 1][position[1] + 1]) &&
                (board[position[0] + 1][position[1] + 1]
                == board[position[0] + 2][position[1] + 2]) &&
                (board[position[0] + 2][position[1] + 2]
                == board[position[0] +  3][position[1] + 3]))
        return true;
    return false;
}


bool checkRight(const int ** board, const int position[2], int size)
{
    bool Legal = false;
    if(IsCheckable(board, position, size, 1) == true)
        Legal = RightDown(board, position);
    if(Legal == false && IsCheckable(board, position, size, 2) == true)
        Legal = RightUp(board, position);
    return Legal;
}


bool WinSituation(const int ** board, int position[2], int size)
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