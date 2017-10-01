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
		int ** board;
		int size = atoi(argv[1]);
		srand(time(NULL));
		board = Create_2d_Useable(board, size);
		int userCounter = 1, 
			game_playing = doesMultiplayer(),
			coordinate[Y_X];
		do
		{
			userCounter %= 2;
			printMap(board, size);
			if(game_playing == 1)
				MakeMove(board, size, userCounter, coordinate, 1);
			else
				MakeMove(board, size, userCounter, coordinate);
			++userCounter;
		}
		while(WinSituation(board, size, coordinate) == false);
		printMap(board,size);
		free_square(board, size);
	}
	return 0;
}