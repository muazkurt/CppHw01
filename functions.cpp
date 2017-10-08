#include "./functions.h"




	void printHead(const int & size)
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


	void printBody(const int **& array_2d, const int & size)
	{
		int won = 0;
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
					case 3:
						won = 1;
						cout << 'x';
						break;
					case 4:
						won = 2;
						cout << 'o';
						break;
					default:
						cout << '-';
						break;
				}
				cout << ' ';
			}
			cout << endl;
		}
		if(won > 0)
			cout << "User " << won << " won!" << endl;
		return;
	}

	void printMap(const int **& array_2d, int size)
	{
		printHead(size);
		printBody(array_2d, size);
		return;
	}


	void Create_2d_Array(int **& input, const int & size)
	{
		input = (int **)std::malloc(sizeof(int *) * size);
		for(int i = 0; i < size; ++i)
			input[i] = (int *)std::malloc(sizeof(int) * size);
		return;
	}


	void Fill_2d_with_0(int **& array, const int & size)
	{
	    for(int i = 0; i < size; ++i)
	        for(int j = 0; j < size; ++j)
	            array[i][j] = 0;
	    return;
	}


	void Create_2d_Useable(int **& input, const int & size)
	{
	    Create_2d_Array(input, size);
	    Fill_2d_with_0(input, size);
	    return;
	}


void Create_Game(game & board, int size, int ai, int user)
{
	Create_2d_Useable(board.board, size);
	board.size = size;
	board.AI_Open = ai;
	board.user = user;
	board.coordinate[0] = 0;
	board.coordinate[1] = 0;
}

