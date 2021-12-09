
void paint_background(HDC hdc, PAINTSTRUCT ps, COLORREF color) {
	COLORREF brushColor = color;
	HBRUSH hbrush = CreateSolidBrush(brushColor);
	FillRect(hdc, &ps.rcPaint, hbrush);
}

void draw_board(HDC hdc, COLORREF Lines_color) {
	
	
	int LineLength = 0.83333333 * Window_height;
	HPEN hPenOld;//for storage for the hLinePen
	HPEN hLinePen;
	COLORREF qLineColor = Lines_color;
	hLinePen = CreatePen(PS_SOLID, 3, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);
	
	//Two vertical lines
	MoveToEx(hdc, 110, dis_from_left_corner, NULL);
	LineTo(hdc, 110, LineLength+ dis_from_left_corner);
	MoveToEx(hdc, 210, dis_from_left_corner, NULL);
	LineTo(hdc, 210, LineLength+ dis_from_left_corner);
	

	//Two Horizontal lines
	MoveToEx(hdc, dis_from_left_corner, 110, NULL);
	LineTo(hdc, LineLength+ dis_from_left_corner, 110);
	MoveToEx(hdc, dis_from_left_corner, 210, NULL);
	LineTo(hdc, LineLength+ dis_from_left_corner, 210);

	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);

}

void draw_O(HDC hdc, COLORREF Lines_color, int x, int y) {
	
	HPEN hPenOld;//for storage for the hLinePen
	HPEN hEllipsePen;
	COLORREF qEllipseColor = Lines_color;
	hEllipsePen = CreatePen(PS_SOLID, 7, qEllipseColor);
	hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);

	Arc(hdc, x + dis_from_left_corner, y + dis_from_left_corner, square_length + x - dis_from_left_corner, square_length + y - dis_from_left_corner,0,0,0,0);


	SelectObject(hdc, hPenOld);
	DeleteObject(hEllipsePen);


}

void draw_X(HDC hdc, COLORREF Lines_color,int x,int y) {
	HPEN hPenOld;//for storage for the hLinePen
	HPEN hLinePen;
	COLORREF qLineColor = Lines_color;
	hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);

	//from up=right to down-left
	MoveToEx(hdc, x+ dis_from_left_corner, y+ dis_from_left_corner, NULL);
	LineTo(hdc, square_length+x- dis_from_left_corner, square_length+y- dis_from_left_corner);
	//from down left to up right
	MoveToEx(hdc, x + dis_from_left_corner, y + square_length- dis_from_left_corner, NULL);
	LineTo(hdc, square_length + x- dis_from_left_corner, y+ dis_from_left_corner);

	
	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);

}

void draw_updated_board(HDC hdc) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (board[i][j].state) {
			case O: {
				draw_O(hdc, RGB(255, 255, 255), board[i][j].x, board[i][j].y);//RGB(255, 255, 255)
			} break;
			case X: {
				draw_X(hdc, RGB(60, 179, 113), board[i][j].x, board[i][j].y);//RGB(60, 179, 113)
			} break;
			default: {

			}
			}

		}
	}
	
}

void bold_winning_strike(HDC hdc,square& square1, square& square2, square& square3,State winner) {
	if (winner == X) {
		draw_X(hdc, RGB(60, 179, 113), square1.x-10, square1.y-10);//RGB(60, 179, 113)
		draw_X(hdc, RGB(60, 179, 113), square2.x - 10, square2.y-10);//RGB(60, 179, 113)
		draw_X(hdc, RGB(60, 179, 113), square3.x - 10, square3.y-10);//RGB(60, 179, 113)
	}
	else {
		draw_O(hdc, RGB(60, 179, 113), square1.x - 10, square1.y - 10);//RGB(60, 179, 113)
		draw_O(hdc, RGB(60, 179, 113), square2.x - 10, square2.y - 10);//RGB(60, 179, 113)
		draw_O(hdc, RGB(60, 179, 113), square3.x - 10, square3.y - 10);//RGB(60, 179, 113)
	}
}