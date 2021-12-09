enum Turn { first, second,pc };
bool Player_turn;

struct square {
	int x, y;
	int state;
};
square board[3][3];

enum State { blank, X, O };
int XScore = 0, OScore = 0, TScore = 0;
wchar_t FPS[20], SPS[20], TS[20];

void reset_squares() {
	int width = 10, height = 10;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j].state = blank;
			board[i][j].x = width;
			board[i][j].y = height;
			width += 100;
		}
		width = 10;
		height += 100;
	}
}

void reset_game() {
	reset_squares();
	Player_turn = first;
}

void reset_score() {
	XScore = 0;
	OScore = 0;
	TScore = 0;
	wsprintf(FPS, L"%s\n%i", L"Player 1 (X)", XScore);
	wsprintf(SPS, L"%s\n %i", L"Player 2 (O)", OScore);
	wsprintf(TS, L"%s\n %i", L"Tie", TScore);

}

boolean Check_Winner(int &player_number) {

	//three horizontals
	for (int i = 0; i < 3; i++) {
		if (board[i][0].state == board[i][1].state && board[i][1].state==board[i][2].state && board[i][0].state!=blank)
		{
			player_number=board[i][0].state;
			return true;
		}
	}

	//three verticals
	for (int i = 0; i < 3; i++) {
		if (board[0][i].state == board[1][i].state && board[1][i].state == board[2][i].state && board[0][i].state != blank){
			player_number = board[0][i].state;
			return true;
		}
			
	}

	//two diagonal lines
	if (board[0][0].state == board[1][1].state && board[1][1].state == board[2][2].state && board[1][1].state != blank){
		player_number = board[1][1].state;
		return true;
	}
	else if (board[2][0].state == board[1][1].state && board[1][1].state == board[0][2].state && board[1][1].state != blank) {
		player_number = board[1][1].state;
		return true;
	}
	return false;
}

boolean board_is_full() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j].state == blank)
				return false;
		}
	}
	return true;
}