#include <stdlib.h>
#include <time.h> 

square* Corners[4];
square* Sides[4];

void update_corners() {
	Corners[0] = &board[0][0];
	Corners[1] = &board[0][2];
	Corners[2] = &board[2][0];
	Corners[3] = &board[2][2];

}
void update_sides() {
	Sides[0] = &board[0][1];
	Sides[1] = &board[1][0];
	Sides[2] = &board[1][2];
	Sides[3] = &board[2][1];
}

void level_one() {
	square* RandomArr[8];
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j].state == blank)
			{
				RandomArr[count] = &board[i][j];
				count++;
			}
				 
		}
	}
		srand(time(NULL));
		int randomPos = rand() % count;
		RandomArr[randomPos]->state = O;
}




bool try_to_win() {
	int player_turn = -1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j].state == blank) {
				board[i][j].state = O;
				if (Check_Winner(player_turn))
				{
					return true;
				}
				else {
					board[i][j].state = blank;
				}
			}
		}
	}
	return false;
}

bool prevent_victory() {
	int player_turn = -1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j].state == blank) {
				board[i][j].state = X;
				if (Check_Winner(player_turn))
				{
					board[i][j].state = O;
					return true;
				}
				else
					board[i][j].state = blank;
			}
		}
	}
	return false;
}

void level_two() {
	if (!try_to_win())
		 if (!prevent_victory())
			level_one();
}




bool pick_corners_randomly() {
	square* RandomArr[4];
	int count = 0;

	for (int i = 0; i < 4; i++) {
		if (Corners[i]->state == blank)
		{
			RandomArr[count] = Corners[i];
			count++;
		}
	}
	if (count > 0)
	{
		srand(time(NULL));
		int randomPos = rand() % count;
		RandomArr[randomPos]->state = O;
		return true;
	}
	return false;
}
bool pick_sides_randomly() {
	square* RandomArr[4];
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (Sides[i]->state == blank)
		{
			RandomArr[count] = Sides[i];
			count++;
		}
	}
	
	if (count > 0)
	{
		srand(time(NULL));
		int randomPos = rand() % count;
		RandomArr[randomPos]->state = O;
		return true;
	}
	return false;
}
bool check_corners_for_X() {
	for (int i = 0; i < 4; i++) {
		if (Corners[i]->state == X)
		{
			return true;
		}
	}
	return false;
}
bool defence() {
	//if X in the corner->O in the middle
	//if X in the middle->O in the corner
	//if X in the sides->O in the corner

	if (check_corners_for_X() && board[1][1].state == blank)
	{
		board[1][1].state = O;
		return true;
	}
	if (board[1][1].state == X || !check_corners_for_X())
	{
		if (pick_corners_randomly())
			return true;
	}
	
	if (pick_sides_randomly())
		return true;
	return false;
	
}

void level_three() {
	update_corners();
	update_sides();
	if (!try_to_win())
		if (!prevent_victory())
			if (!defence())
				level_one();
			
}