//
	int CharLover(char & letter)
	{
		int i = 0;
		if(letter >= 'A' && letter <= 'Z')
		{
			letter -= ('A' - 'a');
			++i;
		}
		return i;
	}

	int stringLover(string & traget)
	{
		int counter = 0;
		for(int i = 0; traget[i] != 0; ++i)
			counter += CharLover(traget[i]);
		return counter;
	}

	int doesMultiplayer()
	{
		cout << "   ------------" << endl
			<<  "P) User vs User" << endl
			<<  "C) User vs Coop" << endl
			<<  "Choice: ";
		int input = 0;
		while(input == 0)
		{
			char section = 0;
			cin >> section;
			CharLover(section);
			if(section == 'p')
				input = 2;
			else if(section == 'c')
				input = 1;
			else
				cout << "Please give another input" << endl
					 << "Choice: ";
		}
		return input - 1;
	}

	int PositionY(const game & situation)
	{
		int i = situation.size - 1;
		if(situation.board[0][situation.coordinate[1]] == 0)
			for(i; situation.board[i][situation.coordinate[1]] > 0 && i >= 0; --i);
		else
			i = -1;
		return i;
	}


	void getInput(game & onTarget)
	{
		onTarget.coordinate[1] = -1;
		do{
			cout << "Please give me a character in range a - "
				<< (char)('a' + (onTarget.size - 1)) 
				<< " to make your move: ";
			string Input;
			cin >> Input;
			stringLover(Input);
			if(Input.size() == 1)
			{
				if(Input[0] > 'a' + (onTarget.size - 1) || Input[0] < 'a')
					cout << "This is not legal." << endl;
				else
				{
					onTarget.coordinate[1] = (Input[0] - 'a');
					onTarget.coordinate[0] = PositionY(onTarget);
					if(onTarget.coordinate[0] == -1)
					{
						cout << "This is not legal." << endl;
						onTarget.coordinate[1] = -1;
					}
				}
			}
			else if(SAVE == Input)
			{
				cin >> Input;
				Input = MEMORY + Input;
				Save(Input, onTarget);
			}
			else if(LOAD == Input)
			{
				cin >> Input;
				Input = MEMORY + Input;
				Load(Input, onTarget);
			}
			else
				cout << "There is no such command" << endl; 
		} while(onTarget.coordinate[1] == -1);
		return;
	}


	void MakeMove(game & onTarget)
	{
		if(onTarget.user == 1)
		{	
			getInput(onTarget);
			onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] = 1;
		}
		else
		{
			if(onTarget.AI_Open == 0)
				Ai_input(onTarget);
			else
				getInput(onTarget);
			onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] = 2;
		}
		return;
	}
	

	void Ai_input(game & onTarget)
	{
		cout << "Computer moving to: ";
		int i = 0;
		bool PositionFound = false;
		while(PositionFound == false)
		{
			switch(i)
			{
				//Watch out for Up to down.
				case 0:
					if(Up_Down(onTarget) > 2 && onTarget.coordinate[0] > 0)
						{
							PositionFound = true;
							--onTarget.coordinate[0];
						}
					break;
				//	Watch out for right down + left up and if it is possible to win for user 1,
				//		then breake it by putting right down onTarget.coordinate.
				case 1:
					if(onTarget.coordinate[0] == onTarget.size - 1 || onTarget.coordinate[1] == onTarget.size - 1);
					else
					{
						int right_temp = Right_Down(onTarget);
						if(right_temp + Left_Up(onTarget) - 1 > 2)
						{
							if((onTarget.coordinate[0] + right_temp < onTarget.size) && (onTarget.coordinate[1] + right_temp < onTarget.size))
							{
								onTarget.coordinate[1] += right_temp;
								if(PositionY(onTarget) == (onTarget.coordinate[0] + right_temp))
								{
									onTarget.coordinate[0] += right_temp;
									PositionFound = true;
								}
								else
									onTarget.coordinate[1] -= right_temp;
							}
						}
					}
					break;
				//	Watch out for right up + left down and if it is possible to win for user 1,
				//		then breake it by putting right up onTarget.coordinate.
				case 2:
					if(onTarget.coordinate[0] == 0 || onTarget.coordinate[1] == onTarget.size - 1);
					else
					{
						int right_temp = Right_Up(onTarget);
						if(right_temp + Left_Down(onTarget) - 1 > 2)
						{
							if((onTarget.coordinate[0] - right_temp >= 0) && onTarget.coordinate[1] + right_temp < onTarget.size)
							{	
								onTarget.coordinate[1] += right_temp;
								if(PositionY(onTarget) == (onTarget.coordinate[0] - right_temp))
								{
									onTarget.coordinate[0] -= right_temp;
									PositionFound = true;
								}
								else
									onTarget.coordinate[1] -= right_temp;
							}
						}
					}
					break;
				//	Watch out for left down + right up and if it is possible to win for user 1,
				//		then breake it by putting left down onTarget.coordinate.
				case 3:
					if(onTarget.coordinate[0] == onTarget.size - 1 || onTarget.coordinate[1] == 0);
					else
					{
						int left_temp = Left_Down(onTarget);
						if(left_temp + Right_Up(onTarget) - 1 > 2)
						{
							if(onTarget.coordinate[0] + left_temp < onTarget.size && onTarget.coordinate[1] - left_temp >= 0)
							{
								onTarget.coordinate[1] -= left_temp;
								if(PositionY(onTarget) == (onTarget.coordinate[0] + left_temp))
								{
									onTarget.coordinate[0] += left_temp;
									PositionFound = true;
								}
								else
									onTarget.coordinate[1] += left_temp;
							}
						}
					}
					break;
				//	Watch out for left up + right down and if it is possible to win for user 1,
				//		then breake it by putting left up onTarget.coordinate.
				case 4:
					if(onTarget.coordinate[0] == 0 || onTarget.coordinate[1] == 0);
					else
					{
						int left_temp = Left_Up(onTarget);
						if(left_temp + Right_Down(onTarget) - 1 > 2)
						{
							if(onTarget.coordinate[0] - left_temp >= 0 && onTarget.coordinate[1] - left_temp >= 0)
							{
								onTarget.coordinate[1] -= left_temp;
								if(PositionY(onTarget) == (onTarget.coordinate[0] - left_temp))
								{
									onTarget.coordinate[0] -= left_temp;
									PositionFound = true;
								}
								else
									onTarget.coordinate[1] += left_temp;
							}
						}
					}
					break;

				//	Watch out for right + left  and if it is possible to win for user 1,
				//		then breake it by putting right onTarget.coordinate.
				case 5:
					if(onTarget.coordinate[1] == onTarget.size - 1);
					else
					{
						int right_temp = To_Right(onTarget);
						if(right_temp + To_Left(onTarget) - 1 > 2)
						{
							if(onTarget.coordinate[1] + right_temp < onTarget.size)
							{
								onTarget.coordinate[1] += right_temp;
								if(onTarget.coordinate[0] == PositionY(onTarget))
								{
									PositionFound = true;			
								}
								else
									onTarget.coordinate[1] -= right_temp;
							}
						}
					}
					break;

				//	Watch out for left + right and if it is possible to win for user 1,
				//		then breake it by putting left onTarget.coordinate.
				case 6:
					if(onTarget.coordinate[1] == 0);
					else
					{
						int left_temp = To_Left(onTarget);
						if(left_temp + To_Right(onTarget) - 1 > 2)
						{
							if(onTarget.coordinate[1] - left_temp >= 0)
							{
								onTarget.coordinate[1] -= left_temp;
								if(onTarget.coordinate[0] == PositionY(onTarget))
								{
									PositionFound = true;			
								}
								else
									onTarget.coordinate[1] += left_temp;
							}
						}
					}
					break;

				//	Search that if there is a possible stack onTarget.coordinate in map for User 2 (AI) side.
				case 7:
					for(onTarget.coordinate[1] = 0, onTarget.coordinate[1] = PositionY(onTarget);
						PositionFound == false && onTarget.coordinate[1] < onTarget.size; 
						++onTarget.coordinate[1], onTarget.coordinate[0] = PositionY(onTarget))
					{
						if(onTarget.coordinate[0] + 1 < onTarget.size)
						{
							++onTarget.coordinate[0];
							if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
								if(Up_Down(onTarget) > 1)
									PositionFound = true;
							--onTarget.coordinate[0];
							// The way like '\' if i can check right down
							if(PositionFound == false && onTarget.coordinate[1] + 1 < onTarget.size)
							{
								++onTarget.coordinate[0];
								++onTarget.coordinate[1];
								int right_temp = 0;
								if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
									right_temp = Right_Down(onTarget);
								--onTarget.coordinate[1];
								--onTarget.coordinate[0];
								if(onTarget.coordinate[0] - 1 >= 0 && onTarget.coordinate[1] - 1 >= 0)
								{
									--onTarget.coordinate[0];
									--onTarget.coordinate[1];
									if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
										right_temp += Left_Up(onTarget);
									++onTarget.coordinate[1];
									++onTarget.coordinate[0];
								}
								if(right_temp > 1)
									PositionFound = true;
							}
							// The way like '/' if i can check left down
							if(PositionFound == false && onTarget.coordinate[1] - 1 >= 0)
							{
								++onTarget.coordinate[0];
								--onTarget.coordinate[1];
								int left_temp = 0;
								if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
									left_temp = Left_Down(onTarget);
								++onTarget.coordinate[1];
								--onTarget.coordinate[0];
								if(onTarget.coordinate[0] - 1 >= 0 && onTarget.coordinate[1] + 1 < onTarget.size)
								{
									--onTarget.coordinate[0];
									++onTarget.coordinate[1];
									if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
										left_temp += Right_Up(onTarget);
									--onTarget.coordinate[1];
									++onTarget.coordinate[0];
								}
								if(left_temp > 1)
									PositionFound = true;
							}
						}
						if(PositionFound == false && onTarget.coordinate[0] - 1 >= 0)
						{
							if(onTarget.coordinate[1] + 1 < onTarget.size)
							{
								--onTarget.coordinate[0];
								++onTarget.coordinate[1];
								int right_temp = 0;
								if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
									right_temp = Right_Up(onTarget);
								--onTarget.coordinate[1];
								++onTarget.coordinate[0];
								if(onTarget.coordinate[0] + 1 < onTarget.size && onTarget.coordinate[1] - 1 >= 0)
								{
									++onTarget.coordinate[0];
									--onTarget.coordinate[1];
									if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
										right_temp += Left_Down(onTarget);
									++onTarget.coordinate[1];
									--onTarget.coordinate[0];
								}
								if(right_temp > 1)
									PositionFound = true;
							}
							if(onTarget.coordinate[1] - 1 >= 0)
							{
								--onTarget.coordinate[0];
								--onTarget.coordinate[1];
								int left_temp = 0;
								if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
									left_temp = Left_Up(onTarget);
								++onTarget.coordinate[1];
								++onTarget.coordinate[0];
								if(onTarget.coordinate[0] + 1 < onTarget.size && onTarget.coordinate[1] + 1 < onTarget.size)
								{
									++onTarget.coordinate[0];
									++onTarget.coordinate[1];
									if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
										left_temp += Right_Down(onTarget);
									--onTarget.coordinate[1];
									--onTarget.coordinate[0];
								}
								if(left_temp > 1)
									PositionFound = true;
							}
						}
						if(PositionFound == false && onTarget.coordinate[1] + 1 < onTarget.size)
						{
							++onTarget.coordinate[1];
							int right_temp = 0;
							if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
								right_temp = To_Right(onTarget);
							--onTarget.coordinate[1];
							if(onTarget.coordinate[1] - 1 >= 0)
							{
								--onTarget.coordinate[1];
								if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
									right_temp += To_Left(onTarget);
								++onTarget.coordinate[1];
							}
							if(right_temp > 1)
								PositionFound = true;
						}
						if(PositionFound == false && onTarget.coordinate[1] - 1 >= 0)
						{
							--onTarget.coordinate[1];
							int left_temp = 0;
							if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
								left_temp = To_Left(onTarget);
							++onTarget.coordinate[1];
							if(onTarget.coordinate[1] + 1 < onTarget.size)
							{
								++onTarget.coordinate[1];
								if(onTarget.board[onTarget.coordinate[0]][onTarget.coordinate[1]] == 2)
									left_temp = To_Right(onTarget);
								--onTarget.coordinate[1];
							}
							if(left_temp > 1)
								PositionFound = true;
						}
					}
					break;
				//Playing randomise.
				case 8:
					int temp;
					temp = rand() % onTarget.size;
					if(temp < 0)
						temp *= -1;
					onTarget.coordinate[1] = temp;
					onTarget.coordinate[0] = PositionY(onTarget);
					PositionFound = true;
					break;
				default:
					break;
			}
			++i;
		}
		cout << "[" << onTarget.coordinate[0] << "," << onTarget.coordinate[1] << "]" << endl;
		return;
	}


	int Up_Down(const game & input)
	{
		int i = 1;
		bool Legal = true;
		while(Legal == true && input.coordinate[0] + i < input.size)
			{
				if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0] + i][input.coordinate[1]])
					Legal = false;
				else
					++i;
			}
		return i;
	}


	int Right_Down(const game & input)
	{
		int i = 1;
		if(input.coordinate[0] == input.size - 1 || input.coordinate[1] == input.size - 1);
		else
		{
			bool Legal = true;
			while(Legal == true && input.coordinate[0] + i < input.size && input.coordinate[1] + i < input.size)
				{
					if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0] + i][input.coordinate[1] + i])
						Legal = false;
					else
						++i;
				}
		}
		return i;
	}

	int Right_Up(const game & input)
	{
		int i = 1;
		if(input.coordinate[0] == 0 || input.coordinate[1] == input.size - 1);
		else
		{
			bool Legal = true;
			while(Legal == true && input.coordinate[0] - i >= 0 && input.coordinate[1] + i < input.size)
				{
					if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0] - i][input.coordinate[1] + i])
						Legal = false;
					else
						++i;
				}
		}
		return i;
	}


	int Left_Down(const game & input)
	{
		int i = 1;
		if(input.coordinate[0] == input.size - 1 || input.coordinate[1] == 0);
		else
		{
			bool Legal = true;
			while(Legal == true && input.coordinate[0] + i < input.size && input.coordinate[1] - i >= 0)
				{
					if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0] + i][input.coordinate[1] - i])
						Legal = false;
					else
						++i;
				}
		}
		return i;
	}


	int Left_Up(const game & input)
	{
		int i = 1;
		if(input.coordinate[0] == 0 || input.coordinate[1] == 0);
		else
		{
			bool Legal = true;
			while(Legal == true && input.coordinate[0] - i >= 0 && input.coordinate[1] - i >= 0)
				{
					if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0] - i][input.coordinate[1] - i])
						Legal = false;
					else
						++i;
				}
		}
		return i;
	}


	int To_Right(const game & input)
	{
		int i = 1;
		if(input.coordinate[1] == input.size - 1);
		else
		{
			bool Legal = true;
			while(Legal == true && input.coordinate[1] + i < input.size)
				{
					if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0]][input.coordinate[1] + i])
						Legal = false;
					else
						++i;
				}
		}
		return i;
	}


	int To_Left(const game & input)
	{
		int i = 1;
		if(input.coordinate[1] == 0);
		else
		{
			bool Legal = true;
			while(Legal == true && input.coordinate[1] - i >= 0)
			{
				if(input.board[input.coordinate[0]][input.coordinate[1]] != input.board[input.coordinate[0]][input.coordinate[1] - i])
					Legal = false;
				else
					++i;
			}
		}
		return i;
	}


	bool WinSituation(const game & searchOn)
	{
		int y = 0,
			x = 0,
			filler = searchOn.board[searchOn.coordinate[0]][searchOn.coordinate[1]];
		bool win = false;
		if((y = Up_Down(searchOn)) >= 4)
		{
			for(y -= 1; y > 0; --y)
				searchOn.board[searchOn.coordinate[0] + y][searchOn.coordinate[1]] = filler + 2;
			win = true;
		}
		else 
		{
			x = Left_Up(searchOn);
			y = Right_Down(searchOn); 
			if(x + y - 1 >= 4)
			{
				for(y -= 1; y > 0; --y)
					searchOn.board[searchOn.coordinate[0] + y][searchOn.coordinate[1] + y] = filler + 2;
				for(x -= 1; x > 0; --x)
					searchOn.board[searchOn.coordinate[0] - x][searchOn.coordinate[1] - x] = filler + 2;
				win = true;
			}
			else 
			{
				x = Left_Down(searchOn);
				y = Right_Up(searchOn);
				if(x + y - 1 >= 4) 
				{
					for(y -= 1; y > 0; --y)
						searchOn.board[searchOn.coordinate[0] - y][searchOn.coordinate[1] + y] = filler + 2;
					for(x -= 1; x > 0; --x)
						searchOn.board[searchOn.coordinate[0] + x][searchOn.coordinate[1] - x] = filler + 2;
					win = true;
				}
				else 
				{
					x = To_Right(searchOn);
					y = To_Left(searchOn);
					if(x + y - 1 >= 4) 
					{
						for(y -= 1; y > 0; --y)
							searchOn.board[searchOn.coordinate[0]][searchOn.coordinate[1] - y] = filler + 2;
						for(x -= 1; x > 0; --x)
							searchOn.board[searchOn.coordinate[0]][searchOn.coordinate[1] + x] = filler + 2;
						win = true;
					}
				}
			}
		}
		if(win == true)
			searchOn.board[searchOn.coordinate[0]][searchOn.coordinate[1]] = filler + 2;
		return win;
	}


