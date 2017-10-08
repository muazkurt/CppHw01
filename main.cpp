/* 
 * File:   main.cpp
 * Id: 151044062
 * Author: Muaz Kurt
 *
 * Created on 18 Eylül 2017 Pazartesi, 23:13
 */


#include "./functions.h"

int main(int argc, char * argv[])
{
	game board;
	cout << "Please give size of the game: ";
	cin >> board.size;
	Create_Game(board, board.size, doesMultiplayer());
	srand(time(NULL));
	do
	{
		board.user %= 2;
		MakeMove(board);
		++board.user;
	}
	while(WinSituation(board) == false);
	printMap((const int **&)board.board, board.size);
	free_square(board.board, board.size);
	return 0;
}