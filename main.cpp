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
	if(argc <= 1)
		cout << "Usage:" << endl << "\t"
			<< argv[0] << " <size of the map>" << endl
			<< "\texample: " << argv[0] << " 10" << endl;
	else
	{
		game board;
		Create_Game(board, 10, doesMultiplayer());
		srand(time(NULL));
		do
		{
			board.user %= 2;
			printMap((const int **&)board.board, board.size);
			MakeMove(board);
			++board.user;
		}
		while(1);
		printMap((const int **&)board.board, board.size);
		free_square(board.board, board.size);
	}
	return 0;
}