//Working File input Output functions.
	int sizeFromFile(const string & input, int & size)
	{
		int i = 0;
		for(i = 0; input[i] != '/'; ++i)
			size = size * 10 + (input[i] - '0');
		return i;
	}

	int AIformFile(const string & input, int & AI_Open)
	{
		AI_Open = input[1] - '0';
		return 1;
	}

	int userFromFile(const string & input, int & user)
	{
		user = input[1] - '0';
		return 1;
	}

	int lastPlayedPosition(const string & input, int * coordinate)
	{
		int i = 0;
		while(input[i] != ',')
		{
			coordinate[0] = coordinate[0] * 10 +(input[i] - '0');
			++i;
		}
		++i;
		while(input[i] != '/')
		{
			coordinate[1] = coordinate[1] * 10 +(input[i] - '0');
			++i;
		}
		return i;
	}

	int Create_2d_Useable(const string & input, game & board)
	{
		Create_2d_Useable(board.board, board.size);
		for(int j = 0; j < board.size; ++j)
			for(int k = 0; k < board.size; ++k)
				board.board[j][k] = input[k + j * board.size] - '0';
		return board.size * board.size;
	}

	void parseInput(const string & input, game & area)
	{
		area.size = 0;
		int position = 0;
		position = sizeFromFile(input, area.size);
		position += AIformFile(&input[position], area.AI_Open);
		position += userFromFile(&input[position], area.user);
		position += lastPlayedPosition(&input[position], area.coordinate);
		position += Create_2d_Useable(&input[position], area);
		return;
	}

	string fileInput(const string & filename, string & loaded)
	{
		ifstream input;
		input.open(filename);
		input >> loaded;
		input.close();
		return loaded;
	}


	void Load(const string & filename, game & output)
	{
		string input;
		input = fileInput(filename, input);
		parseInput(input, output);
		printMap((const int **&) output.board, output.size);
		return;
	}


	void Int_2d_String(const game & input, string & output)
	{
		output = to_string(input.size);
		output += '/';
		output += input.AI_Open + '0';
		output += '/';
		output += input.user + '0';
		output += '/';
		output += to_string(input.coordinate[0]);
		output += ',';
		output += to_string(input.coordinate[1]);
		output += '/';
		for(int i = 0; i < input.size; ++i)
			for(int j = 0; j < input.size; ++j)
				output += input.board[i][j] + '0';
		return;
	}

	void Save(const string & filename, const game & input)
	{
		ofstream output;
		output.open(filename);
		string info;
		Int_2d_String(input, info);
		output << info;
		output.close();
	}






void free_square(int ** array, int size)
{
	for(int i = 0; i < size; ++i)
		std::free(array[i]);
	std::free(array);
	return;
}